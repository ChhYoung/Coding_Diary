#include"../../include/op_node/Minus.h"
#include <iostream>
#include <vector>
using namespace AG;
Minus::Minus(std::string type, std::string id, std::string idx) : OperatorNode(type, id, idx) {
}

void Minus::op() {
    Tensor* parent0_output = ((OperatorNode*)m_parents[0])->m_output;
    Tensor* parent1_output = ((OperatorNode*)m_parents[1])->m_output;
    this->m_output = parent1_output->scalar_mult(-1.0);
    parent0_output->add(m_output, m_output);
}

void Minus::grad_op() {
    Tensor* parent0_output = ((OperatorNode*)m_parents[0])->m_output;
    Tensor* parent1_output = ((OperatorNode*)m_parents[1])->m_output;
    std::vector<int> shape0(2);
    shape0[0] = this->m_output->m_size;//pq
    shape0[1] = parent0_output->m_size;//mn
    std::vector<int> shape1(2);
    shape1[0] = this->m_output->m_size;
    shape1[1] = parent1_output->m_size;

    Tensor grad0 = Tensor(shape0);
    Tensor grad1 = Tensor(shape1);

    std::vector<int> idxs(2);
    // grad 0
    for (int i = 0; i < this->m_output->m_size; ++i) {
        for (int j = 0; j < parent0_output->m_size; ++j) {
            if (i == j) {
                idxs[0] = i; idxs[1] = j;
                grad0.set_value(idxs, 1);
            }
        }
    }

    // grad 1
    for (int i = 0; i < this->m_output->m_size; ++i) {
        for (int j = 0; j < parent1_output->m_size; ++j) {
            if (i == j) {
                idxs[0] = i; idxs[1] = j;
                grad1.set_value(idxs, -1);
            }
        }
    }

    // chain rule
    chain_rule(&grad0, 0);
    chain_rule(&grad1, 1);
}

void Minus::release_tensor() {
    if (m_sum_grad != nullptr) {
        delete  m_sum_grad;
        m_sum_grad = nullptr;
    }
    delete m_output;
    m_output = nullptr;
}

Minus::~Minus() {
    release_tensor();
}