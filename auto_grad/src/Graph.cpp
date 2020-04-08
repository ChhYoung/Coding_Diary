#include <iostream>
#include "../include/Graph.h"

using namespace AG;

void Graph::add_node(std::string parent_name, Node* node) {
	this->m_node_map[node->get_name()] = node; //节点加入字典
	if (parent_name != "") {
		if (this->m_node_map.end() != this->m_node_map.find(parent_name)) {
			Node* parent_node = this->m_node_map[parent_name];
			node->m_parents.push_back(parent_node);
			m_adj_table[parent_name].push_back(node);//节点加入邻接表
		}
		else {
			std::cout << "parent node is not in graph" << std::endl;
		}
	}
}

Node* Graph::get_node(std::string name) {
	if (this->m_node_map.end() == this->m_node_map.find(name)) {
		return nullptr;
	}
	else {
		return this->m_node_map[name];
	}
}

void Graph::build_subgraph(std::vector<Node*> endnode_list) {
	std::unordered_map<std::string, Node*>::iterator node_map_it = this->m_node_map.begin();
	while (node_map_it != this->m_node_map.end()) { //所有节点设置为不可见
		node_map_it->second->m_invisible = 1;
		++node_map_it;
	}
	// 构造子图
	std::queue<Node*> q;
	std::unordered_set<Node*> visit;
	std::vector<Node*>::iterator endnode_list_it = endnode_list.begin();
	while (endnode_list_it != endnode_list.end()) {
		q.push(*endnode_list_it);
		visit.insert(*endnode_list_it);
		++endnode_list_it;
	}
	while (!q.empty()) {
		Node* node = q.front();
		q.pop();
		node->m_invisible = 0; // 将子图的节点设为可见
		for (int i = 0; i < node->m_parents.size(); ++i) {
			if (visit.find(node->m_parents[i]) == visit.end()) {
				visit.insert(node->m_parents[i]);
				q.push(node->m_parents[i]);
			}
		}
	}
}

void Graph::topological_sort(std::unordered_map<std::string, std::vector<Node*>>& adj_table, std::vector<Node*>& result) {
	std::unordered_map<std::string, int> indegree; // 存储每个节点的入度
	std::unordered_map<std::string, Node*>::iterator node_map_it = m_node_map.begin();
	while (node_map_it != m_node_map.end()) { 
		indegree[node_map_it->first] = 0;
		++node_map_it;
	}
	std::unordered_map<std::string, std::vector<Node*>>::iterator adj_table_it = adj_table.begin();
	while (adj_table_it != adj_table.end()) { // 由邻接表计算每个节点的入读
		for (int i = 0; i < adj_table_it->second.size(); ++i) {
			++indegree[(adj_table_it->second)[i]->get_name()];
		}
		++adj_table_it;
	}

	std::queue<Node*> q;
	std::unordered_map<std::string, int>::iterator indegree_it = indegree.begin();
	while (indegree_it != indegree.end()) {
		if (indegree_it->second == 0) { // 将入度为零的放入队列中
			q.push(m_node_map[indegree_it ->first]);
		}
		++indegree_it;
	}

	while (!q.empty()) {
		Node* node = q.front();
		q.pop();
		if (node->m_invisible == 0) { //可见节点加入result
			result.push_back(node);
		}
		std::vector<Node*> adj_nodes = adj_table[node->get_name()];
		for (int i = 0; i < adj_nodes.size(); ++i) { // 当前节点的后继的入度减1，再将入度0的加入队列
			--indegree[(adj_nodes[i])->get_name()];
			if (indegree[(adj_nodes[i])->get_name()] == 0) {
				q.push(adj_nodes[i]);
			}
		}
	}
}

void Graph::build_reverse_graph() {
	std::unordered_map<std::string, std::vector<Node*>>::iterator adj_table_it = this->m_adj_table.begin();
	while (adj_table_it != this->m_adj_table.end()) {
		Node* parent = this->m_node_map[adj_table_it->first];
		std::vector<Node*> adj_nodes = adj_table_it->second;
		for (int i = 0; i < adj_nodes.size(); ++i) {
			std::string name = (adj_nodes[i])->get_name();
			this->m_reverse_table[name].push_back(parent);
		}
		++adj_table_it;
	}
}

void Graph::get_endnode(std::vector<Node*>& endNode_list) {
	std::unordered_map<std::string, std::vector<Node*>>::iterator reverse_table_it = this->m_reverse_table.begin();
	std::unordered_map<std::string, Node*>::iterator node_map_it = m_node_map.begin();
	std::unordered_map<std::string, int> indegree; // 转置表节点入度
	while (node_map_it != this->m_node_map.end()) {
		indegree[node_map_it->first] = 0;
		++node_map_it;
	}

	while (reverse_table_it != this->m_reverse_table.end()) { // 转置表入度
		std::vector<Node*> adj_nodes = reverse_table_it->second;
		for (int i = 0; i < adj_nodes.size(); ++i) {
			++indegree[(adj_nodes[i])->get_name()];
		}
		++reverse_table_it;
	}

	std::unordered_map<std::string, int>::iterator indegree_it = indegree.begin();
	while (indegree_it != indegree.end()) {
		if (indegree_it->second == 0) {
			endNode_list.push_back(m_node_map[indegree_it->first]);
		}
		++indegree_it;
	}
}

Graph::~Graph() {
	std::cout << "free node_map" << std::endl;
	std::unordered_map<std::string, Node*>::iterator node_map_it = this->m_node_map.begin();
	while (node_map_it != m_node_map.end()) {
		delete node_map_it->second;
		node_map_it->second = 0;
		++node_map_it;
	}
}


