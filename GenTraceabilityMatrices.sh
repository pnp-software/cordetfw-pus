#!/bin/bash
# Generate the following traceability matrices:
# 
# - VerifyInfo.csv: requirement items to test cases which verify them
# - VerUserInterface.csv: user interface items to test cases which verify them
# - ReqToImpl.csv: requirement items to their implementation items
# 
# All traceability files are generated in directory: docs/int/vr.
# 
# The script must be run from the top-level directory of the PUS Extension.
#
#===============================================================================

#-------------------------------------------------------------------------------
# Part 1: Generation of VerifyInfo.csv
# 
# The traceability information is extracted from the header files of the test 
# suite where verification information is placed in @verify tags.
#-------------------------------------------------------------------------------

# Add the header line at the top of the file
echo "TestCase,AAType,AAName,Desc" > VerifyInfo.csv

for filename in test/*.h; do
    var="${filename#test/}"     # Strip 'test/' from the file name
    var="$var,"
    grep "@verify" $filename  | sed "s/@verify/$var/g" >> VerifyInfo.csv
done

sed -i 's/TsTestCase_//g' VerifyInfo.csv    # Strip first part of file name
sed -i 's/TsTestCase//g' VerifyInfo.csv     # Strip first part of file name
sed -i 's/   \* //g' VerifyInfo.csv         # Strip doxygen asterisk
sed -i 's/, /,/g' VerifyInfo.csv            # Remove white space after commas
sed -i 's/_/\\_/g' VerifyInfo.csv           # Replace underscore (for latex)
sed -i 's/\.h//g' VerifyInfo.csv            # Remove file extension

# Sort by the name field
sort --field-separator=',' --key=2,3 -o VerifyInfo.csv VerifyInfo.csv

# Replace comma with pipe as separator
sed -i 's/,/|/g' VerifyInfo.csv

mv VerifyInfo.csv docs/int/vr/VerifyInfo.csv

#-------------------------------------------------------------------------------
# Part 2: Generation of VerReqItem.csv
# 
# The traceability information is generated by a dedicated python script
#-------------------------------------------------------------------------------

cd docs/int/vr
python ReqItemToTestCase.py
cd ../../..
