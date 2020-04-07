#include "../../include/op_node/Sigmoid.h"
#include <cmath>
using namespace AG;

Sigmoid::Sigmoid(std::string type, std::string id, std::string idx) : OperatorNode(type,id,idx) {
}

void Sigmoid::op() {
	Tensor* parent_output = ((OperatorNode*)m_parents[0])->m_output;
	this->m_output = new Tensor(parent_output->m_shape);
	for (int i = 0; i < parent_output->m_size; ++i) {
		this->m_output->m_tensor[i] = 1.0 / (1 + std::pow(2.718, 0 - parent_output->m_tensor[i]));
	}
}

void Sigmoid::grad_op() {
	Tensor* parent_output = ((OperatorNode*)m_parents[0])->m_output;
	std::vector<int> shape(2);
	shape[0] = this->m_output->m_size;
	shape[1] = parent_output->m_size;
	Tensor grad = Tensor(shape);

	std::vector<int> idxs(2);

	// grad
	for (int i = 0; i < this->m_output->m_size; ++i) {
		for (int j = 0; j < parent_output->m_size; ++j) {
			idxs[0] = i;
			idxs[1] = j; 
			if (i == j) {
				grad.set_value(idxs, this->m_output->m_tensor[i] * (1 - this->m_output->m_tensor[i]));
			}
		}
	}
	chain_rule(&grad, 0);
}


void Sigmoid::release_tensor() {
	if (m_sum_grad != nullptr) {
		delete m_sum_grad;
		m_sum_grad = nullptr;
	}
	delete m_output;
	m_output = nullptr;
}

Sigmoid::~Sigmoid() {
	release_tensor();
}