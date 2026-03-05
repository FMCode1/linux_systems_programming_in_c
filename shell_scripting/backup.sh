#!/bin/bash

echo "to check $1"
if [ $# -ne 1 ] ; then
    echo "Must be exactly 1 argument in $0"
elif [ -e $1 ] ; then
    echo "File/Folder $1 already exists"
else
    mkdir $1
    cp *.c *.h $1
fi