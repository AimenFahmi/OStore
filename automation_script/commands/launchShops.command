#!/usr/bin/env bash

parentdir="$(dirname "$0")"

cd $parentdir
cd ../../cmake-build-debug

make Shop

for i in {1..80}
do
    ./Shop &
done
wait

for i in {1..80}
do
    ./Shop &
done
wait

for i in {1..80}
do
    ./Shop &
done
wait

echo "finished"