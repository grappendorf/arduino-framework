#!/bin/bash
DIR=arduino-eclipse
mkdir -p build
cd ..
rm -f $DIR/build/arduino-eclipse-1.0-r3.zip
zip -r $DIR/build/arduino-eclipse-1.0-r3.zip $DIR -x $DIR/\*.git\* -x $DIR/\*_\* -x $DIR/target
cd $DIR
