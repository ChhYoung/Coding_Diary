#ifndef CODE_D_CPPPROJECTS_H_
#define CODE_D_CPPPROJECTS_H_

#include<string>
#include<vector>
#include<cstring>

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

// 保存目录的结构
typedef struct Cnode{
    std::vector<Cnode *> ch;
    std::string heading;
    std::string tag;

    //构造函数
    Cnode (const std::string &hd):heading(hd){}
}Cnode;

// 保存正文内容的结构
typedef struct node{
    int type; //节点代表的类型
    std::vector<node *> ch; 
    std::string elem[3]; //存放3个重要的属性
    // elem[0] 要显示的内容
    // elem[1] 链接
    // elem[2] 保存了title
    node (int _type): type(_type) {}
}node;
// Cnode node都用vector储存所以有push_back等方法

class MarkdownTransform{
private:
    std::string content, TOC;
    node *root,*now;
    Cnode *Croot;
    // 记录HTML内容位置
    int cntTag = 0;
    // 缓存要处理的行
    char s[maxLenth];

    // 是否为标题
    inline bool isHeading(node* v){
        return (v->type >= h1 && v->type <=16);
    } 

    // 是否为图片
    inline bool isImage(node* v){
        return (v->type == image);
    }

    // 是否为超链接
    inline bool isHref(node* v){
        return (v->type == href);
    }

    // 解析一行开始的空格和Tab
    // src ： 源串
    // return : 空格数 ； 有内容处的char * 指针 构成的std::pair
    inline std::pair<int,char *> start(char *src){
        // 如果该行内容为空，直接返回
        if((int)std::strlen(src) == 0)
            return std::make_pair(0,nullptr);
        // 统计空格和Tab数
        int cntspace = 0, cnttab = 0;
        // 从该行第一个起开始读，统计空格和Tab
        // 遇到不是空格和Tab的就停止
        for(int i = 0;src[i] != '\0';++i){
            if(src[i] == ' ')
                ++cntspace;
            else if(src[i] == '\t')
                ++cnttab;
            // 同时有空格和Tab，则按照Tab数，1 Tab == 4 space
            else return std::make_pair(cnttab + cntspace/4,src+i);
        }
        return std::make_pair(0,nullptr);
    }

    // 判断当前行的类型
    // src ： 源串
    // return : 行类型 ； 除去关键词后内容的指针char *  构成的std::pair
    inline std::pair<int,char *> JudgeType(char *src){
        char *ptr = src;

        // 跳过 '#'
        while(*ptr == '#') ++ptr;

        // 出现空格这是 ‘<h>’ 标签
        if(ptr - src > 0  && *ptr == ' ')
            return std::make_pair(ptr - src + h1 - 1,ptr + 1);

        // 重置分析位置
        ptr = src;

        // ``` 出现这是代码块
        if(std::strncmp(ptr,"```",3) == 0)
            return std::make_pair(blockcode,ptr+3);

        // + * - 出现且后面是空格，则说明是列表
        if( std::strncmp(ptr,"+ ",2) == 0 ||
            std::strncmp(ptr,"* ",2) == 0 ||
            std::strncmp(ptr,"- ",2) == 0 )
            return std::make_pair(ul, ptr + 1);

        // 出现数字且下一个是`. ` ，则说明是有序列表
        char *ptr1 = ptr;
        while(*ptr1 && (isdigit(*ptr1))) ptr1++;
        if(ptr1 != ptr && *ptr1 == '.' && ptr1[1] == ' ')
            return std::make_pair(ol,ptr1 + 1);

        // 否则，就是普通段落
        return std::make_pair(paragraph, ptr);
    }


    // 节点搜索
    // 在造树的过程中通过给定一个深度来找到想要查找的节点
    // depth : 树的深度
    // return : 找到节点的指针
    inline node* findnode(int depth){
        node* ptr = root;
        while(!ptr->ch.empty() && depth != 0){
            ptr = ptr->ch.back();
            if(ptr->type == li)
                --depth;
        }
        return ptr;
    }

    // 新节点的插入
    // 为了实现点击目录的跳转功能，使用tag标签标记这个目录所指向的内容
    void Cins(Cnode* v, int x, const std::string &hd, int tag){
        int n = (int)v->ch.size();
        if(x == 1){
            v->ch.push_back(new Cnode(hd));
            v->ch.back()->tag = "tag" + std::to_string(tag);
            return ;
        }
        if(!n || v->ch.back()->heading.empty())
            v->ch.push_back(new Cnode(""));
        Cins(v->ch.back(), x-1, hd, tag);
    }

    // 正文部分的处理，主要在于找到超链接和图片

    // 向指定节点中插入要处理的串
    // v:节点
    // src: 要处理的串
    void insert(node* v,const std::string &src){
        int n = (int)src.size();
        bool incode = false,
             inem = false,
             instrong = false,
             inautolink = false;
        v->ch.push_back(new node(nul));

        for(int i=0; i<n; i++){
            char ch = src[i];
            if(ch == '\\'){
                ch = src[++i];
                v->ch.back()->elem[0] += std::string(1,ch);
                continue;
            }

            // 处理行内代码
            if (ch == '`' && !inautolink){
                incode ? v->ch.push_back(new node(nul)):v->ch.push_back(new node(code));
                incode = !incode;
                continue;
            }

            // 处理加粗
            if (ch == '*' && (i<n-1 &&(src[i+1] == '*'))&& !incode && !inautolink){
                ++i;
                instrong ? v->ch.push_back(new node(nul)):v->ch.push_back(new node(strong));
                instrong = !instrong;
                continue;
            }
            if (ch == '_' && !incode && !instrong && !inautolink) {
                inem ? v->ch.push_back(new node(nul)) : v->ch.push_back(new node(em));
                inem = !inem;
                continue;
            }

            //  处理图片
            if ( ch == '!' && (i < n - 1 && src[i+1] == '[') &&
                !incode && !instrong && !inem && !inautolink){
                v->ch.push_back(new node(image));
                for(i += 2; i<n-1 && src[i] != ']'; ++i)
                    v->ch.back()->elem[0] += std::string(1,src[i]);
                
                for (i++;i<n-1 && src[i] != ' '&& src[i] != ')';++i)
                    v->ch.back()->elem[1] += std::string(1,src[i]);
                if (src[i] != ')')
                    for(i++; i<n-1 && src[i] != ')';++i)
                        if(src[i] != '"')
                            v->ch.back()->elem[2] += std::string(1,src[i]);
                v->ch.push_back(new node(nul));
                continue;
            }
        }
    }

    


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




// 类型获取



// 新增节点


#endif //CODE_D_CPPPROJECTS_H_