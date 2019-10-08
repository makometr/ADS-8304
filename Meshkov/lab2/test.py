import subprocess
from subprocess import Popen
import os

program = './lab2'

if not os.path.isfile(program):
    print(program, "is not found.")
    quit()

def test_with_file(path):
    with open(path, 'r') as file:
        iteration = 0
        while True:
            iteration += 1
            
            expression = file.readline()
            variable = file.readline()
            if not expression or not variable:
                break
            expression = expression.rstrip('\n')
            variable = variable.rstrip('\n')
            
            print('Test ', iteration, ': ', sep='')
            
            p = Popen(program, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
            
            out, _ = p.communicate(expression + '\n' + variable + '\n')
            
            out = out.replace('Enter expression: ', 'Expression: ' + expression + '\n')
            out = out.replace('Enter target variable: ', 'Target variable: ' + variable + '\n')
            
            print(out)
                
for address, _, files in os.walk('Tests'):
    for file in files:
        path = os.path.join(address, file)
        print(path, ':', sep='')
        print()
        test_with_file(path)
