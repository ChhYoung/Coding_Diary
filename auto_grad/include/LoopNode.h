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
	virtual void init(Graph* compute_graph); //  初始化循环，为循环子图中的一些节点补上节点依赖
	virtual int condition(Graph* compute_graph, int idx);//成立返回1， 否则返回0
	virtual void inner_loop(Graph* compute_graph); // 内循环
	virtual ~LoopNode();
};

}




#endif