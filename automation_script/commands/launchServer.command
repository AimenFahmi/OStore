#!/usr/bin/env bash

parentdir="$(dirname "$0")"

cd $parentdir

cd ../../cmake-build-debug

make Server
echo "Working..."
./Server
echo "Finished"


