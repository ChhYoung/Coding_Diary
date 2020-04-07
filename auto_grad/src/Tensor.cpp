#include "../include/Tensor.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace AG;

Tensor::Tensor(std::vector<int> shape,int need_init) {
	this->m_size = 1;
	for (int i = 0; i < shape.size(); ++i) {
		m_shape.push_back(shape[i]);
		m_size *= shape[i];
	}
	
	m_tensor = new float[m_size];
	if (need_init == 1) {
		for (int i = 0; i < this->m_size; ++i) {
			this->m_tensor[i] = 0.0;
		}
	}
}

Tensor::Tensor(std::vector<int> shape, float data[]) {
	this->m_size = 1;

	for (int i = 0; i < shape.size(); ++i) {
		m_shape.push_back(shape[i]);
		m_size *= shape[i];
	}

	m_tensor = new float[m_size];

	for (int i = 0; i < this->m_size; ++i) {
		this->m_tensor[i] = data[i];
	}
}

float Tensor::get_value(std::vector<int> idxs) {
	int idx = 0;
	int t = 1;
	for (int i = idxs.size() - 1; i >= 0; --i) {
		idx += idxs[i] * t;
		t *= this->m_shape[i];
	}
	return this->m_tensor[idx];
}

void Tensor::set_value(std::vector<int> idxs, float value) {
	int idx = 0;
	int t = 1;
	for (int i = idxs.size() - 1; i >= 0; --i) {
		idx += idxs[i] * t;
		t *= this->m_shape[i];
	}
	m_tensor[idx] = value;
}

Tensor* Tensor::matrix_mult(Tensor* tensor) {
	Tensor* result = nullptr;
	if (this->m_shape[1] == tensor->m_shape[0]) {
		std::vector<int> result_shape(2);
		result_shape[0] = this->m_shape[0];
		result_shape[1] = tensor->m_shape[1];
		result = new Tensor(result_shape,0);
		int idx0 = 0, idx1 = 0, idx2 = 0;
		for (int i = 0; i < this->m_shape[0]; ++i) {
			for (int j = 0; j < tensor->m_shape[1]; ++j) {
				float r = 0;
				for (int k = 0; k < this->m_shape[1]; ++k) {
					// M[i][j] = sum( a[i][k]*b[k][j] )
					idx0 = i * m_shape[1] + k;
					idx1 = k * tensor->m_shape[1] + j;
					r += m_tensor[idx0] * tensor->m_tensor[idx1];
				}
				idx2 = i * tensor->m_shape[1] + j;
				result->m_tensor[idx2] = r;
			}
		}
	}
	return result;
}

Tensor* Tensor::scalar_mult(float scalar) {
	Tensor* result = new Tensor(m_shape,0);
	for (int i = 0; i < this->m_size; ++i) {
		result->m_tensor[i] = this->m_tensor[i] * scalar;
	}
	return result;
}

void Tensor::add(Tensor* tensor, Tensor* result) {
	for (int i = 0; i < tensor->m_size; ++i) {
		result->m_tensor[i] = this->m_tensor[i] + tensor->m_tensor[i];
	}
}

Tensor* Tensor::add(Tensor* tensor) {
	Tensor* result = nullptr;
	int same_shape = 1;
	if (this->m_shape.size() == tensor->m_shape.size()) {
		for (int i = 0; i < this->m_shape.size(); ++i) {
			if (this->m_shape[i] != tensor->m_shape[i]) {
				same_shape = 0;
				break;
			}
		}
	}
	else {
		same_shape = 0;
	}

	if (same_shape == 1) {
		result = new Tensor(this->m_shape,0);
		for (int i = 0; i < this->m_size; ++i) {
			result->m_tensor[i] = this->m_tensor[i] + tensor->m_tensor[i];
		}
	}
	return result;
}

void Tensor::init() {
	srand(time(0));
	for (int i = 0; i < this->m_size; ++i) {
		m_tensor[i] = (rand() % 2000) / 1000.0 - 1.0;
	}
}

void Tensor::display() {
	std::vector<int> idxs0(2);
	for (int i = 0; i < this->m_shape[0]; ++i) {
		for (int j = 0; j < this->m_shape[1]; ++j) {
			idxs0[0] = i; idxs0[1] = j;
			std::cout << get_value(idxs0) << " ";
		}
		std::cout << std::endl;
	}
}

Tensor::~Tensor() {
	delete[]  m_tensor;
}