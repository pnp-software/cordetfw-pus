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
                   derPcktToPcktPars, specItems, domNameToSpecItem, \
                   MAX_LINE_LENGTH, isEndianitySwapNeeded,constToSpecItem
from Format import pattern_edit


#===============================================================================
# Write a list of strings as a doxygen comment to a string and return the string.
# Empty items in the list of strings are ignored.
# Strings which are longer than MAX_LINE_LENGTH are split to fit within MAX_LINE_LENGTH.
def writeDoxy(lines):
    f = ''
    newLines = []
    for line in lines:
        if line == '':
            continue
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
        f = f + '/**\n'
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
    assert pcktPar['cat'] == 'PacketPar'
    pcktParDataItem = specItems[pcktPar['s_link']]
    pcktParDataItemType = specItems[pcktParDataItem['p_link']]
    return int(pcktParDataItemType['n1'])


#===============================================================================
# Return the type of a packet parameter.
def getPcktParType(pcktPar):
    assert pcktPar['cat'] == 'PacketPar'
    pcktParDataItem = specItems[pcktPar['s_link']]
    pcktParDataItemType = specItems[pcktParDataItem['p_link']]
    return pcktParDataItemType['name']


#===============================================================================
# Return the name of the service to which an InCommand or OutComponent belongs.
def getServName(specItem):
    assert specItem['cat'] in ('InCommand', 'OutComponent')
    idPacket = specItem['p_link']
    packet = specItems[idPacket]
    idServ = packet['p_link']
    return specItems[idServ]['name']


#===============================================================================
# Return the type of a data item. If the type of the data item has a native
# type, then the native type is returned; otherwise the type name is returned.
def getDataItemNativeType(specItem):
    assert specItem['cat'] == 'DataItem'
    dataItemTypeId = specItem['p_link']
    dataItemType = specItems[dataItemTypeId]
    if dataItemType['implementation'] == '':
        return dataItemType['name']
    else:
        return dataItemType['implementation']

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
        
    assert False
    return (0,0)


#===============================================================================
# Return the value of the discriminant of a derived packet as an integer and
# as an enumerated value.
def getDiscVal(derPacket):
    idDiscDataItem = derPacket['p_link']
    discDataItem = specItems[idDiscDataItem]
    assert discDataItem['cat'] == 'EnumValue'
    return (discDataItem['value'], discDataItem['name'])
  
    
#===============================================================================
# Return the multiplicity of a data item as a tuple (s, i) where 's' is the 
# symbolic value of the multiplicty and 'i' is its integer value.
# If no symbolic value for the multiplicity is defined, 's' is set to the 
# empty string.
# The following cases are handled:
# - No multiplicity is defined (empty string): a value of ('', 1) 1 is returned
# - The multiplicity field contains a reference to another data item: (s,i) is
#   returned with 's' being the name of the referenced data item and 'i' its
#   value as an integer
# - The multiplicity is assumed to be a string representing an integer: ('',i)
#   is returned value with 'i' being the integer representation of the string
def getMultiplicity(dataItem):
    assert dataItem['cat'] == 'DataItem'
    try:
        mult = dataItem['t1']
        if mult == '':          # No multiplicity is defined, 1 is assumed
            return ('', 1)
            
        match = pattern_edit.search(dataItem['t1'])
        if match != None:
            refName = match.group(2)+':'+match.group(3)
            return (match.group(3), int(domNameToSpecItem[refName]['value']))
        
        return ('', int(mult))
    except:
        print('ERROR: multiplicity of '+getSpecItemName(dataItem)+' could not '+\
              ' be established. A value of 1 is returned')
        return ('', 1)
          
        
#===============================================================================
# Return True if the argument text specifies a default implementation for
# an InCommand or OutComponent check or action. A check or action specification
# is declared to be "default implementation" if its specification starts
# with the string 'default implementation' (case insensitive).
def isDefault(actionOrCheckText):
    return actionOrCheckText.lower().startswith('default implementation')


#===============================================================================
# The argument text specifies an action or check of a command/report.
# This function checks whether the specification is the same as the specification
# of an action or check of another command/report. In that case, it returns
# the specification of the referenced action or check. 
# If, instead, the specification is not the same as the specification of another
# action or check, the function returns an empty string.
# A specification is declared to be the same as the specificatin of another 
# action or check if it begins with: 'same as' and then contains a reference 
# to an InCommand or OutComponent.
# Argument 'name' holds the name of the action or check (e.g. 'EnableCheck' or
# 'StartAction'.
def getSameAs(actionOrCheckText, specItem, actionOrCheckName):
    if not actionOrCheckText.lower().startswith('same as'):
        return ''
    
    match = pattern_edit.search(actionOrCheckText)
    if match == None:
        return ''
    
    referredItemName = match.group(2)+':'+match.group(3)
    assert referredItemName in domNameToSpecItem
    referredItem = domNameToSpecItem[referredItemName]
    assert referredItem['cat'] == specItem['cat']
    return getActionOrCheckFunction(referredItem, actionOrCheckName)


#===============================================================================
# Return the name of the function implementing a command's or component's action
# or check.
# Argument 'name' holds the name of the action or check (e.g. 'EnableCheck' or
# 'StartAction'.
# This function considers two special cases of action or check name:
# - If the specification of the action or check name begins with 'default 
#   implementation', then the name of the function with the default implementation
#   for the corresponding check or action is returned
# - If the specification of the action or check begins with: 'same as' and
#   then contains a reference to an InCommand or OutComponent, then the
#   name of the function implementing the action or check in the referenced
#   InCommand or OutComponent is returned
# .
# If neither of the above conditions are satisfied, then the name for the 
# function implementing the action or check is built from the name of the 
# argument InCommand or OutComponent and the name of the action or check.
def getActionOrCheckFunction(specItem, name):
    assert specItem['cat'] in ('OutComponent', 'InCommand') 
    if specItem['cat'] == 'OutComponent':
        if name == 'EnableCheck':
            if isDefault(specItem['t1']):
                return 'CrFwOutCmpDefEnableCheck'
            temp = getSameAs(specItem['t1'], specItem, name)
            if temp != '':
                return temp
        if name == 'ReadyCheck':
            if isDefault(specItem['t2']):
                return 'CrFwSmCheckAlwaysTrue'
            temp = getSameAs(specItem['t2'], specItem, name)
            if temp != '':
                return temp
        if name == 'RepeatCheck':
            if isDefault(specItem['t3']):
                return 'CrFwSmCheckAlwaysFalse'
            temp = getSameAs(specItem['t3'], specItem, name)
            if temp != '':
                return temp
        if name == 'UpdateAction':
            if isDefault(specItem['t5']):
                return 'CrFwSmEmptyAction'
            temp = getSameAs(specItem['t5'], specItem, name)
            if temp != '':
                return temp
                
        return 'CrPsOutCmp' + specItem['domain'] + specItem['name'][:-6] + 'Rep' + name

    if specItem['cat'] == 'InCommand':
        if name == 'ValidityCheck':
            if isDefault(specItem['value']):
                return 'CrFwInCmdDefValidityCheck'
            temp = getSameAs(specItem['value'], specItem, name)
            if temp != '':
                return temp
        if name == 'ReadyCheck':
            if isDefault(specItem['t1']):
                return 'CrFwSmCheckAlwaysTrue'
            temp = getSameAs(specItem['t1'], specItem, name)
            if temp != '':
                return temp
        if name == 'StartAction':
            if isDefault(specItem['t2']):
                return 'CrFwSmEmptyAction'
            temp = getSameAs(specItem['t2'], specItem, name)
            if temp != '':
                return temp
        if name == 'ProgressAction':
            if isDefault(specItem['t3']):
                return 'CrFwSmEmptyAction'
            temp = getSameAs(specItem['t3'], specItem, name)
            if temp != '':
                return temp
        if name == 'TerminationAction':
            if isDefault(specItem['t4']):
                return 'CrFwSmSuccessAction'
            temp = getSameAs(specItem['t4'], specItem, name)
            if temp != '':
                return temp
        if name == 'AbortAction':
            if isDefault(specItem['t5']):
                return 'CrFwSmEmptyAction'
            temp = getSameAs(specItem['t5'], specItem, name)
            if temp != '':
                return temp

        return 'CrPsInCmd' + specItem['domain'] + specItem['name'][:-5] + 'Cmd' + name

    assert False


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
        parentPcktLen = getPcktLen(parentPckt)*8
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
# Write a getter function for a packet parameter to a string and return the string.
# If groupSizePar1 is equal to None, the parameter for which the getter method
# is generated is a non-group parameter; else, the parameter is part of a group
# and groupSizePar1 is the parameter holding the group size.
def writePcktParGetterFunction(parName, pcktName, servName, parType, groupSizePar1, groupSizePar2=None):
    assert not ((groupSizePar2!=None) and (groupSizePar1==None))
    if groupSizePar1 == None:
        s = writeDoxy(['Getter function for parameter '+parName+' in packet '+pcktName,
                       '@param p Pointer to the packet',
                       '@return Value of parameter '+pcktName])
        s = s + 'static inline ' + parType + ' get' + \
            servName + pcktName + parName + '(void* p) {\n'
    if groupSizePar1 != None and groupSizePar2 == None:
        s = writeDoxy(['Getter function for an instance of parameter '+parName+' in packet '+pcktName,
                       'The parameter '+parName+' is part of a group. The function returns the value',
                       'of the parameter in the n-th instance of the group.',
                       '@param p Pointer to the packet',
                       '@param n The index (starting from 0) of the group instance from which '+parName+' is read',
                       '@return Value of n-th instance of parameter '+pcktName])
        s = s + 'static inline ' + parType + ' get' + \
            servName + pcktName + parName + '(void* p, '+getPcktParType(groupSizePar1)+' n) {\n'
    if groupSizePar1 != None and groupSizePar2 != None:
        s = writeDoxy(['Getter function for an instance of parameter '+parName+' in packet '+pcktName,
                       'The parameter '+parName+' is part of a nested group. The function returns the value',
                       'of the parameter in the k-th instance of the inner group in the n-th instance of',
                       'the outer group.',
                       '@param p Pointer to the packet',
                       '@param n The index (starting from 0) of the outer group',
                       '@param k The index (starting from 0) of the inner group',
                       '@return Value of n-th instance of parameter '+pcktName])
        s = s + 'static inline ' + parType + ' get' + \
            servName + pcktName + parName + '(void* p, '+getPcktParType(groupSizePar1)+' n, '+\
            getPcktParType(groupSizePar2)+' k) {\n'
    
    s = s + '    ' + pcktName + '_t* t;\n'
    s = s + '     t = (' + pcktName + '_t*)p;\n'
    if groupSizePar1 == None:
        retVal = parName
    if groupSizePar1 != None and groupSizePar2 == None:
        retVal = groupSizePar1['name']+'_[n].'+parName
    if groupSizePar1 != None and groupSizePar2 != None:
        retVal = groupSizePar1['name']+'_[n].'+groupSizePar2['name']+'_[k].'+parName
    if isEndianitySwapNeeded:
        s = s + '    return __builtin_bswap16(t->' + retVal + ');\n'
    else:
        s = s + '    return __t->' + retVal + ';\n'
    s = s + '}\n\n'
    return s


#===============================================================================
# Write a setter function for a packet parameter to a string and return the string.
# If groupSizePar1 is equal to None, the parameter for which the getter method
# is generated is a non-group parameter; else, the parameter is part of a group
# and groupSizePar1 is the parameter holding the group size.
def writePcktParSetterFunction(parName, pcktName, servName, parType, groupSizePar1, groupSizePar2=None):
    if groupSizePar1 == None:
        s = writeDoxy(['Setter function for parameter '+parName+' in packet '+pcktName,
                       '@param p Pointer to the packet',
                       '@param '+parName+' Value to be set in packet\n'])
        s = s + 'static inline void set' + servName + pcktName + \
            parName + '(void* p, ' + parType + ' ' + \
            parName + ') {\n'
    if groupSizePar1 != None and groupSizePar2 == None:
        s = writeDoxy(['Setter function for an instance of parameter '+parName+' in packet '+pcktName,
                       'The parameter '+parName+' is part of a group. The function sets the value',
                       'of the parameter in the n-th instance of the group.',
                       '@param p Pointer to the packet',
                       '@param n The index (starting from 0) of the group instance where '+parName+' is written',
                       '@param '+parName+' Value to be set in packet\n'])
        s = s + 'static inline void set' + servName + pcktName + \
            parName + '(void* p, ' + getPcktParType(groupSizePar1) + ' n, ' + parType + ' ' + \
            parName + ') {\n'
    if groupSizePar1 != None and groupSizePar2 != None:
        s = writeDoxy(['Setter function for an instance of parameter '+parName+' in packet '+pcktName,
                       'The parameter '+parName+' is part of a nested group. The function sets the value',
                       'of the parameter in the k-th instance of the inner group of the n-th instance',
                       'of the outer group',
                       '@param p Pointer to the packet',
                       '@param n The index (starting from 0) of the outer group',
                       '@param k The index (starting from 0) of the inner group',
                       '@param '+parName+' Value to be set in packet\n'])
        s = s + 'static inline void set' + servName + pcktName + \
            parName + '(void* p, ' + getPcktParType(groupSizePar1) + ' n, ' + \
            getPcktParType(groupSizePar2) + ' k, ' + parType + ' ' + parName + ') {\n'
        
    s = s + '    ' + pcktName + '_t* t;\n'
    s = s + '     t = (' + pcktName + '_t*)p;\n'
    if groupSizePar1 == None:
        setVal = parName
    if groupSizePar1 != None and groupSizePar2 == None:
        setVal = groupSizePar1['name'] + '_[n].' + parName
    if groupSizePar1 != None and groupSizePar2 != None:
        setVal = groupSizePar1['name'] + '_[n].' + groupSizePar2['name'] + '_[k].' +  parName
    if isEndianitySwapNeeded:
        s = s + '    t->' + setVal + '= __builtin_bswap16(' + parName + ');\n'
    else:
        s = s + '    t->' + setVal + '= ' + parName + ';\n'
    s = s + '}\n\n'
    return s


#===============================================================================
# Create a header file with the given name and the given content.
def createHeaderFile(dirName, fileName, content, shortDesc):
    name = dirName + '/' + fileName
    ct = str(datetime.datetime.now())
    ifdefName = fileName[:-2].replace('_','').upper()
    with open(name, 'w') as fd:
        fd.write('/**                                          \n')
        fd.write(' * @ingroup gen_cfw                          \n')
        fd.write(' *                                           \n')
        fd.write(' * ' + shortDesc + ' \n')
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
    
        
