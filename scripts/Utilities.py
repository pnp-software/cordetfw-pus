__author__ = 'Alessandro Pasetti, P&P software GmbH'

#===============================================================================
# Convenience functions to support the code generator.
#===============================================================================

import sys
import os
import argparse
import shutil
import csv
import pdb
import json
import operator
import re
import copy
import zipfile
import datetime;

from Config import tmPcktHeaderLen, tcPcktHeaderLen, pcktCrcLen, pcktToPcktPars, \
                   derPcktToPcktPars, specItems, MAX_LINE_LENGTH


#===============================================================================
# Write a list of strings as a doxygen comment to a string and return the string.
# Strings which are longer than MAX_LINE_LENGTH are split to fit within MAX_LINE_LENGTH.
# @param f the file string to which the comments are written
# @param lines the list of lines to be written out as doxygen comments
def writeDoxy(lines):
    f = ''
    newLines = []
    for line in lines:
        if len(line)<=MAX_LINE_LENGTH:
            newLines.append(line)
        else:
            words = line.split()
            newLine = ''
            length = 0
            for word in words:
                length += len(word)+1
                newLine += word + ' '
                if (length>MAX_LINE_LENGTH):
                    newLines.append(newLine)
                    newLine = ''
                    length =0
            if length>0:
                newLines.append(newLine)
       
    if len(newLines) == 1:
        f += '/** ' + newLines[0] + ' */'+'\n'
    else:
        f = f + '/**'
        for s in newLines:
            f = f + ' * ' + s + '\n'
        f = f + ' */\n'
    return f


#===============================================================================
# Return the spec_item name as 'Domain:Name'.
def getSpecItemName(specItem):
    return specItem['domain'] + ':' + specItem['name']


#===============================================================================
# Return the length in bits of a packet parameter.
def getPcktParLen(pcktPar):
    pcktParDataItem = specItems[pcktPar['s_link']]
    pcktParDataItemType = specItems[pcktParDataItem['p_link']]
    return int(pcktParDataItemType['n1'])


#===============================================================================
# Return the type and sub-type of the argument packet as a tuple (x,y).
# The argument can be one of: a packet, a derived packet, a telecommand or a
# telemetry report.
def getTypeAndSubType(specItem):
    if specItem['cat'] == 'Packet':
        service = specItem['p_link']
        servType = specItems[service]['value']
        servSubType = specItem['value']
        return (servType, servSubType)
        
    if specItem['cat'] == 'DerPacket':
        parentPckt = specItems[specItem['s_link']]
        assert parentPckt['cat'] == 'Packet'
        return getTypeAndSubType(parentPckt)
        
    if specItem['cat'] == 'InCommand' or specItem['cat'] == 'OutComponent':
        packet = specItems[specItem['p_link']]
        assert packet['cat'] == 'Packet'
        return getTypeAndSubType(packet)
        
    return (0,0)


#===============================================================================
# Return the value of the discriminant of a derived packet as an integer.
def getDiscVal(derPacket):
    disc = derPacket['p_link']
    if disc['cat'] != 'DataItem':
        print('ERROR: Derived packet '+derPacket['name']+' has a discriminant which is non a data item') 
        return 0
    return disc['value']
        

#===============================================================================
# Return the name of the function implementing a command's or component's action
# or check.
def getActionOrCheckFunction(specItem, name):
    def isDefault(actionOrCheckText):
        return actionOrCheckText.lower().startswith('default implementation')
    
    if name == 'EnableCheck':
        if isDefault(specItem['t1']):
            return 'CrFwOutCmpDefEnableCheck'
    if name == 'ReadyCheck':
        if isDefault(specItem['t2']):
            return 'CrFwSmCheckAlwaysTrue'
    if name == 'RepeatCheck':
        if isDefault(specItem['t3']):
            return 'CrFwSmCheckAlwaysFalse'
    if name == 'UpdateAction':
        if isDefault(specItem['t5']):
            return 'CrFwSmEmptyAction'
    return 'CrPsOutCmp' + specItem['domain'] + specItem['name'][:-5] + name


#===============================================================================
# Return the length in bytes of a packet. The argument can be either a packet,
# or a derived packet, or an InCommand or an OutComponent.
# If a packet contains a parameter with length 0 (parameter of 'deduced type'),
# then the length of the packet is set to 0  to indicate that the length can
# only be determined at run time (e.g. a dynamically defined (3,25) packet).
def getPcktLen(specItem):
    pcktName = getSpecItemName(specItem)
    if specItem['cat'] == 'Packet':
        pcktLen = 0
        for pcktPar in pcktToPcktPars[pcktName]:
            pcktParLen = getPcktParLen(pcktPar)
            if pcktParLen == 0:     # Parameter of 'deduced type'
                return 0
            pcktLen = pcktLen + pcktParLen
        if specItem['p_kind'] == 'TC':
            lenInBits = pcktLen + tcPcktHeaderLen*8 + pcktCrcLen*8
        else:
            lenInBits = pcktLen + tmPcktHeaderLen*8 + pcktCrcLen*8
        assert (lenInBits % 8)==0, 'Packet '+pcktName+' has non-integer length'
        return int(lenInBits/8)
    
    if specItem['cat'] == 'DerPacket':
        parentPckt = specItems[specItem['s_link']]
        assert parentPckt['cat'] == 'Packet'
        parentPcktLen = getPcktLen(specItem)
        if parentPcktLen == 0:      # Parent packet contains a par of 'deduced type'
            return 0
        pcktLen = 0
        for pcktPar in derPcktToPcktPars[pcktName]:
            pcktParLen = getPcktParLen(pcktPar)
            if pcktParLen == 0:     # Parameter of 'deduced type'
                return 0
            pcktLen = pcktLen + getPcktParLen(pcktPar)
        lenInBits = parentPcktLen + pcktLen
        assert (lenInBits % 8)==0, 'DerPacket '+pcktName+' has non-integer length'
        return int(lenInBits/8)
        
    if specItem['cat'] in ('OutComponent', 'InCommand'):
        idPckt = specItem['p_link']
        assert specItems[idPckt]['cat'] in ('Packet', 'DerPacket') 
        return getPcktLen(specItems[idPckt])

    assert False

#===============================================================================
# Create a header file with the given name and the given content.
def createHeaderFile(dirName, fileName, content):
    name = dirName + '/' + fileName
    ct = str(datetime.datetime.now())
    ifdefName = fileName[:-2].replace('_','').upper()
    with open(name, 'w') as fd:
        fd.write('/**                                          \n')
        fd.write(' * @ingroup gen_cfw                          \n')
        fd.write(' *                                           \n')
        fd.write(' * This file is part of the PUS Extension of the  CORDET Framework \n')
        fd.write(' *                                           \n')
        fd.write(' * @note This file was generated on  ' + ct + '\n')
        fd.write(' * @author Automatically generated by CORDET Editor Generator\n')
        fd.write(' * @copyright P&P Software GmbH\n')
        fd.write(' */                                          \n')
        fd.write('#ifndef ' + fileName[:-2].replace('_','').upper() + '_H_\n')
        fd.write('#define ' + fileName[:-2].replace('_','').upper() + '_H_\n')
        fd.write('\n')
        fd.write(content)
        fd.write('#endif /* ' + fileName[:-2].replace('_','').upper() + '_H_ */\n')
    
#===============================================================================
# Create a string representing the #define statement for constant (inclusive of 
# its doxygen comment)
def createVarDef(specItem):
    assert specItem['cat'] == 'DataItem'
    s = ''
    if specItem['remarks'] != '':
        writeDoxy(s, [specItem['desc'], specItem['remarks']])
    else:
        writeDoxy(s, [specItem['desc']])
    s = s + '#define ' + specItem['name'] + '(' +  specItem['value']  + ')'
    return s 
    
        
