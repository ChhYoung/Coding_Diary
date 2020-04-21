#ifndef COMPUTEGRAPH_H_
#define COMPUTEGRAPH_H_
#include "Graph.h"
#include "Node.h"
#include <vector>

namespace AG {

class ComputeGraph : public Graph {
public:
	void forward_propagation(std::vector<Node*>& result_list);
	void back_propagation();
	void release_tensor();
	~ComputeGraph();
};

}



#endif //!COMPUTEGRAPH_H_
