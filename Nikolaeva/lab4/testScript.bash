#!/bin/bash
make

for file in ./Tests/*
do

./lab4.exe $file

done

