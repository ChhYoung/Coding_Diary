#ifndef NODE_H_
#define NODE_H_
#include <vector>
#include <string>

namespace AG{

class Node {
public:
	std::vector<std::string> m_name;
	std::vector<Node*> m_parents; // �����ڵ��б�
	int m_invisible; // 0: �ɼ��� 1: ���ɼ�

	virtual std::string get_name();
	Node(std::string type, std::string id);
	virtual ~Node();
};


}
#endif // NODE_H_