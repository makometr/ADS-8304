#!/bin/bash
make

for file in ./Tests/*
do

./lab4 $file

done

