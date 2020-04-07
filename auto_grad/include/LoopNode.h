#ifndef LOOPNODE_H_
#define LOOPNODE_H_
#include "Node.h"
#include "VirtualGraph.h"

namespace AG {

class LoopNode : public Node {
public:
	VirtualGraph* m_sub_vgraph;
	Node* m_end_compute_node;
	LoopNode(std::string type, std::string id);
	virtual void init(Graph* compute_graph); //  ��ʼ��ѭ����Ϊѭ����ͼ�е�һЩ�ڵ㲹�Ͻڵ�����
	virtual int condition(Graph* compute_graph, int idx);//��������1�� ���򷵻�0
	virtual void inner_loop(Graph* compute_graph); // ��ѭ��
	virtual ~LoopNode();
};

}




#endif