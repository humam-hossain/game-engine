#!/bin/bash
# Build script for rebuilding everything
set echo on
source ~/vulkan/1.4.304.1/setup-env.sh
echo "Building everything..."
pushd engine
source build.sh
popd
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi
pushd testbed
source build.sh
popd
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi
echo "All assemblies built successfully."