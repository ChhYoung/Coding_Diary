#!/bin/bash
int=1
while((int<=100))
do
    echo "loop ---------------------------------"
    echo $int
    python run.py
    let "int++"
done
