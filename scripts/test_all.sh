#!/bin/bash

set -euo pipefail

MY_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

$MY_DIR/build_from_scratch.sh -DUSE_CPP11=OFF -DCMAKE_BUILD_TYPE=Debug
$MY_DIR/run_tests.sh

$MY_DIR/build_from_scratch.sh -DUSE_CPP11=ON -DCMAKE_BUILD_TYPE=Debug
$MY_DIR/run_tests.sh
