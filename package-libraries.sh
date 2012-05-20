#!/bin/bash

pack() {
	VERSION=$(cat $1/version.txt)
	zip -r ../build/$1-${VERSION//./_}.zip $1 --exclude \*.svn\*
}

libraries="\
	CMPS03\
	Fader\
	SRF02\
	WheelEncoder\
	XXBee"

mkdir -p tmp
mkdir -p build
for l in $libraries
do
	cp -a $l tmp
done
cd tmp
find . -iname "*.cpp" | xargs perl -pi -w -e 's/Wire\/Wire\.h/Wire\.h/g;'
find . -iname "*.cpp" | xargs perl -pi -w -e 's/WProgram\.h/WProgram\.h/g;'
for l in $libraries
do
	pack $l
done
cd ..
rm -rf tmp
