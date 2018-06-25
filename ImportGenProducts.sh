#!/bin/bash
# This script imports the following items into the cordetfw-pus:
# - The code outputs generated by the CORDET Editor
# - The data pool csv description file generated by the CORDET Editor
# - The constants csv description file generated by the CORDET Editor
# - The code generated by the FW Profile Editor
#
# The script assumes that the above outputs have been placed or expanded
# into a directory which passed to the script as an argument through the
# -d option.
#
# The script makes certain assumptions about the structure of the cordetfw-pus
# directory structure. If this changes, the script may have to be adapted.
#
# The script must be run from the top-level directory of the cordetfw-pus project
# (e.g. /home/Projects/cordetfw-pus).
#
# Example: ./ImportCordetEditorOutput.sh -f -d="/home/ap/Downloads"
#
#====================================================================================

showHelp() {
    echo "Options: "
    echo "-c, --constant         process the csv constant description file"
    echo "-p, --datapool         process the csv data pool description file"
    echo "-e, --editor           process the code generated by the CORDET Editor"
    echo "-f, --fwprofile        process the code generated by the FW Profile Editor"
    echo "-d=, --dir=            path to directory holding inputs, defaults to current directory"
    echo "-h, --help             this help text"
    exit 0
}

# Parsing of command line parameters
for i in "$@"
do
case $i in
    -d=*|--dir=*)
    EDITOR_PATH=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
    ;;
    -h|--help)
    showHelp
    ;;
    -c|--constant)
    CONSTANT="YES"
    ;;
    -p|--datapool)
    DATAPOOL="YES"
    ;;
    -f|--fwprofile)
    FWPROFILE="YES"
    ;;
    -e|--editor)
    EDITOR="YES"
    ;;
esac
done

if [ "$EDITOR_PATH" == "" ]
then
    EDITOR_PATH="."
fi

# Copy the files holding the packet accessor functions
if [ "$EDITOR" == "YES" ]
  then
    echo "--Copy the files holding the packet accessor functions--"
    cp $EDITOR_PATH/pck/CrPsPkt.h ./tests/PusConfig
    #cp $EDITOR_PATH/pck/CrPsPktVer.h ./src/VerService
    cp $EDITOR_PATH/pck/CrPsPktTst.h ./src/TstService
    #cp $EDITOR_PATH/pck/CrPsPktLpt.h ./src/LptService
    #cp $EDITOR_PATH/pck/CrPsPktHk.h ./src/HkService
fi

# Copy the files with the definition of the types and of the constants
if [ "$EDITOR" == "YES" ]
  then
    echo "--Copy the files with the definition of the types and of the constants--"
    cp $EDITOR_PATH/pck/CrPsConstants.h ./tests/PusConfig
    cp $EDITOR_PATH/pck/CrPsTypes.h ./tests/PusConfig
fi

# Copy the files for the PUS Definition Document
if [ "$EDITOR" == "YES" ]
  then
    echo "--Copy the files for the PUS Definition Document--"
    cp $EDITOR_PATH/spec/CrPsSpec.tex ./doc/pus/GeneratedTables
    cp $EDITOR_PATH/icd/PUSExtensionCrPsErrRepCodet.csv ./doc/pus/GeneratedTables
    cp $EDITOR_PATH/icd/PUSExtensionCrPsEvtIdt.csv ./doc/pus/GeneratedTables
    cp $EDITOR_PATH/icd/PUSExtensionCrPsFailCodet.csv ./doc/pus/GeneratedTables
    cp $EDITOR_PATH/icd/PUSExtensionServiceOverview.csv ./doc/pus/GeneratedTables
    cp $EDITOR_PATH/icd/PUSExtensionServices.csv ./doc/pus/GeneratedTables
fi
if [ "$CONSTANT" == "YES" ]
  then
    echo "--Copy the csv constant definition file--"
    cp $EDITOR_PATH/Constants.csv ./doc/pus/GeneratedTables
fi
if [ "$DATAPOOL" == "YES" ]
  then
    cp $EDITOR_PATH/Datapool.csv ./doc/pus/GeneratedTables
fi

# Copy the files for the data pool
if [ "$EDITOR" == "YES" ]
  then
    echo "--Copy the files for the data pool--"
    cp $EDITOR_PATH/dp/*.h ./src/DataPool
    cp $EDITOR_PATH/dp/*.c ./src/DataPool
    #cp $EDITOR_PATH/dp/CrPsDpVer.* ./src/DataPool
    #cp $EDITOR_PATH/dp/CrPsDpTst.* ./src/DataPool
    #cp $EDITOR_PATH/dp/CrPsDpLpt.* ./src/DataPool
    #cp $EDITOR_PATH/dp/CrPsDpHk.* ./src/DataPool
    #cp $EDITOR_PATH/dp/CrPsDpTypes.h ./src/DataPool
    #cp $EDITOR_PATH/dp/CrPsDp.* ./src/DataPool
fi

# Copy the files which define the commands and reports
if [ "$EDITOR" == "YES" ]
  then
    echo "--Copy the files which define the commands and reports--"
    cp $EDITOR_PATH/cfw/spec/CrPsVer*.h ./src/VerService
    cp $EDITOR_PATH/cfw/spec/CrPsTst*.h ./src/TstService
    cp $EDITOR_PATH/cfw/spec/CrPsLpt*.h ./src/LptService
    cp $EDITOR_PATH/cfw/spec/CrPsHk*.h ./src/HkService
fi

# Copy the files which define the configuration of the CORDET Framework
if [ "$EDITOR" == "YES" ]
  then
    echo "--Copy the files which define the configuration of the CORDET Framework--"
    cp $EDITOR_PATH/cfw/config/*.h ./tests/PusConfig
fi

# Copy the code generated by the FW Profile Editor
if [ "$FWPROFILE" == "YES" ]
  then
    echo "--Copy the code generated by the FW Profile Editor--"
    cp $EDITOR_PATH/CrPsCmd17s3Prgr/CrPsCmd17s3Prgr.h ./src/TstService
    cp $EDITOR_PATH/CrPsCmd17s3Prgr/CrPsCmd17s3Prgr.c ./src/TstService
    cp $EDITOR_PATH/CrPsCmd17s3Start/CrPsCmd17s3Start.h ./src/TstService
    cp $EDITOR_PATH/CrPsCmd17s3Start/CrPsCmd17s3Start.c ./src/TstService
    cp $EDITOR_PATH/CrPs*/*.png ./doc/images
fi


















