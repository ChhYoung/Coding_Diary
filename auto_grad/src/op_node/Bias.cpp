#include "../../include/op_node/Bias.h"
#include <iostream>
using namespace AG;
Bias::Bias(std::string type, std::string id, std::string idx):OperatorNode(type,id,idx){
}

void Bias::op() {
	Tensor* parent0_output = ((OperatorNode*)m_parents[0])->m_output;
	Tensor* parent1_output = ((OperatorNode*)m_parents[1])->m_output;// Æ«ÖÃÏòÁ¿

	m_output = nullptr;
	if (parent1_output->m_shape[0] == 1 && parent0_output->m_shape[1] == parent1_output->m_shape[1]) {
		m_output = new Tensor(parent0_output->m_shape,0);
		for (int i = 0; i < parent0_output->m_size; ++i) {
			int j = i % parent1_output->m_size;
			m_output->m_tensor[i] = parent0_output->m_tensor[i] + parent1_output->m_tensor[j];
		}
	}
	if (m_output == nullptr) {
		std::cout << "shape is not match:" << get_name() << std::endl;
	}
}

void Bias::grad_op() {
    Tensor* parent0_output = ((OperatorNode*)m_parents[0])->m_output;
    Tensor* parent1_output = ((OperatorNode*)m_parents[1])->m_output;
    std::vector<int> shape0(2);
    shape0[0] = m_output->m_size;
    shape0[1] = parent0_output->m_size;
    std::vector<int> shape1(2);
    shape1[0] = m_output->m_size;
    shape1[1] = parent1_output->m_size;

    Tensor grad0 = Tensor(shape0);
    Tensor grad1 = Tensor(shape1);

    std::vector<int> idxs(2);
    // grad0
    for (int i = 0; i < m_output->m_size; ++i) {
        for (int j = 0; j < parent0_output->m_size; ++j) {
            if (i == j) {
                idxs[0] = i; idxs[1] = j;
                grad0.set_value(idxs, 1);
            }
        }
    }
    // grad1
    for (int i = 0; i < m_output->m_size; ++i) {
        for (int j = 0; j < parent1_output->m_size; ++j) {
            if (i % parent1_output->m_size == j) {
                idxs[0] = i; idxs[1] = j;
                grad1.set_value(idxs, 1);
            }
        }
    }

    // chain rule
    chain_rule(&grad0, 0);
    chain_rule(&grad1, 1);
}


void Bias::release_tensor() {
    if (m_sum_grad != nullptr) {
        delete  m_sum_grad;
        m_sum_grad = nullptr;
    }
    delete m_output;
    m_output = nullptr;
}

Bias::~Bias() {
    release_tensor();
}