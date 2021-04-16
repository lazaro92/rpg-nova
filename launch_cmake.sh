#!/bin/bash

DIR="build/"

# create build folder (if not exist) and go inside
if [-d "$DIR"]; then
    mkdir ${DIR}
fi
cd ${DIR}

# execute CMAKE and generate a Unix Makefile
cmake ..
cmake --build .
