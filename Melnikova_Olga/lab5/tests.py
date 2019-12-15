import os
import subprocess
import shutil
out=subprocess.call(["g++ ./Source/main.cpp"], shell=True)
if out==0:
	print("Compiling successful");
	for f in os.listdir("Tests"):
		print("\n╒═══════════════════════════════════════════════════════════════════════════════")
		print("│ " + f + ":")
		shutil.copy("Tests/" + f + "/input.txt", "./Source/input.txt")
		shutil.copy("Tests/" + f + "/inputToDelete.txt", "./Source/inputToDelete.txt")
		s = open(r"./ReadTree.txt", "w")
		s.close()
		s = open(r"./TreeAfterDelete.txt", "w")
		s.close()
		subprocess.call("./a.out ./Source/input.txt ./Source/inputToDelete.txt", shell=True, cwd=".")
		print("Cчитанное дерево:")
		a = open(r"./ReadTree.txt", "r")
		file_contents = a.read()
		print (file_contents)
		a.close()
		print("Дерево после удаления заданных элементов:")
		b = open(r"./TreeAfterDelete.txt", "r")
		file_contents = b.read()
		print (file_contents)
		b.close()
		
