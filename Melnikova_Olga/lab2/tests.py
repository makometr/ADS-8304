import os
import subprocess
import shutil
out=subprocess.call(["g++ main.cpp"], shell=True, cwd="./Source")
if out==0:
	print("Compiling successful");
	for f in os.listdir("Tests"):
		print("\n╒═══════════════════════════════════════════════════════════════════════════════")
		print("│ " + f + ":")
		shutil.copy("Tests/" + f + "/lisp.txt", "./Source/lisp.txt")
		shutil.copy("Tests/" + f + "/symb.txt", "./Source/symb.txt")
		s = open(r"Source/"+ f +".txt", "w")
		s.close()
		subprocess.call("./a.out lisp.txt symb.txt " + f + ".txt", shell=True, cwd="./Source")
		a = open(r"Source/"+ f +".txt", "r")
		file_contents = a.read()
		print (file_contents)
		a.close()
		
