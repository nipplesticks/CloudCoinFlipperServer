#!/bin/bash
path=$(cd $(dirname "${BASH_SOURCE:-$0}") && pwd)

cd "${path}/CloudCoinFlipperServer"
rm -fr bin
cmake -S . -B bin

cd "bin"
cmake --build .

if [ -d "Debug/" ]
then
	cp SFML-2.5.1/lib/Debug/*.dll Debug/
	mv "Debug" "${path}/exec/"
else
	cp SFML-2.5.1/lib/Release/*.dll Release/
	mv "Release" "${path}/exec/"
fi