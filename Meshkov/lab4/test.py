import subprocess
from subprocess import Popen
import os

program = './lab4'

if not os.path.isfile(program):
    print(program, "is not found.")
    quit()

def test_with_file(path):
    all_tests_are_ok = True
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
            
            tree_expr = readline()
            correct_result = ''
            while True:
                line = readline()
                if not line or line.startswith(';'):
                    break
                correct_result += line
            
            if not tree_expr or not correct_result:
                break
            
            p = Popen(program, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
            
            out, _ = p.communicate(tree_expr)
            
            result_begin = out.find(':', out.rfind('Enter')) + len(': ')
            result = out[result_begin:]

            out = out.replace('Enter a bin tree: ', f'Tree: {tree_expr}')
            
            status = 'ok'
            if result != correct_result:
                status = 'FAILED'
                out += f'Expected:\n{correct_result}\n'
                all_tests_are_ok = False
            
            print(f'Test {iteration}: {status}')
            print(out)
    return all_tests_are_ok
                
for address, _, files in os.walk('Tests'):
    all_tests_are_ok = True
    for file in files:
        path = os.path.join(address, file)
        print(path, ':', sep='')
        print()
        all_tests_are_ok &= test_with_file(path)
    if all_tests_are_ok:
        print('All tests are ok.')
    else:
        print('Some tests are FAILED.')
