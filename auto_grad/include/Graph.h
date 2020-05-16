#ifndef GRAPH_H_
#define GRAPH_H_
#include "Node.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

namespace AG {

class Graph {
protected:
	std::unordered_map<std::string, Node*> m_node_map; //计算图中节点字典
public:
	Graph(){}
	std::unordered_map<std::string, std::vector<Node*>> m_adj_table; //计算图的邻接表
	std::unordered_map<std::string, std::vector<Node*>> m_reverse_table; // 计算图的转置图
	void add_node(std::string parent_name, Node* node);//计算图中添加节点
	Node* get_node(std::string name); // 计算图中查找节点
	void build_subgraph(std::vector<Node*>& endnode_list); // 根据终止节点列表构造子图，当前节点父节点上溯.  从输出节点向上构造
	void topological_sort(std::unordered_map<std::string, std::vector<Node*>>& adj_table, std::vector<Node*>& result);//拓扑排序
	void build_reverse_graph(); //构建转置图
	void get_endnode(std::vector<Node*>& endNode_list); // 获取转置图中没有前驱的节点。即得到原图的输出节点。
	virtual ~Graph(); 
};

}
#endif // !GRAPH_H_

