#!/bin/bash
DIR=arduino-eclipse
mkdir -p package-build
cd ..
rm -f $DIR/package-build/arduino-eclipse-1.0-r3.zip
zip -r $DIR/package-build/arduino-eclipse-1.0-r3.zip $DIR -x $DIR/\*.git\* -x $DIR/\*_\* -x $DIR/target
cd $DIR
