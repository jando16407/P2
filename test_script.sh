#!/bin/bash

## Test Variables
NUMBER_TESTS_PASSED=0
NUMBER_TESTS_FAILED=0

## Make the program binary
make

## Test #1: Small Input
cp test/test_smallinput.txt ./input.txt
./det
ANSWER=$(cat output.txt)

if [ "$ANSWER" == "668" ]; then 
    echo "Test #1: Passed"
    NUMBER_TESTS_PASSED=$((NUMBER_TESTS_PASSED+1))
else
    echo "Test #1: Failed"
    NUMBER_TESTS_FAILED=$((NUMBER_TESTS_FAILED+1))
fi

rm input.txt
rm output.txt

## Test #2: Medium Input
cp test/test_mediuminput.txt ./input.txt
./det
ANSWER=$(cat output.txt)

if [ "$ANSWER" == "8.74952e+07" ]; then 
    echo "Test #2: Passed"
    NUMBER_TESTS_PASSED=$((NUMBER_TESTS_PASSED+1))
else
    echo "Test #2: Failed"
    NUMBER_TESTS_FAILED=$((NUMBER_TESTS_FAILED+1))
fi

rm input.txt
rm output.txt


## Display test results
make clean
echo "Number of tests passed: $NUMBER_TESTS_PASSED"
echo "Number of tests failed: $NUMBER_TESTS_FAILED"

if (($NUMBER_TESTS_FAILED > 0)); then
    ## Exit failure
    exit 1
fi
