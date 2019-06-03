#ifndef CODE_D_CPP_PROJECTS_H_
#define CODE_D_CPP_PROJECTS_H_

#include<string>
#include<vector>
#include<cstring>

// 缓冲数组的最大长度，缓冲数组用来缓存要处理的行
#define maxLength 10000

// 词法关键字枚举
enum{
    maxLenth    = 10000,
    nul         = 0,
    paragraph   = 1,
    href        = 2,
    ul          = 3,
    ol          = 4,
    li          = 5,
    em          = 6,
    strong      = 7,
    hr          = 8,
    br          = 9,
    image       = 10,
    quote       = 11,
    h1          = 12,
    h2          = 13,
    h3          = 14,
    h4          = 15,
    h5          = 16,
    h6          = 17,
    blockcode   = 18,
    code        = 19
};

// HTML前缀标签
const std::string ftontTag[] = {
    "","<p>","","<ul>","<ol>","<li>","<em>","<strong>",
    "<hr color=#CCCCCC size=1 />","<br />",
    "","<blockquote>",
    // 右边的尖括号预留给添加其他的标签属性, 如 id
    "<h1 ","<h2 ","<h3 ","<h4 ","<h5 ","<h6 ", 
    "<pre><code>","<code>"
};

// HTML后缀标签
const std::string backTag[] = {
    "","</p>","","</ul>","</ol>","</li>","</em>","</strong>",
    "","","","</blockquote>",
    "</h1>","</h2>","</h3>","</h4>","</h5>","</h6>",
    "</code></pre>","</code>"
};

// 构造类似DOM树的节点来存储解析出来的内容

// 保存目录的结构 TOC
typedef struct Cnode{
    // 指向节点的指针
    std::vector<Cnode *> ch;
    std::string heading;
    std::string tag;
    // 构造函数
    Cnode(const std::string &hd):heading(hd){};
}Cnode;

// 保存正文内容的结构 content
typedef struct node{
    // 节点代表类型
    int type;
    // 指向节点的指针
    std::vector<node *> ch;
    // 存放三个重要的属性，
    // elem[0] 要显示的内容
    // elem[1] 保存了链接
    // elem[2] 保存了title
    std::string elem[3];
    // 构造函数
    node(int _type):type(_type){}
}node;

// Markdown 解析类
class MarkdownTransform{
private:
    // 内容 和 标题
    std::string content,TOC;    
    // 解析后内容的节点
    node *root, *now;
    Cnode *Croot;
    // 记录索引位置
    int cntTag = 0;
    // 缓存数组
    char s[maxLength];
public:
    // 构造函数
    MarkdownTransform(const std::string &filename);

    // 获取目录 TOC
    std::string getTableOfContents(){return TOC;}

    // 获取Markdown 内容 content
    std::string getContents(){ return content;}

    // 析构函数
    ~MarkdownTransform();

    // 处理空格和Tab
    // input: src  源字符串
    // return: std::pair<空格数，第一个非空格元素的指针> 
    inline std::pair<int,char*> start(char* src){
        // 空行则返回
        if( (int)strlen(src) == 0 )
            return std::make_pair(0,nullptr);
        // 记录空格数和Tab数，按Tab+ 0.25 x Sapce 数计算
        int cntSpace = 0, cntTab = 0;
        
        for(int i = 0 ; src[i] != '\0'; ++ i){
            if(src[i] == '\t')
                ++ cntTab;
            else if(src[i] == ' ')
                ++ cntSpace;
            else return std::make_pair(cntTab + cntSpace / 4,src + i );
        }
        return std::make_pair(0,nullptr);
    }
};

#endif //CODE_D_CPP_PROJECTS_H_