#ifndef VIRTUALGRAPH_H_
#define VIRTUALGRAPH_H_
#include "Graph.h"
#include "ComputeGraph.h"

namespace AG {

class VirtualGraph : public Graph {
public:
	Node* build_compute_graph(Graph* compute_graph, int idx = 0);//构建前向传播计算图
	~VirtualGraph();
};

}

#endif
