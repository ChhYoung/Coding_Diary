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
	std::unordered_map<std::string, Node*> m_node_map; //����ͼ�нڵ��ֵ�
public:
	Graph(){}
	std::unordered_map<std::string, std::vector<Node*>> m_adj_table; //����ͼ���ڽӱ�
	std::unordered_map<std::string, std::vector<Node*>> m_reverse_table; // ����ͼ��ת��ͼ
	void add_node(std::string parent_name, Node* node);//����ͼ����ӽڵ�
	Node* get_node(std::string name); // ����ͼ�в��ҽڵ�
	void build_subgraph(std::vector<Node*>& endnode_list); // ������ֹ�ڵ��б�����ͼ����ǰ�ڵ㸸�ڵ�����.  ������ڵ����Ϲ���
	void topological_sort(std::unordered_map<std::string, std::vector<Node*>>& adj_table, std::vector<Node*>& result);//��������
	void build_reverse_graph(); //����ת��ͼ
	void get_endnode(std::vector<Node*>& endNode_list); // ��ȡת��ͼ��û��ǰ���Ľڵ㡣���õ�ԭͼ������ڵ㡣
	virtual ~Graph(); 
};

}
#endif // !GRAPH_H_

