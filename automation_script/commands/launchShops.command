#!/usr/bin/env bash

parentdir="$(dirname "$0")"

cd $parentdir
cd ../../cmake-build-debug

make Shop

for i in {1..40}
do
    ./Shop &
done
wait

echo "finished"