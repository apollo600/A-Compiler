# A-Compiler

## Abstract

- 要求与目标：完成 SysY 到 llvm-ir 的静态编译器前端。
- 总体完成情况：基本完成 SysY 源代码到 llvm-ir 的静态编译工作。
- 团队分工情况：单人完成。

## Quick Start

SysY 的前端静态编译器。

生成可执行文件：
``` 
make -C front-end
```

使用方法：
```
./build/parser.out  \
    <input_file>    \
    [-o <output_file>]  \
    [--hide-AST]
```
参数说明：
- `-o` 指定 llvm-IR 的输出文件
- `--hide-AST` 隐藏抽象语法树 AST 的输出

## 执行测试

### 样例

使用样例文件 `functional-test/samples/test_parser.sy`。

---

生成抽象语法树 AST 和 IR：
```
./build/parser.out ./functional-test/samples/test_parser.sy -o main.ll
```

生成 IR，不输出 AST：
```
./build/parser.out ./functional-test/samples/test_parser.sy -o main.ll --hide-AST
```

### 测试集

单点测试：
```
cd functional-test/
python TestMachine.py ./function_test2021/001_var_defn.sy
```

完整测试
```
python TestBatch.py
```

> 该编译器只实现了 SysY 的主要语法，因此并不能通过所有测试样例，目前通过的样例为：
> ```
> Pass Cases: total  44
> [0, 1, 2, 3, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 30, 31, 32, 34, 35, 36, 37, 38, 39, 40, 41, 43, 44, 45, 49, 52, 53, 54, 55, 91]
> ```
