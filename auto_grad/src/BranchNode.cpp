#include "../include/BranchNode.h"
#include "../include/op_node/Parameter.h"
#include "../include/Tensor.h"
#include <iostream>
#include <vector>

using namespace AG;

BranchNode::BranchNode(std::string type, std::string id):Node(type,id){}

Node* BranchNode::choose_node(int idx, Graph* compute_graph) {
	return nullptr;
}