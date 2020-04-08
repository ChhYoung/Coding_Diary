#include "../../include/op_node/RnnInputX.h"
#include <stdlib.h>
#include <iostream>
using namespace AG;

RnnInputX::RnnInputX(std::string type, std::string id, std::string idx, std::vector<Tensor*> input_data) :OperatorNode(type, id, idx) {
	m_data_ptr = 0;
	m_data = input_data;
}

void RnnInputX::op() {
	int batch_size = 1;
	std::vector<int> shape(2); shape[0] = batch_size; shape[1] = 2;
	
	float* data = new float[2 * batch_size];
	for (int i = 0; i < batch_size; ++i) {
		Tensor* a = m_data[m_data_ptr];
		Tensor* b = m_data[m_data_ptr + 1];
		int idx = std::atoi(m_name[2].c_str());
		data[i * 2] = a->m_tensor[idx];
		data[i * 2 + 1] = (m_data_ptr + 2) % m_data.size();
		m_data_ptr = (m_data_ptr + 2)%m_data.size();
	}
	m_output = new Tensor(shape, data);
}

void RnnInputX::release_tensor() {
	if (m_sum_grad != nullptr) {
		delete  m_sum_grad;
		m_sum_grad = nullptr;
	}
	delete m_output;
	m_output = nullptr;
}

RnnInputX::~RnnInputX() {
	release_tensor();
}
