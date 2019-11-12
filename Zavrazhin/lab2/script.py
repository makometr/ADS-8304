#!/bin/python3
import os
import subprocess


out = subprocess.call(['clear && make'], shell=True, cwd='./')
if out == 0:
	print("Compilation was successful.");
	path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "Tests")
	for root, dirs, filenames in os.walk(path):
	    for filename in filenames:
	        with open(os.path.join(root, filename), 'r', encoding='UTF8')\
	                  as input_file:
	            for line in input_file:
	                subprocess.call('./lab2 "' + line + '"', shell=True, 
	                                cwd='./')
	                print()
	                input("Press Enter to continue...")
	                print()

