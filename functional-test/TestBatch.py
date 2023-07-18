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
for test_case in test_cases:
    Test(test_case, Compiler)