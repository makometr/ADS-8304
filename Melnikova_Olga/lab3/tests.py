import os
import subprocess
import shutil
out=subprocess.call(["g++ ./Source/main.cpp"], shell=True)
if out==0:
	print("Compiling successful");
	for f in os.listdir("Tests"):
		print("\n╒═══════════════════════════════════════════════════════════════════════════════")
		print("│ " + f + ":")
		shutil.copy("Tests/" + f, "./Source/relations.txt")
		s = open(r"Source/result.txt", "w")
		s.close()
		subprocess.call("./a.out relations.txt", shell=True, cwd="./Source")
		a = open(r"Source/result.txt", "r")
		file_contents = a.read()
		print (file_contents)
		a.close()
