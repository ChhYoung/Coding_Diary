C++ 实现markdown解析器

## 1.前置知识
**Markdown基本语法:**
**HTML标签格式:**
**DOM:**
- Document Object Model,文档对象模型
- 浏览器收到html代码后通过html解析器构建一颗dom树，然后从上到下，从左到右的顺序读取DOM树的节点。`（DOM构造）`
- 然后依据DOM树进行布局`（布局）`
- 再进行绘制`（绘制）`
- 得到网页

构造：DOM树按照一定的关联性构造，再将css代码通过css解析器构建样式规则，放到对应节点中。

布局：从上到下，从左到右的顺序读取DOM树的节点，顺序放到一个虚拟传送带（文档流）上。子节点放到父节点内部。获取节点坐标大小等css属性，再页面上布局。

绘制：块级元素独占一行，一个子节点的内容为一行，超出长度后换行显示。

[详情](https://www.zhihu.com/question/34219998)

## 2. mdtransform设计
解析关键字：
1. `#` 标题类型可以简单转换为 `<h>`的HTML标签
2. 正常段落，直接用`<p>`进行包裹
3. `[]()`插入超链接 用`<a href=" ">...</a>`
4. `![]()`插入图片 用`<img alt="" src=""/>`
5. 两个\`用一个行内代码`<code>`,三个则`<pre><code>`进行替换
6. `>`使用`<blockquote>`标签
7. `—` `1.`分别用用`<u1>`和`<ol>`进行包裹，最后将整个内容使用`<li>`进行包装
8. `_`和`*`分别用`<em>`和`<strong>`标签

设计关键字token
```
* 0: null                          |开始
* 1: <p>                           |段落
* 2: <a href=" ">...</a>           |超链接
* 3: <ul>                          |无序列表
* 4: <ol>                          |有序列表
* 5: <li>                          |列表
* 6: <em>                          |斜体
* 7: <strong>                      |加粗
* 8: <hr />                        |水平分割线
* 9: <br />                        |换行
* 10: <img alt="" src="" />        |图片
* 11: <blockquote>                 |引用
* 12: <h1>                         |h1
* 13: <h2>                         |h2
* 14: <h3>                         |h3
* 15: <h4>                         |h4
* 16: <h5>                         |h5
* 17: <h6>                         |h6
* 18: <pre><code>                  |代码段
* 19: <code>                       |行内代码
```
根据这些定义`MarkdownTransform`类

```c++
class MarkdownTransform{
private:
    std::string content, TOC;
public:
    //   构造函数
    MarkdownTransform(const std::string &filename);

    //   获取Markdown目录
    std::string getTableContents(){ return TOC;}
    //   获取Markdown内容
    std::string getContents(){ return content;}

    //   析构函数
    ~MarkdownTransform();
};
```

因为Markdown和HTML类似都具有类似DOM tree的结构，所以需要去实现一个树结构
```C++
// 保存目录
typedef struct Cnode{
    std::vector <Cnode *> ch;
    std::string heading;
    std::string tag;

    // 构造函数
    Cnode(const std::string &hd):heading(hd){}
}Cnode;

// 保存正文内容
typedef struct node{
    // 节点类型
    int type;
    
    std::vector<node *> ch;

    // 存放三个重要属性
    // elem[0]   保存要显示的内容
    // elem[1]   保存链接
    // elem[2]   保存title
    std::string elem[3];

    node(int _type):type(_type){}
}node;
```
再到`MarkdownTransform`类中添加私有属性
```C++
private:
    node *root, *node;
    Cnode *Croot;
    // 记录HTML内容位置
    int cntTag = 0;
    // 缓存要处理的行
    char s[maxLenth];
```

## 3.实验步骤:

## 设计MarkdownTransform类的成员函数

### 3.1 处理每行开始处的空格和Tab

空格不影响整个markdown解析，最好的办法是将每行开始的空格和Tab进行一个预处理

> - 该行为空返回,否则
> - 记录空格数和Tab数，都有则按 Tab+0.25*Space 数计算
> - 返回pair(空格数，第一个非空格元素指针)
```c++
// 解析一行开头处的空格与Tab
// src:源串
// return 空格数和有内容处char* 构成的std::pair
inline std::pair<int , char*> start(char* src){
	//TODO
}
```

### 3.2 判断行类型
`#`后有空格 则为`<h>`
\`\`\`则为`blockcode`
`* + -`则为列表
`>`和空格则为引用
数字加`.`则为有序列表
否则就是普通段落
```c++
// 判断当前行的类型
// src: 源串
// 返回值: 当前行的类型和除去行标志性关键字的正是内容的 char* 指针组成的 std::pair
inline std::pair<int,char*>JudgeType(char* src){
	//TODO
}
```

### 3.3 类型获取
- 判断是否为标题
- 判断是否为图片
- 判断是否为超链接
```c++
// 判断是否为标题
inline bool isHeading(node *v) {
    //TODO
}
// 判断是否为图片
inline bool isImage(node *v) {
    //TODO
}
// 判断是否为超链接
inline bool isHref(node *v) {
    //TODO
}

```
```c++
// 判断当前行的类型
// src ： 源串
// return 当前行的类型和除去行标志性关键字的正是内容的 char* 指针组成的 std::pair
inline std::pair<int , char*>JudgeType(char* src){
    //TODO
}
```



### 3.4 节点搜索

给定一个深度查找想要的节点

```c++
// depth: 树的深度
// return : 找到的节点的指针
inline node* findnode(int depth){
    // TODO
    return ptr;
}
```



### 3.5 新增节点的插入
- Cnode中插入目录(设置tag标签来完成跳转到正确目录)
- node中插入解析内容

```c++
void Cins(Cnode *v,int x,const std::string &hd,int tag){
    // TODO
}
```



### 3.6 正文部分的处理

```c++
// 向指定节点插入要处理的串
// v: 节点
// src : 要处理的串
void insert(node* v ,const std::string &src){
    //TODO
    // 难点在于解析图片与超链接
}

```

### 3.7 换行的处理与段落生成

```c++
// 判断是否需要换行

inline bool isCutline(char* src){
    // TODO
    // 注意 --- 分割线
    // 代码块中又不能破坏代码的属性
}
```

```c++
//得到段落文本后生成
inline void mkpara(node *v){
    // TODO
}
```

### 3.8 遍历与生成

语法树是通过深度优先遍历的，对目录的深度遍历与对正文的深度遍历不同，分开实现

```c++
// 正文深度优先遍历
void dfs(node *v){
    // TODO
}
// 目录的深度优先遍历：
// 区别主要为 目录的展示方式需要使用无序列表
void Cdfs(Cnode* v, std::string index){
    // TODO
}
```

### 3.9 关键构造逻辑

基于上面的操作完善`MarkdownTransform`类的构造函数

```c++
MarkdownTransform(const std::string &filename){
    //TODO
}
```

### 3.10 析构函数

利用模板来同时生成Cnode和node的析构函数

