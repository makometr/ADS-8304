#!/bin/bash
make

for file in ./Tests/*
do

./lab2 $file

done
