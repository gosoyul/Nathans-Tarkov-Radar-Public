##!/bin/sh

# Client name
CLIENT_NAME="TarkovInjector"

# Set PATH
SHELL_PATH=`pwd -P`
BUILD_PATH="${SHELL_PATH}/memory-client/src/build"
DEST="${SHELL_PATH}/memory-client"

# Move directory
cd "${BUILD_PATH}"

# Ninja build
ninja

# Move TarkovInjector to DESTination
mv ./${CLIENT_NAME} ${DEST}/${CLIENT_NAME}
