#!/bin/bash

indent() { sed 's/^/  /'; }

for i in ./build/tests/*/test*; do
    printf "Executing test: '$i'\n\n"
    $i | indent
    if [ ${PIPESTATUS[0]} -ne 0 ]
    then
        printf "\nError: '$i' failed.\n\n"
        exit 42
    else
        printf "\n'$i' executed successfully.\n\n"
    fi
done
