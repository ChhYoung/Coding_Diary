#include "../include/LoopNode.h"
#include <iostream>
using namespace AG;

LoopNode::LoopNode(std::string type, std::string id) : Node(type, id){
	m_sub_vgraph = new VirtualGraph();
	m_end_compute_node = nullptr;
}

//  初始化循环，为循环子图中的一些节点补上节点依赖
void LoopNode::init(Graph* compute_graph) {
}

//成立返回1， 否则返回0
int LoopNode::condition(Graph* compute_graph, int idx) {
	return 1;
}

// 内循环
void LoopNode::inner_loop(Graph* compute_graph) {
	int idx = 0;
	init(compute_graph); //初始化循环
	while (condition(compute_graph, idx) == 0) {
		// 每次循环时动态生成计算图
		m_end_compute_node = m_sub_vgraph->build_compute_graph(compute_graph, idx);
		++idx;
	}
}

LoopNode::~LoopNode() {
	std::cout << "free LoopNode: " << get_name() << std::endl;
	delete m_sub_vgraph;
	m_sub_vgraph = nullptr;
	m_end_compute_node = nullptr;
}