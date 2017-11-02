#!/bin/bash

# Enable strict mode
set -euo pipefail

# Enable debug
# set -x

MY_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJ_DIR="$( cd "${MY_DIR}/../" && pwd )"
BUILD_DIR="$PROJ_DIR/build"

rm -rf "$BUILD_DIR"
mkdir -v "$BUILD_DIR"
cd $BUILD_DIR
cmake ..
make
