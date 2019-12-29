import subprocess
from subprocess import Popen
import os

program = './course_work'

if not os.path.isfile(program):
    print(program, "is not found.")
    quit()

def test_with_file(path):
    with open(path, 'r') as file:
        iteration = 0
        while True:
            iteration += 1
            
            def readline():
                line = file.readline()
                if not line:
                    return None
                return line.rstrip('\n') + '\n'
            
            input = readline()
            if not input:
                break
            
            p = Popen(program, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
            
            out, _ = p.communicate(input)

            enter_pos = out.find('Enter actions:') + len('Enter actions:\n')
            out = out[:enter_pos] + input + out[enter_pos:]
            
            print(f'Test {iteration}:')
            print(out)
            
            os.rename('red-black-tree-demo.html', f'red-black-tree-demo-{iteration}.html')
            
for address, _, files in os.walk('Tests'):
    for file in files:
        path = os.path.join(address, file)
        print(path, ':', sep='')
        print()
        test_with_file(path)
