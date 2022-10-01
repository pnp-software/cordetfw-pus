__author__ = 'Alessandro Pasetti, P&P software GmbH'

#===============================================================================
# Code Generator for the PUS Extension of the Cordet Framework.
# The input to the code generator is the project export file of the 
# PUS Extension of the Corder Framework.
#
# This script should be run from the top level directory of the PUS Project (e.g.
# from: /home/ap/Projects/cordetfwpus/) with a command like:
#
#   python3 ./scripts/CrPsCodeGenerator.py ~/Downloads/cordetfw_editor_CordetFw.zip
#
# The argument of the script is the project export file of the PUS Extension.
#
# The configuration information for the script is defined in module config.py.
# This configuration information includes in particular the location of the 
# directories where the generated products are created.
# 
# @copyright P&P Software GmbH, All Rights Reserved
#
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

from Config import specItems, enumTypesToEnumValues, enumValToDerPckts, \
                   pcktToPcktPars, outComponents, inCommands, \
                   derPcktToPcktPars, pcktToDerPckts, domNameToSpecItem, \
                   dataItemTypes, enumTypes, generatedTablesDir, configDir, \
                   services, packets, \
                   CR_FW_OUTFACTORY_MAX_NOF_OUTCMP, CR_FW_INFACTORY_MAX_NOF_INCMD, \
                   CR_FW_OUTREGISTRY_N
from Format import convertEditToLatex
from Utilities import createHeaderFile, getSpecItemName, getTypeAndSubType, \
                      getActionOrCheckFunction, writeDoxy, getPcktLen, getDiscVal


#===============================================================================
# Create header file which the CrPwOutRegistryUserPar header file.
def createCrPsOutRegistryHeader():
    s = ''
    s = s + '#include \"CrPsConstants.h\"\n'
    s = s + '#include \"CrPsTypes.h\"\n\n'

    outRegistryEntries = {}
    for packet in packets:
        if packet['p_kind'] != 'TM' or packet['domain'] == 'Hdr':
            continue
        idServ = packet['p_link']
        servType = int(specItems[idServ]['value'])
        servSubType = int(packet['value'])
        pcktDomName = getSpecItemName(packet)
        discToDerPckt = {}
        if pcktDomName in pcktToDerPckts:
            for derPacket in pcktToDerPckts[pcktDomName]:
                idDiscEnumVal = derPacket['p_link']
                discEnumVal = specItems[idDiscEnumVal]
                disc = discEnumVal['value']
                assert disc.isdigit(), 'Discriminant of ' + pcktDomName + ' is not a positive integer'
                discToDerPckt[int(disc)] = derPacket
        if len(discToDerPckt) == 0:
            outRegistryEntries[(int(servType), int(servSubType), 0, 0)] = ('0', '0')
        else:
            discMin = min(discToDerPckt)
            discMax = max(discToDerPckt)
            discMinEnumVal = getDiscVal(discToDerPckt[discMin])[1]
            discMaxEnumVal = getDiscVal(discToDerPckt[discMax])[1]
            outRegistryEntries[(servType, servSubType, discMin, discMax)] = (discMinEnumVal, discMaxEnumVal)
            
    outRegistryEntriesSorted = dict(sorted(outRegistryEntries.items()))
    
    s = s + writeDoxy(['Total number of out-going service types/sub-types provided by the application'])
    s = s + '#define CR_FW_OUTREGISTRY_NSERV (' + str(len(outRegistryEntriesSorted)) + ')\n\n'

    s = s + writeDoxy(['Maximum number of out-going reports which can be tracked by OutRegstry'])
    s = s + '#define CR_FW_OUTREGISTRY_N (' + str(CR_FW_OUTREGISTRY_N) + ')\n\n'
    
    s = s + '#define CR_FW_OUTREGISTRY_INIT_SERV_DESC {\\\n'
    for index, (key, entry) in enumerate(outRegistryEntriesSorted.items()):
        outRegDef = '    {' + str(key[0]) + ', ' + \
                              str(key[1]) + ', ' + \
                              entry[0] + ', ' + \
                              entry[1]  + ', ' + \
                              '0, 0, 0, 0}'
        if index == len(outRegistryEntriesSorted)-1:
            s = s + outRegDef + '\\\n' 
        else:
            s = s + outRegDef + ',\\\n' 
    s = s + '}\n\n'
        
    createHeaderFile(configDir, 'CrFwOutRegistryUserPar.h', s)
    return 


#===============================================================================
# Create header file which defines the constants with the service and sub-service
# identifiers (CrPsServTypeId header file).
def createCrPsServTypeIdHeader():
    s = ''
    
    for service in services:
        s = s + writeDoxy([service['title'], service['remarks']])
        s = s + '#define ' + service['name'].upper() + '_TYPE (' + service['value'] + ')\n\n' 

    for packet in packets:
        idService = packet['p_link']
        service = specItems[idService]
        s = s + writeDoxy(['Identifier for sub-type of packet '+packet['name']+\
                           ' in service '+service['value'] +' ('+packet['title']+')'])
        if packet['p_kind']=='TM':
            endName = packet['name'][:-3] + 'REP_STYPE ('
        else: 
            endName = packet['name'][:-3] + 'CMD_STYPE ('
        s = s + '#define ' + packet['domain'].upper() + endName.upper() + packet['value'] + ')\n\n'
            
    createHeaderFile(configDir, 'CrPsServTypeId.h', s)
    return


#===============================================================================
# Create header file which defines the CrPs types (DataItemTypes and EnumTypes).
def createCrPsTypesHeader():
    s = ''
    s = s + '#include \"CrFwUserConstants.h\"\n'
    s = s + '#include \"CrFwConstants.h\"\n\n'
    
    for dataItemType in dataItemTypes:
        if dataItemType['name'][0:4] != 'CrPs':
            continue
        s = s + writeDoxy([dataItemType['desc'], dataItemType['remarks']])
        s = s + 'typedef ' + dataItemType['implementation'] + ' ' +  dataItemType['name'] + ';\n\n'
    for enumType in enumTypes:
        if enumType['name'][0:4] != 'CrPs':
            continue
        if enumType['remarks'] == '':
            s = s + writeDoxy([enumType['desc']])
        else:
            s = s + writeDoxy([enumType['desc'], enumType['remarks']])
        s = s + 'typedef ' + enumType['implementation'] + ' ' +  enumType['name'] + ';\n'
        s = s + 'enum {\n'
        enumTypeName = enumType['domain'] + ':' + enumType['name']
        for index, enumValue in enumerate(enumTypesToEnumValues[enumTypeName]):
            s = s + '    ' + enumValue['name'] + ' = ' + enumValue['value']
            if index < len(enumTypesToEnumValues[enumTypeName])-1:
                s = s + ',\n'
            else:
                s = s + '\n'
        s = s + '};\n\n'
            
    createHeaderFile(configDir, 'CrPsTypes.h', s)
    return


#===============================================================================
# Create content of InFactory header file (only the InCommand part of the 
# InFactory is generated)
def createInFactoryHeader():
    s = ''
    for inCommand in inCommands:
        s = s + '#include \"' + inCommand['domain'] + '/' + inCommand['name'] + '.h\"\n'
    s = s + '\n'

    s = s + writeDoxy(['Maximum number of OutComponents which may be allocated at any one time'])
    s = s + '#define CR_FW_INFACTORY_MAX_NOF_INCMD (' + str(CR_FW_INFACTORY_MAX_NOF_INCMD) + ')\n\n'
    
    inCmdTemp = {}
    for inCommand in inCommands:
        packet = specItems[inCommand['p_link']]
        if packet['cat'] == 'DerPacket':
            disc = getDiscVal(packet)[0]
        else:
            disc = '0'
        inCmdSortIndex = (int(getTypeAndSubType(inCommand)[0]),
                          int(getTypeAndSubType(inCommand)[1]),
                          int(disc))
        inCmdTemp[inCmdSortIndex] = inCommand
    inCmdSorted = dict(sorted(inCmdTemp.items()))
            
    s = s + writeDoxy(['The total number of kinds of inCommands supported by the application'])
    s = s + '#define CR_FW_INCMD_NKINDS (' + str(len(inCmdSorted)) + ')\n\n'
    
    s = s + writeDoxy(['Definition of the inCommand kinds supported by the application'])
    s = s + '#define CR_FW_INCMD_INIT_KIND_DESC {\\\n'
    for index, (key, inCommand) in enumerate(inCmdSorted.items()):
        inCmdDef = '    {' + getTypeAndSubType(inCommand)[0] + ', ' + \
                             getTypeAndSubType(inCommand)[1] + ', ' + \
                             disc + ', ' + \
                             '1'  + ', ' + \
                             str(getPcktLen(inCommand)) + ', ' + \
                             '&' + getActionOrCheckFunction(inCommand, 'ValidityCheck') + ', ' + \
                             '&' + getActionOrCheckFunction(inCommand, 'ReadyCheck') + ', ' + \
                             '&' + getActionOrCheckFunction(inCommand, 'StartAction') + ', \\\n        ' + \
                             '&' + getActionOrCheckFunction(inCommand, 'ProgressAction') + ', ' + \
                             '&' + getActionOrCheckFunction(inCommand, 'TerminationAction') + ', ' + \
                             '&' + getActionOrCheckFunction(inCommand, 'AbortAction') + '}'
        if index == len(inCmdSorted)-1:
            s = s + '\\\n' + inCmdDef
        else:
            s = s + ',\\\n' + inCmdDef 
    s = s + '}\n\n'
        
    createHeaderFile(configDir, 'CrFwInFactoryUserPar.h', s)
    return 


#===============================================================================
# Create content of OutFactory header file.
def createOutFactoryHeader():
    s = ''
    for outComponent in outComponents:
        s = s + '#include \"' + outComponent['domain'] + '/' + outComponent['name'] + '.h\"\n'
    s = s + '\n'

    s = s + writeDoxy(['Maximum number of OutComponents which may be allocated at any one time'])
    s = s + '#define CR_FW_OUTFACTORY_MAX_NOF_OUTCMP (' + str(CR_FW_OUTFACTORY_MAX_NOF_OUTCMP) + ')\n\n'
    
    outCmpTemp = {}
    for outComponent in outComponents:
        packet = specItems[outComponent['p_link']]
        if packet['cat'] == 'DerPacket':
            disc = getDiscVal(packet)[0]
        else:
            disc = '0'
        outCmpSortIndex = (int(getTypeAndSubType(outComponent)[0]),
                           int(getTypeAndSubType(outComponent)[1]),
                           int(disc))
        outCmpTemp[outCmpSortIndex] = outComponent
    outCmpSorted = dict(sorted(outCmpTemp.items()))
            
    s = s + writeDoxy(['The total number of kinds of OutComponents supported by the application'])
    s = s + '#define CR_FW_OUTCMP_NKINDS (' + str(len(outCmpSorted)) + ')\n\n'
    
    s = s + writeDoxy(['Definition of the OutComponent kinds supported by the application'])
    s = s + '#define CR_FW_OUTCMP_INIT_KIND_DESC {\\\n'
    for index, (key, outComponent) in enumerate(outCmpSorted.items()):
        outCmpDef = '    {' + getTypeAndSubType(outComponent)[0] + ', ' + \
                              getTypeAndSubType(outComponent)[1] + ', ' + \
                              disc + ', ' + \
                              '2'  + ', ' + \
                              str(getPcktLen(outComponent)) + ', ' + \
                              '&' + getActionOrCheckFunction(outComponent, 'EnableCheck') + ', ' + \
                              '&' + getActionOrCheckFunction(outComponent, 'ReadyCheck') + ', \\\n        ' + \
                              '&' + getActionOrCheckFunction(outComponent, 'RepeatCheck') + ', ' + \
                              '&' + getActionOrCheckFunction(outComponent, 'UpdateAction') + ', ' + \
                              '&CrFwOutCmpDefSerialize}'
        if index == len(outCmpSorted)-1:
            s = s + '\\\n' + outCmpDef
        else:
            s = s + ',\\\n' + outCmpDef 
    s = s + '}\n\n'
        
    createHeaderFile(configDir, 'CrFwOutFactoryUserPar.h', s)
    return 


#===============================================================================
# Create table with the event IDs
def generateEvtIds():
    with open(generatedTablesDir+'/PUSExtensionCrPsEvtIdt.csv', 'w') as fd:
        fd.write('Value|Name|Description|Parameters\n')
        for eid in enumTypesToEnumValues['Evt:CrPsEvtId_t']:
            derPckts = enumValToDerPckts[getSpecItemName(eid)]
            if len(derPckts) > 1:
                print('WARNING: Event '+eid['name']+' acts as discriminant for multiple derived packets')
            if len(derPckts) == 0:
                print('WARNING: Event '+eid['name']+' does not act as discriminant for any derived packet')
                continue
            parametersDesc = derPckts[0]['t1']
            fd.write(eid['value'] + '|' +
                     eid['name'] + '|' +
                     eid['desc'] + '|' +
                     parametersDesc + '\n')


#===============================================================================
# Create table with the adaptation points
def generatePusAPs():
    with open(generatedTablesDir+'/PusExtensionAP.csv', 'w') as fd:
        fd.write('Category|Id|Origin|AP|DefValue|Implementation|Remarks\n')
        for id, specItem in specItems.items():
            if specItem['cat'] == 'AdaptPoint' and specItem['domain'] == 'PUS':
                if specItem['name'].count('_') != 2:
                    print('ERROR: PUS adaptation point with incorrect name format: '+specItem['name'])
                    continue

                fd.write(specItem['name'].split('_')[1] + '|' +
                         specItem['name'].split('_')[2] + '|' +
                         convertEditToLatex(specItem['rationale']) + '|' +
                         convertEditToLatex(specItem['title']) + '|' +
                         convertEditToLatex(specItem['value']) + '|' +
                         convertEditToLatex(specItem['implementation']) + '|' +
                         convertEditToLatex(specItem['remarks']) + '\n')


#===============================================================================
# Create table with the requirements
def generatePusReqs():
    with open(generatedTablesDir+'/PusExtensionReq.csv', 'w') as fd:
        fd.write('Category|Type|Id|Text|Implementation|Verification|Remarks\n')
        for id, specItem in specItems.items():
            if specItem['cat'] == 'Requirement' and specItem['domain'] == 'PUS':
                if '_' not in specItem['name']:
                    print('ERROR: PUS requirement with incorrect name format: '+specItem['name'])
                    continue
                if specItem['p_kind'] == 'CNS':
                    reqKind = 'C'
                elif specItem['p_kind'] == 'STD':
                    reqKind = 'S'
                elif specItem['p_kind'] == 'PRP':
                    reqKind = 'P'
                elif specItem['p_kind'] == 'AP':
                    reqKind = 'A'
                else:
                    reqKind = '??'

                fd.write(specItem['name'].split('_')[0] + '|' +
                         reqKind + '|' +
                         specItem['name'].split('_')[1] + '|' +
                         convertEditToLatex(specItem['value']) + '|' +
                         convertEditToLatex(specItem['implementation']) + '|' +
                         convertEditToLatex(specItem['t1']) + '|' +
                         convertEditToLatex(specItem['remarks']) + '\n')


#===============================================================================
# Create table with the definition of the constants
def generateConstants():
    with open(generatedTablesDir+'/Constants.csv', 'w') as fd:
        fd.write('Domain|Name|Desc|Value|Remarks\n')
        for id, specItem in specItems.items():
            if specItem['cat'] == 'DataItem' and specItem['p_kind'] == 'CNS':
                fd.write(specItem['domain'] + '|' +
                         specItem['name'] + '|' +
                         convertEditToLatex(specItem['desc']) + '|' +
                         convertEditToLatex(specItem['value']) + '|' +
                         convertEditToLatex(specItem['remarks']) + '\n')


#===============================================================================
# Create table with the definition of the data pool items
def generateDataPool():
    with open(generatedTablesDir+'/DataPool.csv', 'w') as fd:
        fd.write('Kind|Domain|Name|ShortDesc|Value|Unit|Multiplicity|Type|Remarks\n')
        for id, specItem in specItems.items():
            if specItem['cat'] == 'DataItem' and specItem['p_kind'] in ('PAR', 'VAR'):
                dataItemType = specItems[specItem['p_link']]
                multiplicity = convertEditToLatex(specItem['t1'])
                if ':' in multiplicity:
                    multiplicity = multiplicity.split(':')[1]
                fd.write(specItem['p_kind'].lower() + '|' +
                         specItem['domain'] + '|' +
                         specItem['name'] + '|' +
                         convertEditToLatex(specItem['desc']) + '|' +
                         convertEditToLatex(specItem['value']) + '|' +
                         convertEditToLatex(specItem['t2']) + '|' +
                         multiplicity + '|' +
                         dataItemType['name'] + '|' +
                         convertEditToLatex(specItem['remarks']) + '\n')


#===============================================================================
# Create table with the command and report specification
def generateCrPsSpec():
    with open(generatedTablesDir+'/CrPsSpec.tex', 'w') as fd:
        for id, specItem in specItems.items():
            if specItem['cat'] == 'InCommand':
                cmdName = specItem['domain'] + specItem['name'][:-5]
                caption = 'InCmd' + cmdName + 'CmdSpec'
                caption_tbl = 'Specification of '+cmdName+'Cmd Component'
                cmdPacket = specItems[specItem['p_link']]
                packetService = specItems[cmdPacket['p_link']]
                cmdType = packetService['value']
                cmdSubType = cmdPacket['value']
                if cmdPacket['s_link'] == '' or cmdPacket['s_link'] == None:
                    discTitle = 'None'
                else:
                    disc = specItems[cmdPacket['s_link']]
                    discTitle = disc['desc']
                fd.write('\\def \\print{0}#1 {{\n'.format(caption) + 
                         '\\begin{pnptable}{#1}' + 
                         '{' + caption_tbl + '}' + 
                         '{tab:' + caption + '}' +
                         '{' + 'Name & ' + cmdName + 'Cmd(' + cmdType  + ',' + cmdSubType + ')}\n'
                         )
                fd.write('Description & ' + convertEditToLatex(cmdPacket['title']) + '\\\\\\hline\n') 
                fd.write('Parameters & ' + convertEditToLatex(cmdPacket['t1']) + '\\\\\\hline\n') 
                fd.write('Discriminant & ' + convertEditToLatex(discTitle) + '\\\\\\hline\n') 
                fd.write('Ready Check & ' + convertEditToLatex(specItem['t1']) + '\\\\\\hline\n') 
                fd.write('Start Action & ' + convertEditToLatex(specItem['t2']) + '\\\\\\hline\n') 
                fd.write('Progress Action & ' + convertEditToLatex(specItem['t3']) + '\\\\\\hline\n') 
                fd.write('Termination Action & ' + convertEditToLatex(specItem['t4']) + '\\\\\\hline\n') 
                fd.write('Abort Action & ' + convertEditToLatex(specItem['t5']) + '\\\\\\hline\n') 
                fd.write('\\end{pnptable}}\n\n') 

            if specItem['cat'] == 'OutComponent':
                repName = specItem['domain'] + specItem['name'][:-6]
                caption = 'OutCmp' + repName + 'RepSpec'
                # Captions in \def commands cannot contain numbers; we 
                # therefore replace them with letters
                digitsToLetters = caption.maketrans('1234567890', 'abcdefghij')
                caption = caption.translate(digitsToLetters)
                caption_tbl = 'Specification of '+repName+'Rep Component'
                repPacket = specItems[specItem['p_link']]
                packetService = specItems[repPacket['p_link']]
                repType = packetService['value']
                repSubType = repPacket['value']
                if repPacket['s_link'] == '' or repPacket['s_link'] == None:
                    discTitle = 'None'
                else:
                    disc = specItems[repPacket['s_link']]
                    discTitle = disc['title']
                fd.write('\\def \\print{0}#1 {{\n'.format(caption) + 
                         '\\begin{pnptable}{#1}' + 
                         '{' + caption_tbl + '}' + 
                         '{tab:' + caption + '}' +
                         '{' + 'Name & ' + repName + 'Rep(' + repType  + ',' + repSubType + ')}\n'
                         )
                fd.write('Description & ' + convertEditToLatex(repPacket['title']) + '\\\\\\hline\n') 
                fd.write('Parameters & ' + convertEditToLatex(repPacket['t1']) + '\\\\\\hline\n') 
                fd.write('Discriminant & ' + convertEditToLatex(discTitle) + '\\\\\\hline\n') 
                fd.write('Enable Check & ' + convertEditToLatex(specItem['t1']) + '\\\\\\hline\n') 
                fd.write('Ready Check & ' + convertEditToLatex(specItem['t2']) + '\\\\\\hline\n') 
                fd.write('Repeat Check & ' + convertEditToLatex(specItem['t3']) + '\\\\\\hline\n') 
                fd.write('Update Action & ' + convertEditToLatex(specItem['t5']) + '\\\\\\hline\n') 
                fd.write('\\end{pnptable}}\n\n') 


#===============================================================================
# Build a cross-table. 
# A cross-table is a dictionary where:
# - the key is the Domain:Name of a spec_item of category C1
# - the value is a list of spec_items of type C2 which have either a p_link
#   or an s_link to the key
# .
# The arguments of this function are:
# - the cross-table dictionary (must be empty when the function is called)
# - the categories C1 and C2
# - the type of link (either 'p_link' or 's_link')
# .
def buildCrossTable(crossTable, keyCatParent, keyCatChild, keyLink): 
    for id, specItem in specItems.items():
        if specItem['cat'] == keyCatParent:
            keyName = specItem['domain'] + ':' + specItem['name']
            crossTable[keyName] = []
    for id, specItem in specItems.items():
        if specItem['cat'] == keyCatChild:
            if specItem[keyLink] in specItems:
                specItemDomName = specItems[specItem[keyLink]]['domain'] + ':' + \
                                  specItems[specItem[keyLink]]['name'] 
                if specItemDomName in crossTable:
                    crossTable[specItemDomName].append(specItem)


#===============================================================================
# Delete the tmp directory if it exists; therwise create it.
# Expand the Cordet FW Project file in the tmp directory,
# read the configuration file and initialize the global variables,
# and then generate all products
def procCordetFw(cordetFwPrFile):
    if os.path.isdir('tmp'):
        shutil.rmtree('tmp')
    os.makedirs('tmp')
        
    try:    
        with zipfile.ZipFile(cordetFwPrFile, 'r') as fd:
            fd.extractall('tmp')    
    except Exception as e:
        print('ERROR: Failure to uncompress Cordet FW Project file '+cordetFwPrFile)
        print('       '+repr(e))
        return
        
    with open('tmp/spec_items.csv') as fd:
        fdDict = csv.DictReader(fd)
        for row in fdDict:
            if not row['status'] in ('NEW', 'CNF', 'MOD'):
                continue
            specItems[row['id']] = row
            if row['cat'] == 'InCommand':
                inCommands.append(row)
            if row['cat'] == 'OutComponent':
                outComponents.append(row)
            if row['cat'] == 'DataItemType':
                dataItemTypes.append(row)
            if row['cat'] == 'EnumType':
                enumTypes.append(row)
            if row['cat'] == 'Service':
                services.append(row)
            if row['cat'] == 'Packet':
                packets.append(row)
            domNameToSpecItem[row['domain']+':'+row['name']] = row
    
    # Build cross-tables
    buildCrossTable(enumTypesToEnumValues, 'EnumType', 'EnumValue', 's_link')
    buildCrossTable(enumValToDerPckts, 'EnumValue', 'DerPacket', 'p_link')
    buildCrossTable(pcktToPcktPars, 'Packet', 'PacketPar', 'p_link')
    buildCrossTable(derPcktToPcktPars, 'DerPacket', 'PacketPar', 'p_link')
    buildCrossTable(pcktToDerPckts, 'Packet', 'DerPacket', 's_link')
    
    # Build tables required for the PUS specification
    generateCrPsSpec()
    generateConstants()
    generateDataPool()
    generatePusReqs()
    generatePusAPs()
    generateEvtIds()
    
    # Build implementation-level generated products 
    createOutFactoryHeader()
    createInFactoryHeader()
    createCrPsTypesHeader()
    createCrPsServTypeIdHeader()
    createCrPsOutRegistryHeader()
    
    
#===============================================================================
## Dummy main to be used to test the functions defined in this module.
if __name__ == "__main__":
    if (len(sys.argv) == 2):
        cordetFwPrFile = sys.argv[1]
        if not os.path.isfile(cordetFwPrFile):
            print('ERROR: first argument is not a file'+cordetFwPrFile)
            exit()
        procCordetFw(cordetFwPrFile)
    else:
        print("Usage: python3 CrPsCodeGenerator CordetFwPrFile")

