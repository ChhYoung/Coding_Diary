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
const std::string frontTag[] = {
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
class MarkdownTransform {
private:
	// 内容 和 标题
	std::string content, TOC;
	// 解析后内容的节点
	node* root, * now;
	Cnode* Croot;
	// 记录索引位置
	int cntTag = 0;
	// 缓存数组
	char s[maxLength];
public:
	// 构造函数
	// 基于下面的操作完善markdown的构造函数
	MarkdownTransform(const std::string& filename) {
		// 初始化，当前指针now指向根节点
		Croot = new Cnode("");
		root = new node(nul);
		now = root;

		// 从文件流读取文件
		std::ifstream fin(filename);

		// 默认不是新段落，默认不在代码块内
		bool newpara = false;
		bool inblock = false;

		// 直接读取到 eof为止
		while (!fin.eof()) {
			fin.getline(s, maxLength);
			// 处理不在代码块且需要换行的
			if (!inblock && isCutline(s)) {
				now = root;
				now->ch.push_back(new node(hr));
				newpara = false;
				continue;
			}
			std::pair<int, char*> ps = start(s);

			// 如果不在代码块，且没有统计空格和Tab，则直接读取下一行
			if (!inblock && ps.second == nullptr) {
				now = root;
				newpara = true;
				continue;
			}

			// 分析改行的类型
			std::pair<int, char*> tj = JudgeType(ps.second);

			// 如果是代码块类型
			if (tj.first == blockcode) {
				// 在代码块中则push一个新节点
				inblock ? now->ch.push_back(new node(nul))
					: now->ch.push_back(new node(blockcode));
				inblock = !inblock;
				continue;
			}

			// 在代码块则直接将内容拼接
			if (inblock) {
				now->ch.back()->elem[0] += std::string(s)+'\n';
				continue;
			}

			//普通段落
			if (tj.first == paragraph) {
				if (now == root) {
					now = findnode(ps.first);
					now->ch.push_back(new node(paragraph));
					now = now->ch.back();
				}
				bool flag = false;
				if (newpara && !now->ch.empty()) {
					node* ptr = nullptr;
					for (auto i : now->ch) {
						if (i->type == nul)
							ptr = i;
					}
					if (ptr != nullptr) {
						mkpara(ptr);
					}
					flag = true;
				}
				if (flag) {
					now->ch.push_back(new node(paragraph));
					now = now->ch.back();
				}
				now->ch.push_back(new node(nul));
				insert(now->ch.back, std::string(tj.second));
				newpara = false;
				continue;
			}
			now = findnode(ps.first);

		}


	}

	// 获取目录 TOC
	std::string getTableOfContents() { return TOC; }

	// 获取Markdown 内容 content
	std::string getContents() { return content; }

	// 析构函数
	~MarkdownTransform();

	// 处理空格和Tab
	// input: src  源字符串
	// return: std::pair<空格数，第一个非空格元素的指针> 
	inline std::pair<int, char*> start(char* src) {
		// 空行则返回
		if ((int)strlen(src) == 0)
			return std::make_pair(0, nullptr);
		// 记录空格数和Tab数，按Tab+ 0.25 x Sapce 数计算
		int cntSpace = 0, cntTab = 0;

		for (int i = 0; src[i] != '\0'; ++i) {
			if (src[i] == '\t')
				++cntTab;
			else if (src[i] == ' ')
				++cntSpace;
			else return std::make_pair(cntTab + cntSpace / 4, src + i);
		}
		return std::make_pair(0, nullptr);
	}

	// 判断行类型
	// input : src
	// output: 当前行类型 和 正文内容的char* 组成的pair
	inline std::pair<int, char*>JudgeType(char* src) {
		char* ptr = src;
		// 判断#
		while (*ptr == '#')
			++ptr;
		if (ptr - src > 0 && *ptr == ' ')
			return std::make_pair(ptr - src - 1 + h1, ptr);
		// 置位
		ptr = src;
		// ``` 代码块
		if (std::strncmp(ptr, "```", 3) == 0)
			return std::make_pair(blockcode, ptr + 3);
		// + -  * 则为列表
		if (std::strncmp(ptr, "+ ", 2) == 0 ||
			std::strncmp(ptr, "- ", 2) == 0 ||
			std::strncmp(ptr, "* ", 2) == 0)
			return std::make_pair(ul, ptr + 1);

		// 引用
		if (std::strncmp(ptr, "> ", 2) == 0)
			return std::make_pair(quote, ptr + 1);
		// 有序列表
		char* ptr1 = ptr;

		while (*ptr1 >= '0' && *ptr1 <= '9')
			++ptr1;
		/*while (*ptr1 && (isdigit(*ptr1)))
			ptr1++;*/

		if (ptr != ptr1 && *ptr1 == '.' && *(ptr1 + 1) == ' ')
			return std::make_pair(ol, ptr1 + 1);

		// 否则是普通段落
		return std::make_pair(paragraph, src);
	}

	// 类型获取
	// 判断是否为标题
	// 判断是否为图片
	// 判断是否为超链接

	inline bool isHeading(node * v) {
		return (v->type >= h1 && v->type <= h6);
	}
	inline bool isImage(node * v) {
		return v->type == image;
	}
	inline bool isHref(node * v) {
		return v->type == href;
	}

	// 节点搜索
	// 给定一个深度查找想要的节点
	// depth : 深度
	// output : 节点的指针
	inline node* findnode(int depth) {
		node* ptr = root;
		while (!ptr->ch.empty() && depth != 0) {
			ptr = ptr->ch.back();
			if (ptr->type == li)
				depth--;
		}
		return ptr;
	}

	// 新增节点的插入
	void Cins(Cnode * v, int x, const std::string & hd, int tag) {
		int n = static_cast<int>(v->ch.size());
		if (x == 1) {
			v->ch.push_back(new Cnode(hd));
			v->ch.back()->tag = "tag" + std::to_string(tag);
			return;
		}
		if (!n || v->ch.back()->heading.empty())
			v->ch.push_back(new Cnode(""));
		Cins(v->ch.back(), x - 1, hd, tag);
	}

	// 向指定节点插入要处理的串
	void insert(node* v, const std::string& src) {
		int n = static_cast<int>(src.size());
		bool incode = false,
			inem = false,
			instrong = false,
			inautolink = false;
		v->ch.push_back(new node(nul));

		for (int i = 0; i < n; ++i) {
			char ch = src[i];
			if (ch == '\\') {
				ch = src[++i];
				v->ch.back()->elem[0] += std::string(1, ch);
				continue;
			}

			//处理行内代码
			if (ch == '`'
				&& !inautolink) {
				incode ? v->ch.push_back(new node(nul)) : v->ch.push_back(new node(code));
				incode = !incode;
				continue;
			}

			// 处理加粗
			if (ch == '*' 
				&& i < n - 1 && src[i + 1] == '*' 
				&& !incode 
				&& !inautolink) {
				instrong ? v->ch.push_back(new node(nul)) : v->ch.push_back(new node(strong));
				instrong != instrong;
				continue;
			}
			// 斜体
			if (ch == '_' 
				&& !incode 
				&& !inautolink) {
				inem ? v->ch.push_back(new node(nul)) : v->ch.push_back(new node(em));
				inem != inem;
				continue;
			}
			// 图片
			if (ch == '!'
				&& (i < n - 1 && src[i + 1] == '[')
				&& !inautolink
				&& !incode
				&& !inem
				&& !instrong) {
				v->ch.push_back(new node(image));
				for (i + 2; i < n - 1 && src[i]!=']'; ++i) {
					v->ch.back()->elem[0] +=std::string(1, src[i]);
				}
				++i;// src[i] == '('  暂时不检查![]( 这种情况
				for (i++; i < n - 1 && src[i] != ' ' && src[i] != ')'; ++i)
					v->ch.back()->elem[1] += std::string(1, src[i]);
				if(src[i] != ')')
					for (i++; i < n - 1 && src[i] != ')'; ++i) {
						if (src[i] != '"')
							v->ch.back()->elem[2] += std::string(1, src[i]);
					}
				v->ch.push_back(new node(nul));
				continue;
			}
			// 超链接
			if (ch == '['
				&& !incode
				&& !instrong
				&& !inem
				&& !inautolink) {
				v->ch.push_back(new node(href));
				for (i++; i < n - 1 && src[i] != '['; ++i) {
					v->ch.back()->elem[0] += std::string(1, src[i]);
				}
				++i;
				for (i++; i < n - 1 && src[i] != ' ' && src[i] != '['; ++i) {
					v->ch.back()->elem[1] += std::string(1,src[i]);
				}
				if (src[i] != '(') {
					for (i++; i < n - 1 && src[i] != ')'; i++) {
						if (src[i] != '"')
							v->ch.back()->elem[2] += std::string(1, src[i]);
					}
				}
				v->ch.push_back(new node(nul));
				continue;
			}
		}
		if (src.size() >= 2)
			if (src.at(src.size() - 1) == ' ' && src.at(src.size() - 2) == ' ')
				v->ch.push_back(new node(br));
	}

	// 换行的处理和段落的生成
	// 判断是否需要换行
	inline bool isCutline(char* src) {
		int count = 0;
		char* ptr = src;
		while (*ptr) {
			if (*ptr != ' ' && *ptr != '\t' && *ptr != '-')
				return false;
			if (*ptr == '-')
				count++;
			ptr++;
		}
		// 出现--- 增加分割线，换行
		return count >= 3;
	}

	// 得到段落文本后生成
	inline void mkpara(node* v) {
		if (v->ch.size() >= 1u && v->ch.back()->type == paragraph)
			return;
		if(v->type == paragraph)
			return;
		if (v->type == nul) {
			v->type = paragraph;
			return;
		}
		node* x = new node(paragraph);
		x->ch = v->ch;
		v->ch.clear();
		v->ch.push_back(x);
	}

	// 语法树的遍历，对目录的遍历与对正文内容的遍历不一样
	// 正文内容的遍历
	void dfs(node* v) {
		if (v->type == paragraph && v->elem[0].empty() && v->ch.empty())
			return;
		content += frontTag[v->type];
		bool flag = true;

		// 遍历树，内容转成html格式
		// 标题
		if (isHeading(v)) {
			content += "id=\"" + v->elem[0] + "\">";
			flag = false;
		}

		// 超链接
		if (isHref(v)) {
			content += "<a href=\"" + v->elem[1] + "\" title=\"" + v->elem[2] + "\">" + v->elem[0] + "</a>";
			flag = false;
		}

		// 处理图片
		if (isImage(v)) {
			content += "<img alt=\"" + v->elem[0] + "\" src=\"" + v->elem[1] + "\" title=\"" + v->elem[2] + "\" />";
			flag = false;
		}

		//  都不是则直接添加内容
		if (flag) {
			content += v->elem[0];
			flag = false;
		}

		// 递归遍历所有
		for (int i = 0; i < static_cast<int>(v->ch.size()); ++i) {
			dfs(v->ch[i]);
		}
		// 拼接结束标签
		content += backTag[v->type];
	}

	// 目录的遍历
	void Cdfs(Cnode* v, std::string index) {
		TOC += "<li>\n";
		TOC += "<a href=\"#" + v->tag + "\">" + index + " " + v->heading + "</a>\n";
		int n = static_cast<int>(v->ch.size());
		if (n) {
			TOC += "<ul>\n";
			for (int i = 0; i < n; ++i) {
				Cdfs(v->ch[i], index + std::to_string(i + 1) + ".");
			}
			TOC += "</ul>\n";
		}
		TOC += "</li>\n";
	}









};



#endif //CODE_D_CPP_PROJECTS_H_