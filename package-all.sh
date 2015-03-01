#!/bin/bash
DIR=arduino-framework
mkdir -p package-build
cd ..
rm -f $DIR/package-build/arduino-framework-1.0.0-r7.zip
zip -r $DIR/package-build/arduino-framework-1.0.0-r7.zip $DIR -x $DIR/\*.git\* -x $DIR/\*_\* -x $DIR/target
cd $DIR
