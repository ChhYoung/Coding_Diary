#include "../include/BranchNode.h"
#include "../include/op_node/Parameter.h"
#include "../include/Tensor.h"
#include <iostream>
#include <vector>

using namespace AG;

BranchNode::BranchNode(std::string type, std::string id, Node* (*func)(int, Graph*, BranchNode*)) :Node(type, id) {
	m_dep_op_node_name = "";
	choose_node = func;
}