#ifndef ADD_H_
#define ADD_H_
#include "../OperatorNode.h"
#include <string>

namespace AG {
class Add : public OperatorNode {
public:
	Add(std::string type, std::string id, std::string idx);
	void op();
	void grad_op();
	~Add();
	void release_tensor();
};

}


#endif 
