#include "../../include/op_node/Input.h"
using namespace AG;

Input::Input(std::string type, std::string id, std::string idx, std::vector<Tensor*> input_data) : OperatorNode(type,id,idx){
	m_data_ptr = 0;
	m_data = input_data;
}

void Input::op() {
	m_output = m_data[m_data_ptr];
	m_data_ptr = (m_data_ptr + 1) % m_data.size();
}

void Input::release_tensor() {
    if (m_sum_grad != nullptr) {
        delete  m_sum_grad;
        m_sum_grad = nullptr;
    }
}

Input::~Input() {
    release_tensor();
}