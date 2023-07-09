# 编译器前端搭建

1. 词法分析+语法分析：flex+bison。这时应该生成一个抽象语法树
2. 线性IR生成，选择LLVM IR，根据抽象语法树生成线性IR

## 词法分析

### 05-10

现在比较困惑的是 flex 负责做什么，bison 负责做什么，但是之后的操作就不清楚了，需要去学一下 bison，我现在还只学了 flex。flex 的目的应该是单纯的识别与记录，**请不要尝试使用 flex 进行语法相关工作**，这会违背两个工具解耦的初心。

此外，我们可以先整理一下会遇到的 token 类型。

- 等号：`=`
- 分号：`;`
- 逗号：`,`
- 括号：`(`|`)`
- 方括号：`[`|`]`
- 花括号：`{`|`}`
- 逻辑运算符：`!`|`&&`|`||`
- 算术运算符：`+`|`-`|`*`|`/`|`%`
- 关系运算符：`==`|`!=`|`<`|`>`|`<=`|`>=`
- 变量类型：`void`|`int`
- 关键字：`if`|`while`|`break`|`continue`|`return`
- 数字常量：`十进制`｜`八进制`｜`十六进制`
- 标识符：`[字母｜_][字母|数字]*`
- 注释：`单行注释`｜`多行注释`(使用自动机COMMENT实现)

今天可以完成纯语法部分，即只进行识别，但是不进行记录，根据 bison 的需要再添加需要记录的部分。

### 05-11

今天添加了输出，即输出每一个识别到的 token；此外，添加了以文件作为输入的支持，调用 yy_switch_to_buffer 函数，可以切换到使用文件创建的 buffer。

时间主要用于解决昨天遇到的问题，通过新建一个可以 work 的小文件，一点点添加已有的内容并测试，发现问题是 `.*`。使用 `.*` 会一直匹配到行末，所以在不同行可以正常识别，但在同一行的情况下就会被认为是 `.*`，这符合了**长度最长**的优先匹配条件，改成 `.` 就没问题了。

### 05-14

> 12号在搞认识实习，下午去的医院，晚上开始发烧。13号烧的厉害，晚上去了校医院。

今天开始继续工作。

效率不算高，勉强看完bison的描述部分，由于书中直接在bison这一步进行了求解，分析抽象语法树的部分没有细看，我们的目的是使用bison得到抽象语法树，然后分析抽象语法树得到LLVM IR。

### 05-15

- [x] 对单个字的字符重构为文本字符，这样可以节省一些空间，看起来也会自然一些。
- [ ] 确定节点的类型，应当包括：数字类型、根节点类型（即子结点不为空）等。
- [ ] 对词法分析器进行修改，添加对应结构体属性的赋值
- [ ] 添加语法规则，完成树的构建
- [ ] 加遍历输出语法树的功能，最好尝试可视化输出

关于如何确定节点的类型，事实上，如果用抽象的理解，树的每个节点代表一个token，但由于不同token存储的方法不一样，所以才需要使用不同的节点类型。在确定节点类型时，应根据语法中的每一个符号去分析需要那些类型，并一一注明。

注意到一个问题，由于sysy语言支持const，所以有很多例子，一个类型会分为两个，例如ConstInitVal、InitVal。这不是问题所在，可以通过`is_const`的方式合并两个类型，但发现ConstExp和Exp的归约方式中，都是指向AddExp，而ConstExp要求AddExp中的元素都是常数，如何在语法规则中体现这一点？语法分析只能从AddExp推导到Exp，而是不是const应该由我们写的c代码去判断，这也验证了用`is_const`合并两个类型的合理性。

另一个问题，由于sysy语言支持数组，所以怎么保存数组的形状，如果数组的形状由常量定义，则直接用vector保存即可，但在函数参数中由变量定义，则不能直接使用vector定义，可以用一个链表，shape。

### 05-16

今天遇到的问题是写到表达式的时候发现不知道怎么写了，写的有点乱，想了想发现不应该每个都实现为单个对象，这些表达式类型部分可以合成一个对象，比如加减乘除、等于不等于。

比如说PrimaryExp这样没有直接递归的非终结符号，可以考虑不单独建立结构体，因为确实没有这个必要。

我发现我的思路可能有点问题，不如先尝试写语法规则，哪里遇到问题了再来改声明部分。

首先完成了Exp及其子符号的规则定义，现在比较疑惑的地方就是`$$=`的实际操作是什么，如果是创建一个节点的话，这个节点返回给谁了；并且这个节点的类型是怎么指定的。答案是，节点类型默认是int，当然可以手动指定节点类型，通过`%type`；除此之外，通过new创建一个类应该也是可以的。而节点返回给谁，应该会按照归约的顺序形成返回给当前节点，这样最终会得到一颗抽象语法树。

好像知道怎么写了，所有节点都用一个类型去表示就方便了。

节点的`node_type`根据真实值类型处理比较方便，还是根据使用场合比较方便。还是根据真实值类型处理比较方便，比如单独一个数组的下标，不能作为一个表达式来看待，不过一个左值可以作为一个表达式来看待。
