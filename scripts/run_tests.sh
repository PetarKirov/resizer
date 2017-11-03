#!/bin/bash

indent() { sed 's/^/>  /'; }

TESTS="./build/tests/*/test*"
TEST_COUNT=`ls -1q $TESTS | wc -l`

echo "---"
echo "Test runner started. $TEST_COUNT tests detected."

for i in $TESTS; do
    echo "* Executing test: '$i'..."
    $i | indent
    if [ ${PIPESTATUS[0]} -ne 0 ]
    then
        printf "Error: '$i' failed.\n\n"
        exit 42
    else
        printf "'$i' executed successfully.\n\n"
    fi
done

echo "All tests ($TEST_COUNT) executed successfully."
echo "---"
