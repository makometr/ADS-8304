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
		subprocess.call("./a.out", shell=True, cwd="./Source")
		
