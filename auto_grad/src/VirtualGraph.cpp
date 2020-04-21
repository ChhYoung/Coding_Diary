#include "../include/VirtualGraph.h"
#include "../include/VirtualNode.h"
#include "../include/LoopNode.h"
#include "../include/OperatorNode.h"
#include <unordered_map>
#include <iostream>
using namespace AG;

Node* VirtualGraph::build_compute_graph(Graph* compute_graph, int idx ) {
	std::vector<Node*> topo_result;
	topological_sort(m_adj_table, topo_result);
	Node* end_node = nullptr;
	for (int i = 0; i < topo_result.size(); ++i) { //构建
		if (topo_result[i]->m_name[0] == "Loop") {
			LoopNode* loop_node = (LoopNode*)topo_result[i];
			loop_node->inner_loop(compute_graph); //执行循环
			end_node = loop_node->m_end_compute_node;
		}
		else if (topo_result[i]->m_name[0] == "Branch") {
			// 分支节点
		}
		else { 
			// 普通虚拟节点
			VirtualNode* v_node = (VirtualNode*)topo_result[i];
			// 添加无前驱的节点
			if (v_node->m_parents.size() == 0) { //添加入度为0的节点
				Node* op_node = v_node->get_op_node(idx); //构造节点
				compute_graph->add_node("", op_node);//计算图中添加节点
				((OperatorNode*)op_node)->op();//执行计算
				end_node = op_node;
			}
			else {
				// 添加有前驱的节点
				std::vector<Node*> parents_op_node;
				v_node->get_parents_op_nodes(idx, compute_graph, parents_op_node);
				int need_op_node = 1;
				for (int i = 0; i < parents_op_node.size(); ++i) {
					if (parents_op_node[i] == 0) {
						need_op_node = 0; // 存在没有生成依赖的计算节点
					}
				}
				if (need_op_node == 1) { // 计算当前依赖
					Node* op_node = v_node->get_op_node(idx);
					for (int i = 0; i < parents_op_node.size(); ++i) {
						compute_graph->add_node(parents_op_node[i]->get_name(), op_node);
					}
					((OperatorNode*)op_node)->op();
					end_node = op_node;
				}
			}
		}
	}
	return end_node;
}

VirtualGraph::~VirtualGraph() {
	std::cout << "virtual graph free " << std::endl;
	//释放虚拟节点
	std::cout << "virtual graph free" << std::endl;
	std::unordered_map<std::string, Node*>::iterator node_map_it = m_node_map.begin();
	while (node_map_it != m_node_map.end()) {
		delete node_map_it->second;
		node_map_it->second = nullptr;
		++node_map_it;
	}
	m_node_map.clear();
	m_adj_table.clear();
	m_reverse_table.clear();
}