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

from Config import specItems
from Format import convertEditToLatex

# Regex pattern for internal references to specification items as they
# are stored in the database (e.g. '#iref:1234')
pattern_db = re.compile('#(iref):([0-9]+)')     

# Directory where generated tables for PUS Spec are stored
generatedTablesDir = 'doc/pus/GeneratedTables'


#===============================================================================
# Create table with the definition of the constants
def generateConstants():
    with open(generatedTablesDir+'/Constants.csv', 'w') as fd:
        fd.write('Domain|Name|Desc|Value|Remarks\n')
        for id, specItem in specItems.items():
            if specItem['cat'] == 'DataItem' and specItem['p_kind'] == 'CNS':
                fd.write(specItem['domain'] + '|' +
                         specItem['name'] + '|' +
                         convertEditToLatex(specItem['title']) + '|' +
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
                         convertEditToLatex(specItem['title']) + '|' +
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
                    discTitle = disc['title']
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
            specItems[row['id']] = row
    
    generateCrPsSpec()
    generateConstants()
    generateDataPool()
    
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

