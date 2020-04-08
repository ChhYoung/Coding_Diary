#include "../include/VirtualNode.h"
#include "../include/BranchNode.h"
#include "../include/LoopNode.h"
#include "../include/op_node/Add.h"
#include "../include/op_node/Input.h"
#include "../include/op_node/Mult.h"
#include "../include/op_node/Minus.h"
#include "../include/op_node/SquareSum.h"
#include "../include/op_node/Sigmoid.h"
#include "../include/op_node/Parameter.h"
#include "../include/op_node/Bias.h"
#include "../include/op_node/AbsSum.h"
#include "../include/op_node/RnnInputX.h"
#include "../include/op_node/RnnInputY.h"
#include <sstream>
#include <iostream>

using namespace AG;


VirtualNode::VirtualNode(std::string type, std::string id,int share_parameter) : Node(type,id){
	m_share_parameter = share_parameter;
}

void VirtualNode::get_parents_op_nodes(int idx, Graph* compute_graph, std::vector<Node*>& node_list) {
	std::ostringstream oss;
	oss << idx << ":";
	for (int i = 0; i < m_parents.size(); ++i) {
		if (m_parents[i]->m_name[0] == "Branch") {
			node_list.push_back(((BranchNode*)m_parents[i])->choose_node(idx, compute_graph));
		}
		else if (m_parents[i]->m_name[0] == "Loop") {
			node_list.push_back(((LoopNode*)m_parents[i])->m_end_compute_node);
		}
		else {
			std::string op_node_name = m_parents[i]->get_name() + oss.str();
			node_list.push_back(compute_graph->get_node(op_node_name));
		}
	}
}

// OperatorNode����
Node* VirtualNode::get_op_node(int idx) {
	std::ostringstream oss;
	oss << idx;
	Node* op_node = nullptr;
	if (m_name[0] == "Add") {
		op_node =  new Add(m_name[0], m_name[1], oss.str());
	}
	else if (m_name[0] == "Input") {
		if (m_input_data.size() == 0) {
			std::cout << "input data is not initialize" << std::endl;
		}
		else {
			op_node = new Input(m_name[0], m_name[1], oss.str(), m_input_data);
		}
	}
	else if (m_name[0] == "Parameter") {
		if (m_data == 0) {
			std::cout << "Parameter node is not initialize" << std::endl;
		}
		else {
			op_node = new Parameter(m_name[0], m_name[1], oss.str(), m_data);
		}
	}
	else if (m_name[0] == "SquareSum") {
		op_node = new SquareSum(m_name[0], m_name[1], oss.str());
	}
	else if (m_name[0] == "Mult") {
		op_node = new Mult(m_name[0], m_name[1], oss.str());
	}
	else if (m_name[0] == "Minus") {
		op_node = new Minus(m_name[0], m_name[1], oss.str());
	}
	else if (m_name[0] == "Sigmoid") {
		op_node = new Sigmoid(m_name[0], m_name[1], oss.str());
	}
	else if (m_name[0] == "Bias") {
		op_node = new Bias(m_name[0], m_name[1], oss.str());
	}
	else if (m_name[0] == "RnnInputX") {
		if (m_input_data.size() == 0) {
			std::cout << "input data is not initialize\n";
		}
		else {
			op_node = new RnnInputX(m_name[0], m_name[1], oss.str(), m_input_data);
		}
	}
	else if (m_name[0] == "RnnInputY") {
		if (m_input_data.size() == 0) {
			std::cout << "input data is not initialize\n";
		}
		else {
			op_node = new RnnInputY(m_name[0], m_name[1], oss.str(), m_input_data);
		}
	}
	else {
		std::cout << "op node name error\n";
	}
	m_op_node_list.push_back(op_node);
	return op_node;
}

VirtualNode::~VirtualNode() {
	//std::cout << "free virtualNode: " << get_name() << std::endl;
	if (m_data != nullptr) {
		delete m_data;
	}
	for (int i = 0; i < m_input_data.size(); ++i){
		delete m_input_data[i];
	}
}