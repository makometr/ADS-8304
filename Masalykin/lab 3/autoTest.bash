#!/bin/bash
make

for file in ./Tests/*
do

./lab3 $file

done

