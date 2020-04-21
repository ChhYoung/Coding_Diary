#include "RnnLoop.h"
using namespace AG;
RnnLoop::RnnLoop(std::string type, std::string id) :LoopNode(type, id) {
}

int RnnLoop::condition(Graph* compute_graph, int idx) {
	if (idx < 8) {
		return 0;
	}
	else {
		return 1;
	}
}