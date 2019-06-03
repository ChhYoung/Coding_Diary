#include<fostream>          // std::ofstream
#include"mdtransformer.hpp"

int main(){
    // 装载markdown测试文件
    MarkdownTranform transformer("test,md");

    // getTableOfCOntents()方法获取Markdown文件的HTML格式
    // 获取目录
    std::string table = transformer.getTableOfCOntents();

    // getContents()方法获取Markdown转成HTML后的内容
    std::string contents = transformer.getContents();

    // 准备要写入的HTML 文件头尾信息
    // 头信息
    std::string head = "<!DOCTYPE html><html><head>\
            <mate charset=\"utf-8\">\
            <title>Markdown</title>\
            <link rel=\"stylesheet\" href=\"github-markdown.css\">\
        </head><body><article class=\"markdown-body\">";
    // 尾信息
    std::string end = "</article></body></html>";

    // 结果写到文件中
    std::ofstream out;
    out.open("output/index.html");

    // 将转换的内容构造到 HTML的<article></article>标签内部
    out << head + table + contents + end;
    out.close();
    return 0;
}