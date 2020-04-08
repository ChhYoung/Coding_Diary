#include "../../include/op_node/SquareSum.h"
using namespace AG;

SquareSum::SquareSum(std::string type, std::string id, std::string idx) :OperatorNode(type, id, idx) {
}

void SquareSum::op() {
	Tensor* parent_output = ((OperatorNode*)m_parents[0])->m_output;
	std::vector<int> shape(2);
	shape[0]=1;
	shape[1]=1;

	m_output = new Tensor(shape);
	for (int i = 0; i < parent_output->m_size; ++i) {
		m_output->m_tensor[0] += parent_output->m_tensor[i] * parent_output->m_tensor[i];
	}
}

void SquareSum::grad_op() {
	Tensor* parent_output = ((OperatorNode*)m_parents[0])->m_output;
	std::vector<int> shape(2);
	shape[0]=1;
	shape[1] = parent_output->m_size;

	Tensor grad = Tensor(shape);
	std::vector<int> idxs(2);
	for (int i = 0; i < parent_output->m_size; ++i) {
		idxs[0] = 0;
		idxs[1] = i;
		grad.set_value(idxs, parent_output->m_tensor[i] * 2);
	}
	chain_rule(&grad, 0);
}


void SquareSum::release_tensor() {
	if (m_sum_grad != nullptr) {
		delete m_sum_grad;
		m_sum_grad = nullptr;
	}
	delete m_output;
	m_output = nullptr;
}

SquareSum::~SquareSum() {
	release_tensor();
}

