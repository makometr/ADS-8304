import os
import subprocess
import shutil
out=subprocess.call(["g++ ./Source/rand.cpp -o rand"], shell=True)
outt=subprocess.call(["g++ ./Source/main.cpp -o main"], shell=True)
count = 1024;
if ((out==0) and (outt==0)):
	print("Compiling rand.cpp successful");
	print("Compiling main.cpp successful");
	i=1;
	while i<5:
		subprocess.call("./rand Tests/file" + str(i) + ".txt " + str(count), shell=True, cwd=".")
		subprocess.call("./main Tests/file" + str(i) + ".txt " + str(10) + " " + str(1), shell=True, cwd=".")
		count*=2;
		i= i+1
	while i<15:
		subprocess.call("./rand Tests/file" + str(i) + ".txt " + str(count), shell=True, cwd=".")
		subprocess.call("./main Tests/file" + str(i) + ".txt " + str(10) + " " + str(0), shell=True, cwd=".")
		count*=2;
		i= i+1




