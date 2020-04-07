#include "../include/LoopNode.h"
#include <iostream>
using namespace AG;

LoopNode::LoopNode(std::string type, std::string id) : Node(type, id){
	m_sub_vgraph = new VirtualGraph();
	m_end_compute_node = nullptr;
}

//  ��ʼ��ѭ����Ϊѭ����ͼ�е�һЩ�ڵ㲹�Ͻڵ�����
void LoopNode::init(Graph* compute_graph) {
}

//��������1�� ���򷵻�0
int LoopNode::condition(Graph* compute_graph, int idx) {
	return 1;
}

// ��ѭ��
void LoopNode::inner_loop(Graph* compute_graph) {
	int idx = 0;
	init(compute_graph); //��ʼ��ѭ��
	while (condition(compute_graph, idx) == 0) {
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