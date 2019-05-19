#!/bin/bash
# This script creates a delivery file for the PUS Extension of the CORDET Framework.
# The script should be called from the /cordetfw-pus directory.
# The delivery file is created in a directory called /CordetFW_PusExt_DeliveryFile.
#
#====================================================================================

VERS_PX="0_2"
VERS_UM="0_2"
VERS_VR="0_2"
VERS_IC="0_2"

# Remove the delivery file directory (if it exists)
if [[ -d CordetFW_PusExt_DeliveryFile ]]; then
    echo "Removing delivery file directory"
    rm -rf CordetFW_PusExt_DeliveryFile
fi

# Create the delivery file directory
echo "Creating delivery file directory and sub-directories"
mkdir CordetFW_PusExt_DeliveryFile
mkdir CordetFW_PusExt_DeliveryFile/log
mkdir CordetFW_PusExt_DeliveryFile/doc
mkdir CordetFW_PusExt_DeliveryFile/lib
mkdir CordetFW_PusExt_DeliveryFile/lib/cordetfw
mkdir CordetFW_PusExt_DeliveryFile/lib/cordetfw/lib
mkdir CordetFW_PusExt_DeliveryFile/lib/cordetfw/lib/fwprofile

# Copying source directories, Makefile and scripts
echo "Copying source directories"
cp -R src CordetFW_PusExt_DeliveryFile/
cp -R lib/cordetfw/src CordetFW_PusExt_DeliveryFile/lib/cordetfw/
cp -R lib/cordetfw/LICENSE CordetFW_PusExt_DeliveryFile/lib/cordetfw/
cp -R lib/cordetfw/lib/fwprofile/src CordetFW_PusExt_DeliveryFile/lib/cordetfw/lib/fwprofile/
cp -R lib/cordetfw/lib/fwprofile/LICENSE CordetFW_PusExt_DeliveryFile/lib/cordetfw/lib/fwprofile/
cp -R tests CordetFW_PusExt_DeliveryFile/

echo "Copying Makefile and licence file"
cp Makefile CordetFW_PusExt_DeliveryFile/
cp DoxygenConfig.txt CordetFW_PusExt_DeliveryFile/
cp LICENSE CordetFW_PusExt_DeliveryFile/
cp ImportGenProducts.sh CordetFW_PusExt_DeliveryFile/
cp MakeDeliveryFile.sh CordetFW_PusExt_DeliveryFile/

# Create and copy Doxygen documentation
echo "Creating Doxygen documentation"
doxygen DoxygenConfig.txt &> log/Doxygen.log
cp -R doc/html CordetFW_PusExt_DeliveryFile/doc

# Generate traceability matrices
echo "Generating traceability matrices"
cd doc/vr
python3 GenListOfVerifyItems.py
cd ../..

# Build the Test Suite and the Test Program
echo "Building test suite"
make -f Makefile clean
make -f Makefile test &> ./log/TestSuiteBuild.log
read -p "Press enter to continue"
make -f Makefile run-test 2>&1 | tee ./log/TestSuiteRun.log
echo "Running test suite with valgrind"
make -f Makefile run-test-valgrind 2>&1 | tee log/TestSuiteRunWithValgrind.log

# Generate coverage information
echo "Generating coverage information"
make -f Makefile gen-lcov &> log/TestSuiteLcov.log
cp -R lcov CordetFW_PusExt_DeliveryFile/doc

# Generate the log files with the software metrics
echo "Generating metrics information"
lizard -x "src/ProtobufImpl/*" -C 12 src > log/Metrics.log
lizard -x "src/DataPool/*" -x "src/Pckt/*" -C 10 src > log/MetricsNonEditor.log 

# Ask user to perform scan-build
echo "Run scan-build (do make clean first and then scan-build -o log make test)"
read -p "Press enter to continue"

# Copy all log files
echo "Copying log files"
cp -R log CordetFW_PusExt_DeliveryFile/

# Compile the latex files (twice to process all cross-references)
cd doc/pus
if [ ! -f "../rel/PusExtension_i${VERS_PX}.pdf" ]
then
    echo "Compiling Spec"
    pdflatex -interaction=nonstopmode PusExtension.tex > ../../log/PusExtension.log
fi  
  
cd ../vr
if [ ! -f "../rel/PusExtensionVR_i${VERS_VR}.pdf" ]
then
    echo "Compiling VR"
    pdflatex -interaction=nonstopmode PusExtensionVR.tex > ../../log/PusExtensionVR.log
fi

cd ../um
if [ ! -f "../um/PusExtensionUM_i${VERS_UM}.pdf" ]
then
    echo "Compiling UM"
    pdflatex -interaction=nonstopmode PusExtensionUM.tex > ../../log/PusExtensionUM.log
fi

cd ../icd
if [ ! -f "../rel/PusExtensionICD_i${VERS_IC}.pdf" ]
then
    echo "Compiling REL"
    pdflatex -interaction=nonstopmode PusExtensionICD.tex > ../../log/PusExtensionICD.log
fi

cd ../pus
if [ ! -f "../rel/PusExtension_i${VERS_PX}.pdf" ]
then
    echo "Compiling Spec"
    pdflatex -interaction=nonstopmode PusExtension.tex > ../../log/PusExtension.log
fi  
  
cd ../vr
if [ ! -f "../rel/PusExtensionVR_i${VERS_VR}.pdf" ]
then
    echo "Compiling VR"
    pdflatex -interaction=nonstopmode PusExtensionVR.tex > ../../log/PusExtensionVR.log
fi

cd ../um
if [ ! -f "../um/PusExtensionUM_i${VERS_UM}.pdf" ]
then
    echo "Compiling UM"
    pdflatex -interaction=nonstopmode PusExtensionUM.tex > ../../log/PusExtensionUM.log
fi

cd ../icd
if [ ! -f "../rel/PusExtensionICD_i${VERS_IC}.pdf" ]
then
    echo "Compiling REL"
    pdflatex -interaction=nonstopmode PusExtensionICD.tex > ../../log/PusExtensionICD.log
fi
cd ../..

echo "Copying the library support documents"
if [ ! -f "doc/rel/PusExtension_i${VERS_PX}.pdf" ]
then
    cp ./doc/pus/PusExtension.pdf doc/rel/PusExtension_i${VERS_PX}.pdf
fi
cp doc/rel/PusExtension_i${VERS_PX}.pdf CordetFW_PusExt_DeliveryFile/doc/PusExtension.pdf

if [ ! -f "doc/rel/PusExtensionUM_i${VERS_UM}.pdf" ]
then
    cp ./doc/um/PusExtensionUM.pdf doc/rel/PusExtensionUM_i${VERS_UM}.pdf
fi
cp doc/rel/PusExtensionUM_i${VERS_UM}.pdf CordetFW_PusExt_DeliveryFile/doc/PusExtensionUM.pdf

if [ ! -f "doc/rel/PusExtensionVR_i${VERS_VR}.pdf" ]
then
    cp ./doc/vr/PusExtensionVR.pdf doc/rel/PusExtensionVR_i${VERS_VR}.pdf
fi
cp doc/rel/PusExtensionVR_i${VERS_VR}.pdf CordetFW_PusExt_DeliveryFile/doc/PusExtensionVR.pdf

if [ ! -f "doc/rel/PusExtensionICD_i${VERS_IC}.pdf" ]
then
    cp ./doc/icd/PusExtensionICD.pdf doc/rel/PusExtensionICD_i${VERS_IC}.pdf
fi
cp doc/rel/PusExtensionICD_i${VERS_IC}.pdf CordetFW_PusExt_DeliveryFile/doc/PusExtensionICD.pdf











