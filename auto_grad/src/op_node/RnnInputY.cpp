#include "../../include/op_node/RnnInputY.h"
#include <stdlib.h>
using namespace AG;

RnnInputY::RnnInputY(std::string type, std::string id, std::string idx, std::vector<Tensor*> input_data) :OperatorNode(type, id, idx) {
	m_data_ptr = 0;
	m_data = input_data;
}

void RnnInputY::op() {
	int batch_size = 1;
	float* data = new float[1 * batch_size];
	std::vector<int> shape(2); shape[0] = batch_size; shape[1] = 1;
	for (int i = 0; i < batch_size; ++i) {
		Tensor* a = m_data[m_data_ptr];
		int idx = std::atoi(m_name[2].c_str());
		data[i] = a->m_tensor[idx];
		m_data_ptr = (m_data_ptr + 1) % m_data.size();
	}
	m_output = new Tensor(shape, data);
}

void RnnInputY::release_tensor() {
	if (m_sum_grad != nullptr) {
		delete m_sum_grad;
		m_sum_grad = nullptr;
	}
	delete m_output;
	m_output = nullptr;
}

RnnInputY::~RnnInputY() {
	release_tensor();
}