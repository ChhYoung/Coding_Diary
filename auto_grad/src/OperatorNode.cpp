#include "../include/OperatorNode.h"
#include <iostream>
using namespace AG;

OperatorNode::OperatorNode(std::string type, std::string id, std::string idx):Node(type,id){
	m_name.push_back(idx);
	m_a = 0.2;
	m_sum_grad = nullptr;
	m_output = nullptr;
}

// dependency_sum_grad += now_sum_grad*grad
void OperatorNode::chain_rule(Tensor* grad, int parent_idx) {
	OperatorNode* parent_op_node = (OperatorNode*)m_parents[parent_idx];
	if (parent_op_node->m_sum_grad == nullptr) {
		if (this->m_sum_grad == nullptr) {
			//parent_op_node->m_sum_grad = new Tensor(grad->m_shape, grad->m_tensor);
			// grad 压缩到一行
			std::vector<int> shape(2); shape[0] = 1; shape[1] = grad->m_shape[1];
			parent_op_node->m_sum_grad = new Tensor(shape);
			for (int i = 0; i < grad->m_size; ++i) {
				int idx = i % parent_op_node->m_sum_grad->m_size;
				parent_op_node->m_sum_grad->m_tensor[idx] += grad->m_tensor[i];
			}
		}
		else {
			parent_op_node->m_sum_grad = this->m_sum_grad->matrix_mult(grad);
		}
	}
	else {
		if (this->m_sum_grad == nullptr) {
			//parent_op_node->m_sum_grad->add(grad, parent_op_node->m_sum_grad);
			// grad 压缩到一行
			for (int i = 0; i < grad->m_size; ++i) {
				int idx = i % parent_op_node->m_sum_grad->m_size;
				parent_op_node->m_sum_grad->m_tensor[idx] += grad->m_tensor[i];
			}
		}
		else {
			parent_op_node->m_sum_grad->add(this->m_sum_grad->matrix_mult(grad), parent_op_node->m_sum_grad);
		}
	}
}

void OperatorNode::op() {
}

void OperatorNode::grad_op() {
}

void OperatorNode::update() {
	if (this->m_sum_grad != nullptr && this->m_name[0] == "Parameter") {
		for (int i = 0; i < m_output->m_size; ++i) {
			m_output->m_tensor[i] -= m_a * m_sum_grad->m_tensor[i];
		}
	}
}

void OperatorNode::release_tensor() {
}

OperatorNode::~OperatorNode() {
	//std::cout << "free OperatorNode: " << get_name() << std::endl;
	delete m_sum_grad;
	if (m_name[0] != "Parameter") {
		delete m_output;
	}
}