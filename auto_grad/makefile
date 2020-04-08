#all: 

xor_test: obj/xor_test.o obj/Graph.o obj/VirtualGraph.o obj/ComputeGraph.o obj/Node.o obj/VirtualNode.o obj/OperatorNode.o obj/Input.o obj/Add.o obj/Bias.o obj/Mult.o obj/Minus.o obj/SquareSum.o obj/Sigmoid.o obj/AbsSum.o obj/Parameter.o obj/RnnInputX.o obj/RnnInputY.o obj/Tensor.o
	g++ -std=c++11 obj/xor_test.o obj/Graph.o obj/VirtualGraph.o obj/ComputeGraph.o obj/Node.o obj/VirtualNode.o obj/OperatorNode.o obj/Input.o obj/Add.o obj/Bias.o obj/Mult.o obj/Minus.o obj/SquareSum.o obj/Sigmoid.o obj/AbsSum.o obj/Parameter.o obj/RnnInputX.o obj/RnnInputY.o obj/Tensor.o -o xor_test

obj/xor_test.o: unit_test/xor_test.cpp
	g++ -std=c++11 -c unit_test/xor_test.cpp -o obj/xor_test.o
obj/SquareSum.o: src/op_node/SquareSum.cpp
	g++ -std=c++11 -c src/op_node/SquareSum.cpp -o obj/SquareSum.o
obj/Sigmoid.o: src/op_node/Sigmoid.cpp
	g++ -std=c++11 -c src/op_node/Sigmoid.cpp -o obj/Sigmoid.o
obj/Mult.o: src/op_node/Mult.cpp
	g++ -std=c++11 -c src/op_node/Mult.cpp -o obj/Mult.o
obj/Minus.o: src/op_node/Minus.cpp
	g++ -std=c++11 -c src/op_node/Minus.cpp -o obj/Minus.o
obj/Add.o: src/op_node/Add.cpp
	g++ -std=c++11 -c src/op_node/Add.cpp -o obj/Add.o
obj/Bias.o: src/op_node/Bias.cpp
	g++ -std=c++11 -c src/op_node/Bias.cpp -o obj/Bias.o
obj/Input.o: src/op_node/Input.cpp
	g++ -std=c++11 -c src/op_node/Input.cpp -o obj/Input.o
obj/Parameter.o: src/op_node/Parameter.cpp
	g++ -std=c++11 -c src/op_node/Parameter.cpp -o obj/Parameter.o
obj/RnnInputX.o: src/op_node/RnnInputX.cpp
	g++ -std=c++11 -c src/op_node/RnnInputX.cpp -o obj/RnnInputX.o
obj/RnnInputY.o: src/op_node/RnnInputY.cpp
	g++ -std=c++11 -c src/op_node/RnnInputY.cpp -o obj/RnnInputY.o
obj/AbsSum.o: src/op_node/AbsSum.cpp
	g++ -std=c++11 -c src/op_node/AbsSum.cpp -o obj/AbsSum.o
obj/ComputeGraph.o: src/ComputeGraph.cpp
	g++ -std=c++11 -c src/ComputeGraph.cpp -o obj/ComputeGraph.o
obj/VirtualGraph.o: src/VirtualGraph.cpp
	g++ -std=c++11 -c src/VirtualGraph.cpp -o obj/VirtualGraph.o
obj/Graph.o: src/Graph.cpp
	g++ -std=c++11 -c src/Graph.cpp -o obj/Graph.o
obj/OperatorNode.o: src/OperatorNode.cpp 
	g++ -std=c++11 -c src/OperatorNode.cpp -o obj/OperatorNode.o
obj/VirtualNode.o: src/VirtualNode.cpp 
	g++ -std=c++11 -c src/VirtualNode.cpp -o obj/VirtualNode.o
obj/LoopNode.o: src/LoopNode.cpp
	g++ -std=c++11 -c src/LoopNode.cpp -o obj/LoopNode.o
obj/BranchNode.o: src/BranchNode.cpp
	g++ -std=c++11 -c src/BranchNode.cpp -o obj/BranchNode.o
obj/Node.o: src/Node.cpp
	g++ -std=c++11 -c src/Node.cpp -o obj/Node.o

obj/Tensor.o: src/Tensor.cpp
	g++ -std=c++11 -c src/Tensor.cpp -o obj/Tensor.o

clean:
	rm obj/*o 
