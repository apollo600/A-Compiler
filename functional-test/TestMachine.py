"""
用于进行测试
1. 提供编译器可执行程序
2. 调用编译器编译SysY源代码，得到LLVM IR
3. 调用LLVM编译LLVM IR，得到可执行程序
4. 执行可执行程序，与输出参照文件进行对比
5. 如果结果一致输出PASS，如果结果不一致输出错误情况
"""

import re
import os
import sys
import datetime
import subprocess

### CONFIG BEGIN

### CONFIG END

class Colors:
    RESET = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    PURPLE = '\033[95m'
    CYAN = '\033[96m'


def init_test(script_file):
    subprocess.run([script_file])


def check_compiler(Compiler):
    if os.path.exists(Compiler):
        timestamp = os.path.getmtime(Compiler)
        modified_time = datetime.datetime.fromtimestamp(timestamp)
        formatted_time = modified_time.strftime("%Y-%m-%d %H:%M:%S")
        print(f"\nUsing Compiler: {Compiler}, Generated at: {formatted_time}")
    else:
        raise FileNotFoundError(f"Compiler {Compiler} not found")


def compile_sysy(Infile, IR, DEBUG_OUTPUT):
    if os.path.exists(Infile):
        if DEBUG_OUTPUT is not None:
            print(f"\nCompile SysY: {Infile} to LLVM IR: {IR} > {DEBUG_OUTPUT}")
            with open(DEBUG_OUTPUT, "w") as output:
                subprocess.run([Compiler, Infile, "-o", IR], stdout=output, stderr=output)
        else:
            print(f"\nCompile SysY: {Infile} to LLVM IR: {IR}")
            subprocess.run([Compiler, Infile, "-o", IR, "--hide-AST"])
    else:
        raise FileNotFoundError(f"Src file {Infile} not found")

        
def compile_IR(IR, Exe):
    if os.path.exists(IR):
        print(f"\nCompile LLVM IR: {IR} to Exe: {Exe}")
        subprocess.run(["clang", IR, "-o", Exe])
    else:
        raise FileNotFoundError(f"IR file {IR} not found")


def run_exe(Exe):
    if os.path.exists(Exe):
        print(f"\nRun Exe: {Exe}")
        result = subprocess.run([Exe])
        return result.returncode
    else:
        raise FileNotFoundError(f"Exe file {Exe} not found")


def check_result(returncode, Outfile, TestCase):
    true_value = None
    with open(Outfile, "r") as outfile:
        true_value = int(outfile.read())
    
    if returncode == true_value:
        print(f"\n{Colors.BOLD}Test Case: {TestCase}{Colors.RESET} return code is {returncode} {Colors.GREEN}PASS{Colors.RESET}")
    else:
        print(f"\nreturn code is {returncode}, true value is {true_value} {Colors.RED}FAILED{Colors.RESET}")


if __name__ == "__main__":
    args = sys.argv

    Script = "make"
    Compiler = "./parser.out"
    In = args[1] # "./function_test2021/001_var_defn.sy"
    IR = "./main.ll"
    DEBUG_OUTPUT = "./parser-output.txt"
    Exe = "./main.out"
    Out = re.sub(".sy$", ".out", In)
    TestCase = int(In.split("\\")[-1][:3])

    try:
        init_test(Script)
        check_compiler(Compiler)
        compile_sysy(In, IR, DEBUG_OUTPUT)
        compile_IR(IR, Exe)
        returncode = run_exe(Exe)
        check_result(returncode, Out, TestCase)
    except Exception as e:
        print(e)
