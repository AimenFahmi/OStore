#!/usr/bin/env bash

parentdir="$(dirname "$0")"

cd $parentdir
cd ../../cmake-build-debug

make Customer

for i in {1..80}
do
    ./Customer &
done
wait

for i in {1..80}
do
    ./Customer &
done
wait

for i in {1..80}
do
    ./Customer &
done
wait

echo "finished"