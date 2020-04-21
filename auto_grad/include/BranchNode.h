#ifndef BRANCHNODE_H_
#define BRANCHNODE_H_
#include "Node.h"
#include "Graph.h"

namespace AG {

class BranchNode : public Node {
public:
	// BranchNode作为循环的一部分时间有时需要BranchNode
	// 所在的LoopNode提供初始化的计算节点名称，从而实现循环级联
	std::string m_dep_op_node_name;
	Node* (*choose_node)(int idx, Graph* compute_graph, BranchNode* branch_node); //  分支选择函数
	BranchNode(std::string type, std::string id, Node* (*func)(int, Graph*, BranchNode*));
};

}



#endif