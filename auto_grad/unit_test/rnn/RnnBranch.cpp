#include "RnnBranch.h"
#include "../../include/op_node/Input.h"
#include <sstream>
using namespace AG;

RnnBranch::RnnBranch(std::string type, std::string id) :BranchNode(type, id) {
}

Node* RnnBranch::choose_node(int idx, Graph* compute_graph) {
	std::ostringstream oss;
	// 首次循环，向后继提供一个初始化矩阵
	// 以后的则向Add:1提供Mult:h这个虚拟节点生成计算节点
	if (idx == 0) {
		int batch_size = 1;
		std::vector<int> shape(2);
		shape[0] = batch_size; shape[1] = 4;
		Tensor* init_tensor = new Tensor(shape);
		std::vector<Tensor*> data;
		data.push_back(init_tensor);
		Node* init_input = new Input("Input", "init", "0", data);
		compute_graph->add_node("", init_input);
		((Input*)init_input)->op();
		return init_input;
	}
	else {
		oss << (idx - 1) << ":";
		std::string name = "Mult:h:" + oss.str();
		return compute_graph->get_node(name);
	}
}