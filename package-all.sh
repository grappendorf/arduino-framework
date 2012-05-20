#!/bin/bash
DIR=arduino-eclipse
mkdir -p build
cd ..
zip -r $DIR/build/arduino-eclipse-1.0-r3.zip $DIR -x $DIR/\*.svn\* -x $DIR/\*_\* -x $DIR/target
cd $DIR
