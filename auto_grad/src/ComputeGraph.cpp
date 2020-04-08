#include "../include/ComputeGraph.h"
#include "../include/OperatorNode.h"
#include <iostream>
using namespace AG;

void ComputeGraph::forward_propagation(std::vector<Node*>& result_list) {
	std::vector<Node*> topo_result;
	topological_sort(m_adj_table, topo_result);
	for (int i = 0; i < topo_result.size(); ++i) {
		((OperatorNode*)topo_result[i])->op();
	}
	//std::vector<Node*> endnode_list;
	//get_endnode(endnode_list); // 转置图中入度为0的节点即为输出
	//for (int i = 0; i < endnode_list.size(); ++i) {
	//	result_list.push_back(((OperatorNode*)endnode_list[i])->m_output);
	//}
	get_endnode(result_list);
}
void ComputeGraph::back_propagation() {
	std::vector<Node*> topo_result;
	topological_sort(m_reverse_table, topo_result);
	for (int i = 0; i < topo_result.size(); ++i) {
		((OperatorNode*)topo_result[i])->grad_op();
	}
	// 更新权值
	for (int i = 0; i < topo_result.size(); ++i) {
		((OperatorNode*)topo_result[i])->update();
	}
}
void ComputeGraph::release_tensor() {
	std::unordered_map<std::string, Node*>::iterator node_map_it = m_node_map.begin();
	while (node_map_it != m_node_map.end()) {
		//// 释放sum_grad
		//if (((OperatorNode*)(node_map_it->second))->m_sum_grad != 0) {
		//	delete ((OperatorNode*)(node_map_it->second))->m_sum_grad;
		//	((OperatorNode*)(node_map_it->second))->m_sum_grad = 0;
		//	//std::cout << "release grad " << node_map_it->first << std::endl;
		//}
		//if (node_map_it->second->m_name[0] != "Parameter" && node_map_it->second->m_name[0] != "Input") { // 释放非参数节点的output
		//	delete ((OperatorNode*)(node_map_it->second))->m_output;
		//	((OperatorNode*)(node_map_it->second))->m_output = 0;
		//	//std::cout << "release output " << node_map_it->first << std::endl;
		//}
		((OperatorNode*)(node_map_it->second))->release_tensor();
		++node_map_it;
	}
}
ComputeGraph::~ComputeGraph() {
	std::cout << "compute graph free " << std::endl;
}