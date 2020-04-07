#include "../../include/op_node/Mult.h"
#include <iostream>
using namespace AG;

Mult::Mult(std::string type, std::string id, std::string idx) :OperatorNode(type, id, idx){
}

void Mult::op() {
	Tensor* parent0_output = ((OperatorNode*)m_parents[0])->m_output;
	Tensor* parent1_output = ((OperatorNode*)m_parents[1])->m_output;
	m_output = parent0_output->matrix_mult(parent1_output);
	if (m_output == 0) {
		std::cout << "shape is not match: " << get_name() << std::endl;
	}
}
// Z = XY
// vec(dZ) = (Y^t OX I_m)vec(dX) + (I_q OX X)vec(dY)
void Mult::grad_op() {
	Tensor* parent0_output = ((OperatorNode*)m_parents[0])->m_output;
	Tensor* parent1_output = ((OperatorNode*)m_parents[1])->m_output;
	std::vector<int> shape0(2);//mq*mn
	shape0[0] = m_output->m_size; // mq
	shape0[1] = parent0_output->m_size; // mn
	std::vector<int> shape1(2);//mq*nq
	shape1[0] = m_output->m_size;//mq
	shape1[1] = parent1_output->m_size;//nq

	Tensor grad0 = Tensor(shape0);  // 由Kronecker得大小
	Tensor grad1 = Tensor(shape1);

	std::vector<int> idxs0(2);
	std::vector<int> idxs1(2);
	// grad 0--->[Y[j,i] * I_m]
	for (int i = 0; i < m_output->m_shape[0]; ++i) {//m
		for (int j = 0; j < m_output->m_shape[1]; ++j) {//q
			for (int l = 0; l < parent0_output->m_shape[0]; ++l) {//m
				for (int k = 0; k < parent0_output->m_shape[1]; ++k) {//n
					idxs0[0] = i * m_output->m_shape[1] + j;//i*q+j, max=(m-1)q+q=mq
					idxs0[1] = i * parent0_output->m_shape[1] + k; // i*n+k , max=(m-1)n+n=mn
					if (i == l) {
						idxs1[0] = k;
						idxs1[1] = j;
						grad0.set_value(idxs0, parent1_output->get_value(idxs1));
					}
					else {
						grad0.set_value(idxs0, 0);
					}
				}
			}
		}
	}

	// gard 1
	for (int i = 0; i < m_output->m_shape[0]; ++i) {
		for (int j = 0; j < m_output->m_shape[1]; ++j) {
			for (int l = 0; l < parent0_output->m_shape[0]; ++l) {
				for (int m = 0; m < parent0_output->m_shape[1]; ++m) {
					idxs0[0] = i * m_output->m_shape[1] + j;
					idxs0[1] = l * parent1_output->m_shape[1] + m;
					if (j == m) {
						idxs1[0] = i;
						idxs1[1] = l;
						grad1.set_value(idxs0, parent0_output->get_value(idxs1));
					}
					else {
						grad1.set_value(idxs0, 0);
					}
				}
			}
		}
	}

	// chain rule
	chain_rule(&grad0, 0);
	chain_rule(&grad1, 1);
}

void Mult::release_tensor() {
	if (m_sum_grad != nullptr) {
		delete  m_sum_grad;
		m_sum_grad = nullptr;
	}
	delete m_output;
	m_output = nullptr;
}

Mult::~Mult() {
	release_tensor();
}