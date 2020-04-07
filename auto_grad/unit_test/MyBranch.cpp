#include "MyBranch.h"
#include <sstream>
using namespace AG;

MyBranch::MyBranch(std::string type, std::string id) :BranchNode(type, id) {
	m_parent_compute_node = 0;
}

Node* MyBranch::choose_node(int idx, Graph* compute_graph) {
	if (idx == 0) {
		return m_parent_compute_node;
	}
	else {
		std::ostringstream oss;
		oss << (idx - 1) << ":";
		std::string name = "SquareSum:1" + oss.str();
		return compute_graph->get_node(name);
	}
}