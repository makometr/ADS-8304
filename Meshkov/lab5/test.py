import subprocess
from subprocess import Popen
import os

program = './lab5'

if not os.path.isfile(program):
    print(program, "is not found.")
    quit()

def test_with_file(path):
    with open(path, 'r') as file:
        iteration = 0
        while True:
            iteration += 1
            
            def readline():
                line = ''
                while True:
                    line = file.readline()
                    if not line.startswith('#'):
                        break
                if not line:
                    return None
                return line.rstrip('\n') + '\n'
            
            values = readline()
            
            if not values:
                break
            
            p = Popen(program, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
            
            out, _ = p.communicate(values)

            colon_pos = out.find(':') + len(':\n')
            out = out[:colon_pos] + values + out[colon_pos:]
            
            print(f'Test {iteration}:')
            print(out)
                
for address, _, files in os.walk('Tests'):
    for file in files:
        path = os.path.join(address, file)
        print(path, ':', sep='')
        print()
        test_with_file(path)
