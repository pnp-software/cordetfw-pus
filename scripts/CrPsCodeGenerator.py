__author__ = 'Alessandro Pasetti, P&P software GmbH'

#===============================================================================
# Convenience functions to extract information from the export file of the 
# Cordet FW Editor Project. 
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

from Config import specItems, enumTypesToEnumValues, enumValToDerPckts,
                   pcktToPcktPars, outComponents, inCommands,
                   CR_FW_OUTFACTORY_MAX_NOF_OUTCMP
from Format import convertEditToLatex
from Utilities import createHeaderFile, getSpecItemName, getTypeAndSubType,
                      getActionOrCheckFunction

# Directory where generated tables for PUS Spec are stored
generatedTablesDir = 'doc/pus/GeneratedTables'

# Directory where configuration files are stored
configDir = 'tests/PusConfig'


#===============================================================================
# Create content of OutFactory header file.
def createOutFactoryHeaderContent():
    s = ''
    for outComponent in outComponents:
        s = s + '#include \"' + outComponent['domain'] + '/' + outComponent['name'] + '.h\"\n'

    writeDoxy(s, 'Maximum number of OutComponents which may be allocated at any one time')
    s = s + '#define CR_FW_OUTFACTORY_MAX_NOF_OUTCMP (' + str(CR_FW_OUTFACTORY_MAX_NOF_OUTCMP) + ')\n\n'
    
    outCmpTemp = {}
    for outComponent in OutComponents:
        packet = outComponent['p_link']
        if packet['cat'] == 'DerPacket':
            disc = getDiscVal(packet)
        else:
            disc = '0'
        outCmpSortIndex = (int(getTypeAndSubType(outComponent)[0]),
                           int(getTypeAndSubType(outComponent)[1]),
                           int(disc))
        outCmpTemp[outCmpSortIndex] = outComponent
    outCmpSorted = dict(sorted(outCmpTemp.items()))
            
    writeDoxy(s, 'The total number of kinds of OutComponents supported by the application')
    s = s + '#define CR_FW_OUTCMP_NKINDS (' + str(len(outCmpSorted)) + ')\n\n'
    
    writeDoxy(s, 'Definition of the OutComponent kinds supported by the application')
    s = s + 'CR_FW_OUTCMP_INIT_KIND_DESC {\\ \n'
    for outComponent in outCmpSorted:
        outCmpDef = '{' + getTypeAndSubType(outComponent)[0] + ', ' + \
                          getTypeAndSubType(outComponent)[1] + ', ' + \
                          disc + ', ' + \
                          '2'  + ', ' + \
                          str(getPcktLen(outComponent)) + ', ' + \
                          '&' + getActionOrCheckFunction(outComponent, 'EnableCheck') + ', ' + \
                          '&' + getActionOrCheckFunction(outComponent, 'ReadyCheck') + ', \\ \n' + \
                          '&' + getActionOrCheckFunction(outComponent, 'RepeatCheck') + ', ' + \
                          '&' + getActionOrCheckFunction(outComponent, 'UpdateAction') + ', ' + \
                          '&CrFwOutCmpDefSerialize}, \\ \n'
        s = s + outCmpDef
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

