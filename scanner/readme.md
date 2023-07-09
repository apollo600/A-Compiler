# 词法分析器

## 单元测试方法

```shell
# 执行目录位于项目根目录
cd ..
make
make run_test_scanner
```

会使用`test_scanner.sy`作为输入，进行词法分析的测试，识别到的带有含义的字符会进行提示输出。

example:

```shell
-- Use scanner/test_scanner.sy as input
Int
Ident: `main`
Char symbol: (
Char symbol: )
Char symbol: {

Return
Digit oct: `0`
Char symbol: ;

Char symbol: }
```
