#!/bin/bash
# This script creates a delivery file for the TS Communication Library.
# The script should be called from the /RocheTSIF directory.
# The delivery file is created in a directory called /TsComLib_DeliveryFile.
#
#====================================================================================

VERS_UM="1_2"
VERS_USP="1_2"
VERS_SVR="1_1"
VERS_KA="1_1"
VERS_REL="1_1"

# Remove the delivery file directory (if it exists)
if [[ -d TsComLib_DeliveryFile ]]; then
    echo "Removing delivery file directory"
    rm -rf TsComLib_DeliveryFile
fi

# Create the delivery file directory
echo "Creating delivery file directory and sub-directories"
mkdir TsComLib_DeliveryFile
mkdir TsComLib_DeliveryFile/log
mkdir TsComLib_DeliveryFile/docs
mkdir TsComLib_DeliveryFile/docs/int
mkdir TsComLib_DeliveryFile/docs/int/common
mkdir TsComLib_DeliveryFile/docs/int/doxygen
mkdir TsComLib_DeliveryFile/docs/int/fwprofile
mkdir TsComLib_DeliveryFile/docs/int/images
mkdir TsComLib_DeliveryFile/docs/int/json
mkdir TsComLib_DeliveryFile/docs/int/octave
mkdir TsComLib_DeliveryFile/docs/int/rel
mkdir TsComLib_DeliveryFile/docs/int/svr
mkdir TsComLib_DeliveryFile/docs/int/um
mkdir TsComLib_DeliveryFile/docs/int/usp
mkdir TsComLib_DeliveryFile/docs/int/keepalive
mkdir TsComLib_DeliveryFile/docs/rel
mkdir TsComLib_DeliveryFile/lib
mkdir TsComLib_DeliveryFile/lib/fwprofile

# Copying source directories, Makefile and scripts
echo "Copying source directories"
cp -R src TsComLib_DeliveryFile/
cp -R lib/fwprofile/src TsComLib_DeliveryFile/lib/fwprofile/
cp -R lib/fwprofile/LICENSE TsComLib_DeliveryFile/lib/fwprofile/
cp -R test TsComLib_DeliveryFile/
echo "Copying document directories"
cp -R docs/int/common TsComLib_DeliveryFile/docs/int
cp -R docs/int/doxygen TsComLib_DeliveryFile/docs/int
cp -R docs/int/fwprofile TsComLib_DeliveryFile/docs/int
cp -R docs/int/images TsComLib_DeliveryFile/docs/int
cp -R docs/int/json TsComLib_DeliveryFile/docs/int
cp -R docs/int/octave TsComLib_DeliveryFile/docs/int

cp -R docs/int/rel/*.tex TsComLib_DeliveryFile/docs/int/rel/
cp -R docs/int/rel/*.png TsComLib_DeliveryFile/docs/int/rel/
cp -R docs/int/rel/*.cls TsComLib_DeliveryFile/docs/int/rel/
cp -R docs/int/rel/*.csv TsComLib_DeliveryFile/docs/int/rel/

cp -R docs/int/svr/*.tex TsComLib_DeliveryFile/docs/int/svr/
cp -R docs/int/svr/*.cls TsComLib_DeliveryFile/docs/int/svr/
cp -R docs/int/svr/*.png TsComLib_DeliveryFile/docs/int/svr/
cp -R docs/int/svr/*.csv TsComLib_DeliveryFile/docs/int/svr/
cp -R docs/int/svr/*.py TsComLib_DeliveryFile/docs/int/svr/

cp -R docs/int/um/*.tex TsComLib_DeliveryFile/docs/int/um/
cp -R docs/int/um/*.png TsComLib_DeliveryFile/docs/int/um/
cp -R docs/int/um/*.cls TsComLib_DeliveryFile/docs/int/um/

cp -R docs/int/usp/*.tex TsComLib_DeliveryFile/docs/int/usp/
cp -R docs/int/usp/*.cls TsComLib_DeliveryFile/docs/int/usp/
cp -R docs/int/usp/*.png TsComLib_DeliveryFile/docs/int/usp/
cp -R docs/int/usp/*.csv TsComLib_DeliveryFile/docs/int/usp/
cp -R docs/int/usp/*.feature TsComLib_DeliveryFile/docs/int/usp/

cp -R docs/int/keepalive/*.tex TsComLib_DeliveryFile/docs/int/keepalive/
cp -R docs/int/keepalive/*.cls TsComLib_DeliveryFile/docs/int/keepalive/
cp -R docs/int/keepalive/*.png TsComLib_DeliveryFile/docs/int/keepalive/

echo "Copying Makefile and scripts"
cp Makefile TsComLib_DeliveryFile/
cp DoxygenConfig.txt TsComLib_DeliveryFile/
cp GenTraceabilityMatrices.sh TsComLib_DeliveryFile/
cp ImportGenProducts.sh TsComLib_DeliveryFile/
cp MakeDeliveryFile.sh TsComLib_DeliveryFile/
cp ProcessCFiles.py TsComLib_DeliveryFile/

# Insert the "Extern C" declaration in all C-files
echo "Inserting Extern-C Declaration in C Files"
python ProcessCFiles.py

# Create and copy Doxygen documentation
echo "Creating Doxygen documentation"
doxygen DoxygenConfig.txt &> log/Doxygen.log
cp -R docs/html TsComLib_DeliveryFile/docs

# Generate traceability matrices
echo "Generating traceability matrices"
./GenTraceabilityMatrices.sh

# Build the Test Suite and the Test Program
echo "Building test suite"
make -f Makefile clean
make -f Makefile test &> log/TestSuiteBuild.log
echo "Running test suite (this takes a few minutes)"
sudo make -f Makefile run-test 2>&1 | tee log/TestSuiteRun.log
echo "Running test suite with valgrind (this takes a few minutes)"
sudo make -f Makefile run-test-valgrind 2>&1 | tee log/TestSuiteRunWithValgrind.log

# Generate coverage information
echo "Generating coverage information"
make -f Makefile gen-lcov &> log/TestSuiteLcov.log
cp -R lcov docs/lcov
cp -R lcov TsComLib_DeliveryFile/docs

# Generate the log files with the software metrics
echo "Generating metrics information"
lizard -x "src/ProtobufImpl/*" -C 12 src > log/Metrics.log
lizard -x "src/DataPool/*" -x "src/Pckt/*" -C 10 src > log/MetricsNonEditor.log 

# Copy all log files
echo "Copying log files"
cp -R log TsComLib_DeliveryFile/

# Compile the latex files (twice to process all cross-references)
cd docs/int/usp
if [ ! -f "../../rel/TsLib_USP_i${VERS_USP}.pdf" ]
then
    echo "Compiling USP"
    pdflatex -interaction=nonstopmode TsLib_USP.tex > ../../../log/TsLib_USP.log
fi  
  
cd ../svr
if [ ! -f "../../rel/TsLib_SVR_i${VERS_SVR}.pdf" ]
then
    echo "Compiling SVR"
    pdflatex -interaction=nonstopmode TsLib_SVR.tex > ../../../log/TsLib_SVR.log
fi

cd ../um
if [ ! -f "../../um/TsLib_UM_i${VERS_UM}.pdf" ]
then
    echo "Compiling UM"
    pdflatex -interaction=nonstopmode TsLib_UM.tex > ../../../log/TsLib_UM.log
fi

cd ../rel
if [ ! -f "../../rel/TsLib_REL_i${VERS_REL}.pdf" ]
then
    echo "Compiling REL"
    pdflatex -interaction=nonstopmode TsLib_REL.tex > ../../../log/TsLib_REL.log
fi

cd ../keepalive
if [ ! -f "../../rel/TsLib_KA_i${VERS_KA}.pdf" ]
then
    echo "Compiling KA"
    pdflatex -interaction=nonstopmode TsLib_Keepalive.tex > ../../../log/TsLib_Keepalive.log
fi

cd ../usp
if [ ! -f "../../rel/TsLib_USP_i${VERS_USP}.pdf" ]
then
    echo "Compiling USP"
    pdflatex -interaction=nonstopmode TsLib_USP.tex > ../../../log/TsLib_USP.log
fi

cd ../svr
if [ ! -f "../../rel/TsLib_SVR_i${VERS_SVR}.pdf" ]
then
    echo "Compiling SVR"
    pdflatex -interaction=nonstopmode TsLib_SVR.tex > ../../../log/TsLib_SVR.log
fi

cd ../um
if [ ! -f "../../um/TsLib_UM_i${VERS_UM}.pdf" ]
then
    echo "Compiling UM"
    pdflatex -interaction=nonstopmode TsLib_UM.tex > ../../../log/TsLib_UM.log
fi

cd ../rel
if [ ! -f "../../rel/TsLib_REL_i${VERS_REL}.pdf" ]
then
    echo "Compiling REL"
    pdflatex -interaction=nonstopmode TsLib_REL.tex > ../../../log/TsLib_REL.log
fi

cd ../keepalive
if [ ! -f "../../rel/TsLib_KA_i${VERS_KA}.pdf" ]
then
    echo "Compiling KA"
    pdflatex -interaction=nonstopmode TsLib_Keepalive.tex > ../../../log/TsLib_Keepalive.log
fi
cd ../../..

echo "Copying the library support documents"
if [ ! -f "docs/rel/TsLib_USP_i${VERS_USP}.pdf" ]
then
    cp ./docs/int/usp/TsLib_USP.pdf docs/rel/TsLib_USP_i${VERS_USP}.pdf
fi
cp docs/rel/TsLib_USP_i${VERS_USP}.pdf TsComLib_DeliveryFile/docs/TsLib_USP.pdf

if [ ! -f "docs/rel/TsLib_SVR_i${VERS_SVR}.pdf" ]
then
    cp ./docs/int/svr/TsLib_SVR.pdf docs/rel/TsLib_SVR_i${VERS_SVR}.pdf 
fi
cp docs/rel/TsLib_SVR_i${VERS_SVR}.pdf TsComLib_DeliveryFile/docs/TsLib_SVR.pdf

if [ ! -f "docs/um/TsLib_UM_i${VERS_UM}.pdf" ]
then
    cp ./docs/int/um/TsLib_UM.pdf docs/rel/TsLib_UM_i${VERS_UM}.pdf 
fi
cp docs/rel/TsLib_UM_i${VERS_UM}.pdf TsComLib_DeliveryFile/docs/TsLib_UM.pdf

if [ ! -f "docs/rel/TsLib_KA_i${VERS_KA}.pdf" ]
then
    cp ./docs/int/keepalive/TsLib_Keepalive.pdf docs/rel/TsLib_Keepalive_i${VERS_SVR}.pdf 
fi
cp docs/rel/TsLib_Keepalive_i${VERS_SVR}.pdf TsComLib_DeliveryFile/docs/TsLib_Keepalive.pdf

if [ ! -f "docs/rel/TsLib_REL_i${VERS_REL}.pdf" ]
then
    cp ./docs/int/rel/TsLib_REL.pdf docs/rel/TsLib_REL_i${VERS_REL}.pdf 
fi
cp docs/rel/TsLib_REL_i${VERS_REL}.pdf TsComLib_DeliveryFile/docs/TsLib_REL.pdf











