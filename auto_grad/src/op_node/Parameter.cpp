#include "../../include/op_node/Parameter.h"
using namespace AG;

Parameter::Parameter(std::string type, std::string id, std::string idx, Tensor* data, int share_data) :OperatorNode(type, id, idx) {
	m_share_data = share_data;
	if (share_data == 0) {
		m_output = new Tensor(data->m_shape, data->m_tensor);
	}
	else {
		m_output = data;
	}
}

void Parameter::release_tensor() {
	if (m_sum_grad != nullptr) {
		delete m_sum_grad;
		m_sum_grad = nullptr;
	}
}

Parameter::~Parameter() {
	release_tensor();
	if (m_share_data == 0) {
		delete m_output;
	}
	m_output = 0;
}