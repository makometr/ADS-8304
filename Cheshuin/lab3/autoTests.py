import subprocess
import os

executable = './lab3'
testsDir = 'Tests/'

callList = [executable]
for name in os.listdir(testsDir):
	path = testsDir + name
	if (os.path.isfile(path)):
		callList.append(path)
	
print(callList)

subprocess.call(callList)