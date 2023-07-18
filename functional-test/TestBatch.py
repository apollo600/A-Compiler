from TestMachine import Test, init_test, check_compiler

import os
import glob

Script = "make"
Compiler = "./parser.out"
TEST_DIR = "./function_test2021"

file_pattern = os.path.join(TEST_DIR, "*.sy")
test_cases = glob.glob(file_pattern)

init_test(Script)
check_compiler(Compiler)
pass_cases = []
fail_cases = []
for test_case in test_cases:
    try:
        case, res = Test(test_case, Compiler)
        if res:
            pass_cases.append(case)
        else:
            fail_cases.append(case)
    except Exception as e:
        print("Top level", repr(e))

print("Pass Cases: total ", len(pass_cases))
print(pass_cases)
# print("Fail Cases: total ", len(fail_cases))
# print(fail_cases)