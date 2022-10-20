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
                   services, packets, cmdRepSrcDir, pcktDir, servToPckts, \
                   CR_FW_OUTFACTORY_MAX_NOF_OUTCMP, CR_FW_INFACTORY_MAX_NOF_INCMD, \
                   CR_FW_OUTREGISTRY_N, isEndianitySwapNeeded, pcktDir, \
                   dataItemPars, dataItemVars, constToSpecItem, dataItems
from Format import convertEditToLatex
from Utilities import createHeaderFile, getSpecItemName, getTypeAndSubType, \
                      getActionOrCheckFunction, writeDoxy, getPcktLen, getDiscVal, \
                      isDefault, getSameAs, getServName, getPcktParType, \
                      writePcktParGetterFunction, writePcktParSetterFunction, \
                      getMultiplicity, getDataItemNativeType


#===============================================================================
# Create the bodies of the service-specific data pool components.
def createCrPsDataPoolServBodies():
    s = ''
    for service services:
        dataPoolDir = cmdRepSrcDir + '/' + service['name']
        if not os.path.isdir(dataPoolDir):
            os.makedirs(dataPoolDir)

        s = s + '#include \"CrPsDp' + service['name'] + '.h\"\n\n'

        s1 = len(s)
        s = s + 'Dp' + service['name'] + 'Params_t dp' + service['name'] + 'Params =  { \\\n'
        s2 = len(s)
        for par in dataItemPars:
            if par['domain'] == service['name']:
                mult = getMultiplicity(par)
                if mult[1] == 1:
                    s = s + '0, /* ' + par['name'] + ' */ \\\n'
                else:
                    s = s + '{0}, /* ' + par['name'] + ' */ \\\n'
        if len(s) == s2:    # There are no parameters in this service 
            s = s[:(s2-s1)] # Remove definition of data structure
        else:
            s = s + '};\n\n'

        s1 = len(s)
        s = s + 'Dp' + service['name'] + 'Vars_t dp' + service['name'] + 'Vars =  { \\\n'
        s2 = len(s)
        for var in dataItemVars:
            if var['domain'] == service['name']:
                mult = getMultiplicity(var)
                if mult[1] == 1:
                    s = s + '0, /* ' + var['name'] + ' */ \\\n'
                else:
                    s = s + '{0}, /* ' + var['name'] + ' */ \\\n'
        if len(s) == s2:    # There are no variables in this service 
            s = s[:(s2-s1)] # Remove definition of data structure
        else:
            s = s + '};\n\n'

        headerFileName = 'CrPsDp' + service['name'] + '.c'
        shortDesc = 'Interface for accessing data pool items of service ' + service['name'] + \
                    ' (' + service['title'] + ')'
        createHeaderFile(dataPoolDir, headerFileName, s, shortDesc)


#===============================================================================
# Create the headers of the service-specific data pool components.
def createCrPsDataPoolServHeaders():
    s = ''
    for service in services:
        dataPoolDir = cmdRepSrcDir + '/' + service['name']
        if not os.path.isdir(dataPoolDir):
            os.makedirs(dataPoolDir)

        s = s + '#include \"CrPsTypes.h\"\n'
        s = s + '#include \"CrPsConstants.h\"\n'
        s = s + '#include \"CrFwUserConstants.h\"\n'
        s = s + '#include \"CrFwConstants.h\"\n\n'

        s = s + writeDoxy(['Structure holding data pool parameters for service ' + service['name']])
        s = s + 'typedef struct {\n'
        for par in dataItemPars:
            if par['domain'] == service['name']:
                s + writeDoxy([par['title']])
                mult = getMultiplicity(par)
                if mult[1] == 1:
                    s = s + getDataItemNativeType(par) + ' ' + par['name'] + ';\n'
                else:
                    if mult[0] != '':
                        s = s + getDataItemNativeType(par) + ' ' + par['name'] + '[' + mult[0] + '];\n'
                     else:
                        s = s + getDataItemNativeType(par) + ' ' + par['name'] + '[' + mult[1] + '];\n'
        s = s + '} Dp' + service['name'] + 'Params_t;\n\n'
        
        s = s + writeDoxy(['Structure holding data pool variables for service ' + service['name']])
        s = s + 'typedef struct {\n'
        for var in dataItemVars:
            if var['domain'] == service['name']:
                s + writeDoxy([var['title']])
                mult = getMultiplicity(var)
                if mult[1] == 1:
                    s = s + getDataItemNativeType(var) + ' ' + var['name'] + ';\n'
                else:
                    if mult[0] != '':
                        s = s + getDataItemNativeType(var) + ' ' + var['name'] + '[' + mult[0] + '];\n'
                     else:
                        s = s + getDataItemNativeType(var) + ' ' + var['name'] + '[' + mult[1] + '];\n'
        s = s + '} Dp' + service['name'] + 'Vars_t;\n\n'
        
        s = s + writeDoxy(['Extern declaration for structure holding data pool variables in service '+service['name']])
        s = s + 'extern Dp' + service['name'] + 'Params_t Dp' + service['name'] + 'Params;\n\n'
        s = s + writeDoxy(['Extern declaration for structure holding data pool parameters in service '+service['name']])
        s = s + 'extern Dp' + service['name'] + 'Vars_t Dp' + service['name'] + 'Vas;\n\n'

        for dataItem in dataItems:
            if not dataItem['p_kind'] in ['PAR', 'VAR']:
                continue
            mult = getMultiplicity(var)
            kind = 'Vars' if dataItem['p_kind']=='VAR' else 'Params'    
            if mult[1] == 1:
                s = s + writeDoxy(['Get the value of data pool item '+dataItem['name']+' ('+dataItem['title']+')',
                                   '@return the value of data pool item '+dataItem['name']])
                s = s + 'static inline ' + getDataItemNativeType(dataItem) + ' getDp' + service['name'] +\
                    dataItem['name'] + '() {\n'
                s = s + '    return dp' + service['name'] + kind  + '.' + dataItem['name'] + ';\n'
                s = s + '}\n\n'

                s = s + writeDoxy(['Set the value of data pool item '+dataItem['name']+' ('+dataItem['title']+')',
                                   '@param the value of data pool item '+dataItem['name']])
                s = s + 'static inline void setDp' + service['name'] + dataItem['name'] + \
                    '(' + getDataItemNativeType(dataItem) + ' ' + dataItem['name'] + ') {\n'
                s = s + '    dp' + service['name'] + kind  + '.' + dataItem['name'] + \
                    '=' + dataItem['name'] + ';\n'
                s = s + '}\n\n'
            else:
                s = s + writeDoxy(['Get the data pool array '+dataItem['name']+' ('+dataItem['title']+')',
                                   '@return the value of data pool array '+dataItem['name']])
                s = s + 'static inline ' + getDataItemNativeType(dataItem) + '* getDp' + service['name'] +\
                    dataItem['name'] + '() {\n'
                s = s + '    return &dp' + service['name'] + kind  + '.' + dataItem['name'] + ';\n'
                s = s + '}\n\n'
                
                s = s + writeDoxy(['Get i-th element of data pool array '+dataItem['name']+' ('+dataItem['title']+')',
                    '@param i index variable',
                    '@return value of i-th element of data pool array '+dataItem['name']])
                s = s + 'static inline ' + getDataItemNativeType(dataItem) + '* getDp' + service['name'] +\
                    dataItem['name'] + 'Item(int i) {\n'
                s = s + '    return &dp' + service['name'] + kind  + '.' + dataItem['name'] + '[i];\n'
                s = s + '}\n\n'
                
                s = s + writeDoxy(['Set i-th element of data pool item '+dataItem['name']+' ('+dataItem['title']+')',
                                   '@param i index variable',
                                   '@param value of i-th element of data pool item '+dataItem['name']])
                s = s + 'static inline void setDp' + service['name'] + dataItem['name'] + \
                    '(int i, ' + getDataItemNativeType(dataItem) + ' ' + dataItem['name'] + ') {\n'
                s = s + '    dp' + service['name'] + kind  + '.' + dataItem['name'] + '[i]' + \
                    '=' + dataItem['name'] + ';\n'
                s = s + '}\n\n'

        headerFileName = 'CrPsDp' + service['name'] + '.h'
        shortDesc = 'Interface for accessing data pool items of service ' + service['name'] + \
                    ' (' + service['title'] + ')'
        createHeaderFile(dataPoolDir, headerFileName, s, shortDesc)


#===============================================================================
# Create the body of the generic data pool component.
def createCrPsDataPoolBody():
    s = ''
    dataPoolDir = cmdRepSrcDir + '/DataPool'
    if not os.path.isdir(dataPoolDir):
        os.makedirs(dataPoolDir)

    s = s + '#include \"CrPsDp.h\"\n\n'
    s = s + '#include \"CrPsFct.h\"\n'
    for service in services:
        s = s + '#include \"CrPsDp' + service['name'] + '.h\"\n'
    s = s + '\n'
    s = s + writeDoxy(['Structure to hold the location and size information of a data pool entry.'])
    s = s + 'typedef struct _DpMetaInfoEntry_t {\n'
    s = s + '/** The address of the data pool entry */\n'
    s = s + 'void* addr;\n'
    s = s + '/** The length in bytes of the data pool entry */\n'
    s = s + 'size_t length;\n'
    s = s + '/** The number of array elements */\n'
    s = s + 'unsigned int nElements;\n'
    s = s + '/** The length of a single array element */\n'
    s = s + 'size_t elementLength;\n'
    s = s + '} DpMetaInfoEntry_t;\n\n'

    s = s + writeDoxy(['Array of @ref _DpMetaInfoEntry_t to hold the meta information of all ' + \
                       ' data pool entries.'])
    s = s + 'static DpMetaInfoEntry_t dpMetaInfoParams[] = {\n'
    for par in dataItemPars:
        structName = 'dp'+par['domain']+'Params'
        if getMultiplicity(par)[0] != '':
            mult = getMultiplicity(par)[0]
        else:
            mult = str(getMultiplicity(par)[1])
        s = s + '{(void*)&' + structName + '.' + par['name'] + ', ' + \
            'sizeof(' + structName + '.' + par['name'] + ')' + ', ' + \
            mult + ', ' + \
            'sizeof(' + structName + '.' + par['name'] + '[0])},\n'
    s = s[:-2] + '\n}\n\n'

    s = s + 'static DpMetaInfoEntry_t dpMetaInfoVars[] = {\n'
    for var in dataItemVars:
        strucName = 'dp'+var['domain']+'Params'
        if getMultiplicity(var)[0] != '':
            mult = getMultiplicity(var)[0]
        else:
            mult = str(getMultiplicity(var)[1])
        s = s + '{(void*)&' + strucName + '.' + var['name'] + ', ' + \
            'sizeof(' + structName + '.' + var['name'] + ')' + ', ' + \
            mult + ', ' + \
            'sizeof(' + structName + '.' + var['name'] + '[0])},\n'
    s = s[:-2] + '\n}\n\n'

    s = s + 'static DpMetaInfoEntry_t* getMetaInfoParam(CrPsParId_t id) {\n'
    s = s + '   DpMetaInfoEntry_t* p;\n'
    s = s + '   p = NULL;\n'
    s = s + '   if (id >= DpIdParamsLowest && id <= DpIdParamsHighest) {\n'
    s = s + '       p = &dpMetaInfoParams[id-DpIdParamsLowest];\n'
    s = s + '   }\n'
    s = s + '   return p;\n'
    s = s + '}\n\n'

   {
      p = &dpMetaInfoParams[id-DpIdParamsLowest];
   }

    s = s + 'static DpMetaInfoEntry_t* getMetaInfoVar(CrPsParId_t id) {\n'
    s = s + '   DpMetaInfoEntry_t* p;\n'
    s = s + '   p = NULL;\n'
    s = s + '   if (id >= DpIdParamsLowest && id <= DpIdParamsHighest) {\n'
    s = s + '       p = &dpMetaInfoVars[id-DpIdVarsLowest];\n'
    s = s + '   }\n'
    s = s + '   return p;\n'
    s = s + '}\n\n'

    s = s + 'static DpMetaInfoEntry_t* getMetaInfo(CrPsParId_t id) {\n'
    s = s + '   DpMetaInfoEntry_t* p;\n'
    s = s + '   p = getMetaInfoParam(id);\n'
    s = s + '   if (p == NULL) {\n'
    s = s + '       p = getMetaInfoVar(id);\n'
    s = s + '   }\n'
    s = s + '   return p;\n'
    s = s + '}\n\n'
 
    s = s + 'size_t getDpValue(CrPsParId_t id, void* dest) {\n'
    s = s + '   DpMetaInfoEntry_t* entry;\n'
    s = s + '   entry = getMetaInfo(id);\n'
    s = s + '   if (entry == NULL) {\n'
    s = s + '       reurn 0;\n'
    s = s + '   }\n'
    s = s + '   (void)memcpy(dest, entry->addr, entry->length);\n'
    s = s + '   return entry->length;\n'
    s = s + '}\n\n'
 
    s = s + 'size_t getDpValueEx(CrPsParId_t id, void* dest, size_t* pElementLength, unsigned int* pNElements) {\n'
    s = s + '   DpMetaInfoEntry_t* entry;\n'
    s = s + '   entry = getMetaInfo(id);\n'
    s = s + '   if (entry == NULL) {\n'
    s = s + '       reurn 0;\n'
    s = s + '   }\n'
    s = s + '   (void)memcpy(dest, entry->addr, entry->length);\n'
    s = s + '   *pElementLength = entry->elementLength;\n'
    s = s + '   return entry->length;\n'
    s = s + '}\n\n'

    s = s + 'int setDpValue(CrPsParId_t id, const void* src) {\n'
    s = s + '   DpMetaInfoEntry_t* entry;\n'
    s = s + '   entry = getMetaInfo(id);\n'
    s = s + '   if (entry == NULL) {\n'
    s = s + '       reurn 0;\n'
    s = s + '   }\n'
    s = s + '   (void)memcpy(entry->addr, src, entry->length);\n'
    s = s + '   return entry->length;\n'
    s = s + '}\n\n'

    s = s + 'int setDpValueEx(CrPsParId_t id, const void* src, void** dest, size_t* pElementLength, unsigned int* pNElements) {\n'
    s = s + '   DpMetaInfoEntry_t* entry;\n'
    s = s + '   entry = getMetaInfo(id);\n'
    s = s + '   if (entry == NULL) {\n'
    s = s + '       reurn 0;\n'
    s = s + '   }\n'
    s = s + '   (void)memcpy(entry->addr, src, entry->length);\n'
    s = s + '   *dest = entry->addr;\n'
    s = s + '   *pElementLength = entry->elementLength;\n'
    s = s + '   *pNElements = entry->nElements;\n'
    s = s + '   return entry->length;\n'
    s = s + '}\n\n'

    s = s + 'size_t getDpSize(CrPsParId_t id) {\n'
    s = s + '   DpMetaInfoEntry_t* entry;\n'
    s = s + '   entry = getMetaInfo(id);\n'
    s = s + '   if (entry == NULL) {\n'
    s = s + '       reurn 0;\n'
    s = s + '   }\n'
    s = s + '   return entry->length;\n'
    s = s + '}\n\n'

    s = s + 'size_t getDpParamSize(CrPsParId_t id) {\n'
    s = s + '   DpMetaInfoEntry_t* entry;\n'
    s = s + '   entry = getMetaInfoParam(id);\n'
    s = s + '   if (entry == NULL) {\n'
    s = s + '       reurn 0;\n'
    s = s + '   }\n'
    s = s + '   return entry->length;\n'
    s = s + '}\n\n'

    s = s + 'size_t getDpVarSize(CrPsParId_t id) {\n'
    s = s + '   DpMetaInfoEntry_t* entry;\n'
    s = s + '   entry = getMetaInfoVar(id);\n'
    s = s + '   if (entry == NULL) {\n'
    s = s + '       reurn 0;\n'
    s = s + '   }\n'
    s = s + '   return entry->length;\n'
    s = s + '}\n\n'

    shortDesc = 'Implementation of interface for accessing data pool items.'
    createHeaderFile(dataPoolDir, 'CrPsDp.c', s, shortDesc)


#===============================================================================
# Create the header of the generic data pool component.
def createCrPsDataPoolHeader():
    s = ''
    dataPoolDir = cmdRepSrcDir + '/DataPool'
    if not os.path.isdir(dataPoolDir):
        os.makedirs(dataPoolDir)

    s = s + '#include \"CrPsTypes.h\"\n'
    s = s + '#include \"CrPsConstants.h\"\n'
    s = s + '#include \"CrFwUserConstants.h\"\n'
    s = s + '#include \"CrFwConstants.h\"\n\n'

    s = s + 'enum {\n'
    s = s + '    /* Parameters */\n'
    s = s + '    DpIpParamsLowest = 1,\n'
    i = 1
    for dataItemPar in dataItemPars:
        s = s + '    ' + dataItemPar['name'] + ' = ' + str(i) + ',\n'
        i = i + 1
        mult = getMultiplicity(dataItemPar)[1]
        if mult > 1:
            for index in range(1,mult+1):
                s = s + '    ' + dataItemPar['name'] + '_' + str(index) + ' = ' + str(i) + ',\n'
                i = i +1
    s = s + '    DpIpParamsHighest = ' + str(i-1) + ',\n'
    s = s + '    /* Variables */\n'
    s = s + '    DpIpVarsLowest = ' + str(i)+ ',\n'
    for dataItemVar in dataItemVars:
        s = s + '    ' + dataItemVar['name'] + ' = ' + str(i) + ',\n'
        i = i + 1
        mult = getMultiplicity(dataItemVar)[1]
        if mult > 1:
            for index in range(1,mult+1):
                s = s + '    ' + dataItemVar['name'] + '_' + str(index) + ' = ' + str(i) + ',\n'
                i = i +1
    s = s + '    DpIpVarsHighest = ' + str(i-1) + ',\n'
    s = s[:-2] + '\n};\n\n'

    s = s + writeDoxy(['Get the value of a data pool item by identifier.',
                       '@param id The data pool item identifier',
                       '@param dest The address of the target variable where the value gets copied to.',
                       '@return Number of bytes copied. 0 if id is invalid.'])
    s = s + 'extern size_t getDpValue(CrPsParId_t id, void* dest);\n\n'
    
    s = s + writeDoxy(['Get the value of a data pool item plus meta information by identifier.',
                       '@param id The data pool item identifier',
                       '@param dest The address of the target variable where the value gets copied to.',
                       '@param pElementLength Pointer to where the element size is copied to.',
                       '@param pNElements Pointer to where the number of elements is copied to.',
                       '@return Number of bytes copied. 0 if id is invalid.'])
    s = s + 'extern size_t getDpValueEx(CrPsParId_t id, void* dest, size_t* pElementLength, unsigned int* pNElements);\n\n'

    s = s + writeDoxy(['Set the value of a data pool item by identifier.',
                       '@param id The data pool item identifier',
                       '@param src The address of the source variable where the value gets copied from.',
                       '@return Number of bytes copied. 0 if id is invalid.'])
    s = s + 'extern int setDpValue(CrPsParId_t id, const void* src);\n\n'
    
    s = s + writeDoxy(['Set the value of a data pool item by identifier and get meta information.',
                       '@param id The data pool item identifier',
                       '@param src The address of the target variable where the value gets copied from.',
                       '@param pElementLength Pointer to where the element size is copied to.',
                       '@param pNElements Pointer to where the number of elements is copied to.',
                       '@return Number of bytes copied. 0 if id is invalid.'])
    s = s + 'extern int setDpValueEx(CrPsParId_t id, const void* src, void** dest, ' + \
            'size_t* pElementLength, unsigned int* pNElements);\n\n'

    s = s + writeDoxy(['Get the size of a data pool item by identifier.',
                       '@param id The data pool item identifier',
                       '@return The size of the data pool item. 0 if id is invalid.'])
    s = s + 'extern size_t getDpSize(CrPsParId_t id);\n\n'
    
    s = s + writeDoxy(['Get the size of a data pool parameter by identifier.',
                       '@param id The data pool parameter identifier',
                       '@return The size of the data pool parameter. 0 if id is invalid.'])
    s = s + 'extern size_t getDpParamSize(CrPsParId_t id);\n\n'
    
    s = s + writeDoxy(['Get the size of a data pool variable by identifier.',
                       '@param id The data pool variable identifier',
                       '@return The size of the data pool variable. 0 if id is invalid.'])
    s = s + 'extern size_t getDpVarSize(CrPsParId_t id);\n\n'

    shortDesc = 'Interface for accessing data pool items.'
    createHeaderFile(dataPoolDir, 'CrPsDp.h', s, shortDesc)


#===============================================================================
# Create header files which defines the accessor methods for the packet parameters.
def createCrPsPcktHeader():
    s = ''
    if not os.path.isdir(pcktDir):
        os.makedirs(pcktDir)
    for service in services:
        if service['name'] == 'Hdr':
            continue
        servDirName = cmdRepSrcDir + '/' + service['name']
        if not os.path.isdir(servDirName):
            os.makedirs(servDirName)
        s = ''
        s = s + '#include \"CrPsTypes.h\"\n'
        s = s + '#include \"CrPsPckt.h\"\n\n'

        s = s + writeDoxy(['Constants defining:',
                           '- For statically defined packets: the full length',
                           '- For packets with groups of dynamic size: length of header + length of CRC field',
                           '- For parent packets: length of the parent part of a packet',
                           'Constant name format is: LEN_<domain>_<basePacketName>_<discriminant> \n'])
        
        for packet in servToPckts[getSpecItemName(service)]:
            s = s + writeDoxy(['Length constant for packet '+packet['name']])
            s = s + '#define LEN_' + service['name'].upper() + '_'+packet['name'].upper() + \
                ' ' + str(getPcktLen(packet)) + '\n\n'
            for derPacket in pcktToDerPckts[getSpecItemName(packet)]:
                s = s + writeDoxy(['Length constant for derived packet '+derPacket['name']])
                disc = getDiscVal(derPacket)[1]
                s = s + '#define LEN_' + service['name'].upper() + '_'+derPacket['name'].upper() + \
                    '_' + disc.upper() + ' ' + str(getPcktLen(derPacket)) + '\n\n'
         
        for packet in servToPckts[getSpecItemName(service)]:
            derPckts = pcktToDerPckts[getSpecItemName(packet)]
            nDerPckts = len(derPckts)
            if nDerPckts == 0:
                continue
            s = s +  writeDoxy(['Number of derived packets in packet '+getSpecItemName(packet)])
            s = s + '#define N_OF_DER_PCKT_' + service['name'].upper() + '_' + \
                packet['name'].upper() + ' ' + str(nDerPckts) + '\n'
            s = s +  writeDoxy(['List of discriminants for derived packets of packet '+ \
                getSpecItemName(packet)])
            s = s + '#define LIST_OF_DER_PCKT_' + service['name'].upper() + '_' + \
                packet['name'].upper() + ' {'
            for derPacket in derPckts:
                s = s + service['name'].upper() + '_' + derPacket['name'].upper() + ', '
            s = s[:-2] + '}\n\n'
            
        for packet in servToPckts[getSpecItemName(service)]:
            s = s +  writeDoxy(['Structure for packet '+getSpecItemName(packet)])
            s = s + 'typedef struct __attribute__((packed)) _'+packet['name']+'_t {\n'
            s = s + '    /** Packet header */\n'
            s = s + '    TmHeader_t Header;\n'
            groupSize = 0
            indent = '    '
            groupSizePar = None
            for par in pcktToPcktPars[getSpecItemName(packet)]:
                if groupSize > 0:
                    groupSize = groupSize - 1
                    indent = '        '
                s = s + indent + '/** ' + par['title'] + ' */\n'
                s = s + indent + getPcktParType(par) + ' ' + par['name'] + ';\n'
                if int(par['n2']) > 0:  # Parameter is not a group size
                    groupSize = int(par['n2'])
                    s = s + indent + 'struct __attribute__((packed)) _{\n'
                    groupSizePar = par
                if groupSize == 0 and groupSizePar != None:
                    indent = '    '
                    s = s + '} ' + groupSizePar['name'] + '_[1];\n' 
                    groupSizePar = None
                    
            s = s + '} ' + packet['name'] + '_t;\n\n' 
            derPckts = pcktToDerPckts[getSpecItemName(packet)]
            nDerPckts = len(derPckts)
            for derPckt in derPckts:
                derPcktName = '_' + getSpecItemName(packet) + '_' + derPckt['name']
                s = s +  writeDoxy(['Structure for derived packet '+derPcktName])
                s = s + 'typedef struct __attribute__((packed)) '+derPcktName+'_t {\n'
                s = s + '    /** Packet header */\n'
                s = s + '    TmHeader_t Header;\n'
                for par in pcktToPcktPars[getSpecItemName(packet)]:
                    s = s + '    /** ' + par['title'] + '(from parent packet) */\n'
                    s = s + '   ' + getPcktParType(par) + ' ' + par['name'] + ';\n'
                for par in derPcktToPcktPars[getSpecItemName(derPckt)]:
                    s = s + '    /** ' + par['title'] + ' */\n'
                    s = s + '   ' + getPcktParType(par) + ' ' + par['name'] + ';\n'
                s = s + '} ' + derPcktName + '_t;\n\n' 

        for packet in servToPckts[getSpecItemName(service)]:
            groupSize = 0
            groupSizePar = None
            for par in pcktToPcktPars[getSpecItemName(packet)]:
                if groupSize > 0:
                    groupSize = groupSize - 1
                if int(par['n2']) > 0:  # Parameter is not a group size
                    groupSize = int(par['n2'])
                    groupSizePar = par
                s = s + writePcktParGetterFunction(par['name'], 
                                                   packet['name'], 
                                                   service['name'], 
                                                   getPcktParType(par),
                                                   groupSizePar)
                s = s + writePcktParSetterFunction(par['name'], 
                                                   packet['name'], 
                                                   service['name'], 
                                                   getPcktParType(par),
                                                   groupSizePar)
                if groupSize == 0:
                    groupSizePar = None
            groupSizePar = None     # We assume that there are no groups in derived packets
            for derPckt in pcktToDerPckts[getSpecItemName(packet)]:
                for par in derPcktToPcktPars[getSpecItemName(derPckt)]:
                    s = s + writePcktParGetterFunction(par['name'], 
                                                       packet['name'], 
                                                       service['name'], 
                                                       getPcktParType(par),
                                                       groupSizePar)
                    s = s + writePcktParSetterFunction(par['name'], 
                                                       packet['name'], 
                                                       service['name'], 
                                                       getPcktParType(par),
                                                       groupSizePar)
            
        headerFileName = 'CrPsPckt' + service['name']
        shortDesc = 'Header file for accessor methods for packets in service ' + service['name'] + \
                    ' (' + service['title'] + ').'
        createHeaderFile(pcktDir, headerFileName + '.h', s, shortDesc)


#===============================================================================
# Create header files for modules implementing OutComponents.
def createCrPsOutCmpHeaders():
    for service in services:
        if service['name'] != 'Hdr':
            servDirName = cmdRepSrcDir + '/' + service['name']
            if not os.path.isdir(servDirName):
                os.makedirs(servDirName)
 
    # Each element of this tuple contains:
    # - The name of an OutComponent action or check
    # - The name of attribute in the OutComponent specItem where the spec of the 
    #   action or check is stored
    # - The return type of the action or check
    # - The type of the argument of the action or check
    # - The name of the argument of the action or check
    actionsAndChecks = [('Enable Check', 't1', 'CrFwBool_t', 'FwSmDesc_t', 'smDesc'),
                        ('Ready Check', 't2', 'CrFwBool_t', 'FwSmDesc_t', 'smDesc'),
                        ('Repeat Check', 't3', 'CrFwBool_t', 'FwSmDesc_t', 'smDesc'),
                        ('Update Action', 't5', 'void', 'FwSmDesc_t', 'smDesc')]
    for outComponent in outComponents:
        s = ''
        s = s + '#include \"CrPsConstants.h\"\n'
        s = s + '#include \"CrPsTypes.h\"\n\n'
        s = s + '#include \"CrFwCore.h\"\n'
        s = s + '#include \"CrFwConstants.h\"\n\n'
        headerFileName = 'CrPsOutCmp' + getServName(outComponent) + outComponent['name'][:-6] + 'Rep'
        typeAndSubType = getTypeAndSubType(outComponent)
        for actionOrCheck in actionsAndChecks:
            actionOrCheckSpec = outComponent[actionOrCheck[1]]
            if isDefault(actionOrCheckSpec) or \
               (getSameAs(actionOrCheckSpec, outComponent, actionOrCheck[0]) != ''):
                continue
            commentFirstLine = actionOrCheck[0] + ' of TM(' + typeAndSubType[0] + \
                               ',' + typeAndSubType[1] + ') ' + outComponent['name'] + \
                               ' (' + outComponent['title'] + ').'
            functionName = headerFileName + actionOrCheck[0].replace(' ','')
            s = s + writeDoxy([commentFirstLine, actionOrCheckSpec])
            s = s + actionOrCheck[2] + ' ' + functionName + '(' + \
                actionOrCheck[3] + ' ' + actionOrCheck[4] + ')\n\n'
        
        servDirName = cmdRepSrcDir + '/' + getServName(outComponent)
        shortDesc = 'Header file for module implementing TM(' + typeAndSubType[0] + \
                    ',' + typeAndSubType[1] + ') ' + outComponent['name'] + '.'
        createHeaderFile(servDirName, headerFileName + '.h', s, shortDesc)
        
    return 

#===============================================================================
# Create header files for modules implementing InCommands.
def createCrPsInCmdHeaders():
    for service in services:
        if service['name'] != 'Hdr':
            servDirName = cmdRepSrcDir + '/' + service['name']
            if not os.path.isdir(servDirName):
                os.makedirs(servDirName)
 
    # Each element of this tuple contains:
    # - The name of an InCommand action or check
    # - The name of attribute in the InCommand specItem where the spec of the 
    #   action or check is stored
    # - The return type of the action or check
    # - The type of the argument of the action or check
    # - The name of the argument of the action or check
    actionsAndChecks = [('Validity Check', 'value', 'CrFwBool_t', 'FwPrDesc_t', 'prDesc'),
                        ('Ready Check', 't1', 'CrFwBool_t', 'FwSmDesc_t', 'smDesc'),
                        ('Start Action', 't2', 'void', 'FwSmDesc_t', 'smDesc'),
                        ('Progress Action', 't3', 'void', 'FwSmDesc_t', 'smDesc'),
                        ('Termination Action', 't4', 'void', 'FwSmDesc_t', 'smDesc'),
                        ('Abort Action', 't5', 'void', 'FwSmDesc_t', 'smDesc')]
    for inCommand in inCommands:
        s = ''
        s = s + '#include \"CrPsConstants.h\"\n'
        s = s + '#include \"CrPsTypes.h\"\n\n'
        s = s + '#include \"CrFwCore.h\"\n'
        s = s + '#include \"CrFwConstants.h\"\n\n'
        headerFileName = 'CrPsInCmd' + getServName(inCommand) + inCommand['name'][:-5] + 'Cmd'
        typeAndSubType = getTypeAndSubType(inCommand)
        for actionOrCheck in actionsAndChecks:
            actionOrCheckSpec = inCommand[actionOrCheck[1]]
            if isDefault(actionOrCheckSpec) or \
               (getSameAs(actionOrCheckSpec, inCommand, actionOrCheck[0]) != ''):
                continue
            commentFirstLine = actionOrCheck[0] + ' of TC(' + typeAndSubType[0] + \
                               ',' + typeAndSubType[1] + ') ' + inCommand['name'] + \
                               ' (' + inCommand['title'] + ').'
            functionName = headerFileName + actionOrCheck[0].replace(' ','')
            s = s + writeDoxy([commentFirstLine, actionOrCheckSpec])
            s = s + actionOrCheck[2] + ' ' + functionName + '(' + \
                actionOrCheck[3] + ' ' + actionOrCheck[4] + ')\n\n'
                
        servDirName = cmdRepSrcDir + '/' + getServName(inCommand)
        shortDesc = 'Header file for module implementing TC(' + typeAndSubType[0] + \
                    ',' + typeAndSubType[1] + ') ' + inCommand['name'] + '.'
        createHeaderFile(servDirName, headerFileName + '.h', s, shortDesc)
    
    return 
            

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
        
    shortDesc = 'Definition of the constants for the OutRegistry component.'
    createHeaderFile(configDir, 'CrFwOutRegistryUserPar.h', s, shortDesc)
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
            
    shortDesc = 'Definition of constants representing supported service types and sub-types.'
    createHeaderFile(configDir, 'CrPsServTypeId.h', s, shortDesc)
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

    shortDesc = 'Definition of PUS Extension types (types whose name starts with \'CrPs\').'            
    createHeaderFile(configDir, 'CrPsTypes.h', s, shortDesc)
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
        
    shortDesc = 'Definition of the constants for the InFactory component.'
    createHeaderFile(configDir, 'CrFwInFactoryUserPar.h', s, shortDesc)
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
        
    shortDesc = 'Definition of the constants for the OutFactory component.'
    createHeaderFile(configDir, 'CrFwOutFactoryUserPar.h', s, shortDesc)
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
            if row['cat'] == 'DataItem' and row['p_kind'] == 'PAR':
                dataItemPars.append(row)
            if row['cat'] == 'DataItem' and row['p_kind'] == 'VAR':
                dataItemVars.append(row)
            if row['cat'] == 'DataItem' and row['p_kind'] == 'CNS':
                constToSpecItem[row['name']] = row
            if row['cat'] == 'DataItem':
                dataItems.append(row)
            domNameToSpecItem[row['domain']+':'+row['name']] = row
    
    # Build cross-tables
    buildCrossTable(enumTypesToEnumValues, 'EnumType', 'EnumValue', 's_link')
    buildCrossTable(enumValToDerPckts, 'EnumValue', 'DerPacket', 'p_link')
    buildCrossTable(pcktToPcktPars, 'Packet', 'PacketPar', 'p_link')
    buildCrossTable(derPcktToPcktPars, 'DerPacket', 'PacketPar', 'p_link')
    buildCrossTable(pcktToDerPckts, 'Packet', 'DerPacket', 's_link')
    buildCrossTable(servToPckts, 'Service', 'Packet', 'p_link')
    
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
    createCrPsOutCmpHeaders()
    createCrPsInCmdHeaders()
    createCrPsPcktHeader()
    createCrPsDataPoolHeader()
    createCrPsDataPoolBody()
    
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

