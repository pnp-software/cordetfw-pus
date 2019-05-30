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
# Example: ./ImportGenProducts.sh -f -d="/home/ap/Downloads"
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
    cp $EDITOR_PATH/pck/CrPsPckt*.h ./src/Pckt
fi

# Copy the files with the definition of the types and of the constants
if [ "$EDITOR" == "YES" ]
  then
    echo "--Copy the files with the definition of the types and of the constants--"
    cp $EDITOR_PATH/pck/CrPsConstants.h ./tests/PusConfig
    cp $EDITOR_PATH/pck/CrPsTypes.h ./tests/PusConfig
    cp $EDITOR_PATH/pck/CrPsServTypeId.h ./tests/PusConfig
fi

# Copy the files for the PUS Definition Documents
if [ "$EDITOR" == "YES" ]
  then
    echo "--Copy the files for the PUS Definition Document--"
    cp $EDITOR_PATH/spec/CrPsSpec.tex ./doc/pus/GeneratedTables
    cp $EDITOR_PATH/icd/PUSExtensionCrPsEvtIdt.csv ./doc/pus/GeneratedTables
    cp $EDITOR_PATH/icd/PUSExtensionCrPsFailCodet.csv ./doc/pus/GeneratedTables
    cp $EDITOR_PATH/icd/PUSExtensionServiceOverview.csv ./doc/pus/GeneratedTables
    cp $EDITOR_PATH/icd/PUSExtensionServices.csv ./doc/pus/GeneratedTables

    echo "--Copy the files for the PUS ICD--"
    cp $EDITOR_PATH/icd/*.tex ./doc/icd/GeneratedTables
fi
if [ "$CONSTANT" == "YES" ]
  then
    echo "--Copy the csv constant definition file--"
    cp $EDITOR_PATH/Constants.csv ./doc/pus/GeneratedTables
fi
if [ "$DATAPOOL" == "YES" ]
  then
    echo "--Copy the csv datapool definition file--"
    cp $EDITOR_PATH/Datapool.csv ./doc/pus/GeneratedTables
fi

# Copy the files for the data pool
if [ "$EDITOR" == "YES" ]
  then
    echo "--Copy the files for the data pool--"
    rsync $EDITOR_PATH/dp/*.* ./src/DataPool --exclude CrPsConstants.h --exclude CrPsTypes.h
fi

# Copy the headers of the files which define the commands and reports
if [ "$EDITOR" == "YES" ]
  then
    echo "--Copy the files which define the commands and reports--"
    cp $EDITOR_PATH/cfw/Ver/*.h ./src/Ver
    cp $EDITOR_PATH/cfw/Hk/*.h ./src/Hk
    cp $EDITOR_PATH/cfw/Evt/*.h ./src/Evt
    cp $EDITOR_PATH/cfw/Mon/*.h ./src/Mon
    cp $EDITOR_PATH/cfw/Lpt/*.h ./src/Lpt
    cp $EDITOR_PATH/cfw/Tst/*.h ./src/Tst
    cp $EDITOR_PATH/cfw/Scd/*.h ./src/Scd
    cp $EDITOR_PATH/cfw/Dum/*.h ./src/Dum
fi

# Copy the files which define the configuration of the CORDET Framework
if [ "$EDITOR" == "YES" ]
  then
    echo "--Copy the files which define the configuration of the CORDET Framework--"
    cp $EDITOR_PATH/cfw/PusConfig/*.h ./tests/PusConfig
fi

# Copy the code generated by the FW Profile Editor
if [ "$FWPROFILE" == "YES" ]
  then
    echo "--Copy the code generated by the FW Profile Editor--"
    cp $EDITOR_PATH/CrPsMonFncPr/CrPsMonFncPr.h ./src/Mon
    cp $EDITOR_PATH/CrPsMonFncPr/CrPsMonFncPr.c ./src/Mon
    cp $EDITOR_PATH/CrPsCmd17s3Prgr/CrPsCmd17s3Prgr.h ./src/Tst
    cp $EDITOR_PATH/CrPsCmd17s3Prgr/CrPsCmd17s3Prgr.c ./src/Tst
    cp $EDITOR_PATH/CrPsCmd17s3Start/CrPsCmd17s3Start.h ./src/Tst
    cp $EDITOR_PATH/CrPsCmd17s3Start/CrPsCmd17s3Start.c ./src/Tst
    cp $EDITOR_PATH/CrPsCmdPrgrFail/CrPsCmdPrgrFail.c ./src/Ver
    cp $EDITOR_PATH/CrPsCmdPrgrSucc/CrPsCmdPrgrSucc.c ./src/Ver
    cp $EDITOR_PATH/CrPsCmdPrg*/CrPsCmdPrg*.h ./src/Ver
    cp $EDITOR_PATH/CrPsCmdVerFail/CrPsCmdVerFail.c ./src/Ver
    cp $EDITOR_PATH/CrPsCmdVerSucc/CrPsCmdVerSucc.c ./src/Ver
    cp $EDITOR_PATH/CrPsCmdVer*/CrPsCmdVer*.h ./src/Ver
    cp $EDITOR_PATH/CrPsPcktReroutingFail/CrPsPcktReroutingFail.c ./src/Ver
    cp $EDITOR_PATH/CrPsPcktReroutingFail/CrPsPcktReroutingFail.h ./src/Ver
    cp $EDITOR_PATH/CrPsDataPool/CrPsDataPool.c ./src/DataPool
    cp $EDITOR_PATH/CrPsDataPool/CrPsDataPool.h ./src/DataPool
    
    cp $EDITOR_PATH/CrPs*/*.png ./doc/images
    cp $EDITOR_PATH/CrPs*/*.json ./doc/json
fi


















