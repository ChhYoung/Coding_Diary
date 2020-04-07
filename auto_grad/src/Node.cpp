#include "../include/Node.h"
using namespace AG;

Node::Node(std::string type, std::string id) {
	m_name.push_back(type);
	m_name.push_back(id);
	m_invisible = 0;
}

std::string Node::get_name() {
	std::string name = "";
	for (int i = 0; i < this->m_name.size(); ++i) {
		name += this->m_name[i] + ":";
	}
	return name;
}

Node::~Node() {
}