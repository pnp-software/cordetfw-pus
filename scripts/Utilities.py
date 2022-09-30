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

from Config import tmPcktHeaderLen, tcPcktHeaderLen, pcktCrcLen, pcktToPcktPars,
                   derPcktToPcktPars


#===============================================================================
# Write a list of strings as a doxygen comment.
# Strings which are longer than MAX_LINE_LENGTH are split to fit within MAX_LINE_LENGTH.
# @param f the file string to which the comments are written
# @param lines the list of lines to be written out as doxygen comments
def writeDoxy(f, lines):
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
        s = newLines[0]
        f += '/** '+s+' */'+'\n'
        return 
    else:
        WriteLn(f, '/**')
        for s in newLines:
            WriteLn(f, ' * ' + s)
        WriteLn(f,' */')


#===============================================================================
# Return the spec_item name as 'Domain:Name'.
def getSpecItemName(specItem):
    return specItem['domain'] + ':' + specItem['name']


#===============================================================================
# Return the length in bits of a packet parameter.
def getPcktParLen(pcktPar):
    pcktParDataItem = specItems[pcktPar['s_link']]
    pcktParDataItemType = specItems[pcktParDataItem['p_link']]
    return pcktParDataItemType['n1']


#===============================================================================
# Return the type and sub-type of the argument packet as a tuple (x,y).
# The argument can be one of: a packet, a derived packet, a telecommand or a
# telemetry report.
def getTypeAndSubType(specItem):
    if specItem['cat'] == 'Packet':
        service = specItem['p_link']
        servType = specItems[service]['value']
        servSubtype = specItem['value']
        return (servType, servSubStype)
        
    if specItem['cat'] == 'DerPacket':
        parentPckt = specItems[specItem['s_link']]
        assert parentPckt['cat'] == 'Packet'
        return getTypeAndSubType(parentPckt)
        
    if specItem['cat'] == 'InCommand' or specItem['cat'] == 'OutComponent':
        packet = specItems[specItem['p_link']]
        assert parentPckt['cat'] == 'Packet'
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
# Return the length in bytes of a packet.
def getPcktLen(specItem):
    pcktName = getSpecItemName(specItem)
    if specItem['cat'] == 'Packet':
        pcktLen = 0
        for pcktPar in pcktToPcktPars[pcktName]:
            pcktLen = pcktLen + getPcktParLen(pcktPar)
        if specItem['p_kind'] == 'TC':
            lenInBits = pcktLen + tcPcktHeaderLen + pcktCrcLen
        else:
            lenInBits = pcktLen + tmPcktHeaderLen + pcktCrcLen
    
    if specItem['cat'] == 'DerPacket':
        parentPckt = specItems[specItem['s_link']]
        assert parentPckt['cat'] == 'Packet'
        parentPcktLen = getPcktLen(specItem)
        pcktLen = 0
        for pcktPar in derPcktToPcktPars[pcktName]:
            pcktLen = pcktLen + getPcktParLen(pcktPar)
        lenInBits = parentPcktLen + pcktLen

    assert (lenInBits % 8)==o, 'Packet '+pcktName+' has non-integer length'
    retrun lenInBits/8

#===============================================================================
# Create a header file with the given name and the given content.
def createHeaderFile(dirName, fileName, content):
    name = dirName + '/' + fileName
    ct = datetime.datetime.now()
    ifdefName = fileName[:-2].replace('_','').upper()
    with open(name, 'w') as fd:
        fd.write('/**                                          \n')
        fd.write(' * @ingroup gen_cfw                          \n')
        fd.write(' *                                           \n')
        fd.write(' * This file is part of the PUS Extention of the  CORDET Framework \n')
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
    
        
