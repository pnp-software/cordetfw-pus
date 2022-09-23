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

#===============================================================================
# Create dictionary holding all requirements.
def extractReq(specItemFile):
    reqs = {}
    with open(specItemFile) as fd:
        specItems = csv.DictReader(fd)
        for specItems in specItemss:
            if specItems['cat'] == 'Requirement':
                desChgs[infoItem['Name']] = {'Title': infoItem['Title'],

    
#===============================================================================
# Delete the tmp directory if it exists; therwise create it.
# Expand the Cordet FW Project file in the tmp directory and
# read the configuration file.
def procCordetFw(cordetFwPrFile, configsFile):
    if os.path.isdir('tmp'):
        shutil.rmtree('tmp')
    os.makedirs('tmp')
        
    with zipfile.ZipFile(cordetFwPrFile, 'r') as zip_ref:
        zip_ref.extractall('tmp')    
        
    try:    
        if os.path.isfile(configsFile):
            with open(configsFile) as config_file:
                configs = json.load(config_file)
    except Exception e:
        print('ERROR: Failure to read configuration file '+configsFile)
        print('       '+repr(e)
        return
        
    reqs = extractReqs('tmp/spec_items.csv')   
    
#===============================================================================
## Dummy main to be used to test the functions defined in this module.
if __name__ == "__main__":
    if (len(sys.argv) == 3):
        cordetFwPrFile = sys.argv[1]
        configsFile = sys.argv[2]
        procCordetFw(cordetFwPrFile, configsFile)
    else:
        print("Usage: python CrPsUtilities CordetFwPrFile")

