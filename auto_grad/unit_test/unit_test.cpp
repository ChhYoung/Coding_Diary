//#include <iostream>
//#include <vector>
//#include <unordered_map>
//
//#include "../include/Tensor.h"
//#include "../include/Graph.h"
//#include "../include/Node.h"
//
//
//#include "../include/op_node/Add.h"
//#include "../include/op_node/SquareSum.h"
//#include "../include/op_node/Minus.h"
//#include "../include/op_node/Mult.h"
//#include "../include/op_node/Sigmoid.h"
//#include "../include/op_node/Parameter.h"
//#include "../include/ComputeGraph.h"
//#include "../include/Tensor.h"
//#include "../include/OperatorNode.h"
//
//#include "../include/VirtualGraph.h"
//#include "../include/VirtualNode.h"
//#include "MyBranch.h"
//#include "MyLoop.h"
//
//
//using namespace AG;
//
//void print_tag(int a) {
//	std::cout <<"the index of test cases : "<< a << std::endl;
//}
//
//void tensor_test() {
//	std::vector<int> shape(2);
//	shape[0] = 2; shape[1] = 2;
//	float data[] = { 1,2,3,4 };
//	float data2[] = { 2,3,4,5 };
//	print_tag(1);
//	Tensor* tensor1 = new Tensor(shape, data);
//	tensor1->display();
//
//	print_tag(2);
//	Tensor* tensor2 = new Tensor(shape, data2);
//	tensor2->display();
//
//	print_tag(3);
//	Tensor* random_tensor = new Tensor(shape);
//	random_tensor->init();
//	random_tensor->display();// 初始化验证
//
//	print_tag(4);
//	Tensor* mult_result = tensor1->matrix_mult(tensor2);// 验证乘法
//	mult_result->display();
//
//	print_tag(5);
//	Tensor* add_result = tensor1->add(tensor2);// 加法验证
//	add_result->display();
//
//	print_tag(6);
//	tensor1->add(tensor2, add_result);// 加法验证2
//	add_result->display();
//
//	print_tag(7);
//	Tensor* scalar_mult_result = tensor1->scalar_mult(3.0);// 标量乘法
//	scalar_mult_result->display();
//
//	print_tag(8);
//	std::vector<int> shape1(3);
//	shape1[0] = 2; shape1[1] = 3; shape1[2] = 2;// {{{1,2},{3,4},{5,6}},{{7,8},{9,10},{11,12}}}
//	float data1[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
//	Tensor* three_dim_tensor = new Tensor(shape1, data1);
//	std::vector<int> idxs(3);
//	idxs[0] = 1; idxs[1] = 1; idxs[2] = 0;
//	std::cout << three_dim_tensor->get_value(idxs) << std::endl;
//}
//
//void graph_test() {
//	Node* a = new Node("a", "0");
//	Node* b = new Node("b", "0");
//	Node* c = new Node("c", "0");
//	Node* d = new Node("d", "0");
//	Node* e = new Node("e", "0");
//	Node* f = new Node("f", "0");
//
//	// 构建图
//	Graph graph;
//	graph.add_node("", a);
//	graph.add_node("", b);
//	graph.add_node(a->get_name(), c);
//	graph.add_node(b->get_name(), c);
//	graph.add_node("", d);
//	graph.add_node(c->get_name(), e);
//	graph.add_node(d->get_name(), e);
//	graph.add_node(c->get_name(), f);
//	// 构建转置图
//	graph.build_reverse_graph();
//	// 构建子图，基于图改写
//	std::vector<Node*> endnode_list;
//	endnode_list.push_back(f);
//	graph.build_subgraph(endnode_list);
//
//	// 拓扑排序
//	std::vector<Node*> toposort_result;
//	graph.topological_sort(graph.m_adj_table, toposort_result);//原图拓扑排序
//	for (int i = 0; i < toposort_result.size(); ++i) {
//		std::cout << toposort_result[i]->get_name() << " ";
//	}
//	std::cout << std::endl;
//	std::vector<Node*> reverse_toposort_result;
//	graph.topological_sort(graph.m_reverse_table, reverse_toposort_result);
//	for (int i = 0; i < reverse_toposort_result.size(); ++i) {
//		std::cout << reverse_toposort_result[i]->get_name() << " ";
//	}
//	std::cout << std::endl;
//}
//
//void operatorNode_test() {
//	std::vector<int> shape1; shape1.push_back(2); shape1.push_back(2);
//	std::vector<int> shape2; shape2.push_back(2); shape2.push_back(2);
//	float data1[] = { 1,2,3,4 };
//	float data2[] = { 2,3,4,5 };
//	Tensor* t1 = new Tensor(shape1, data1);
//	Tensor* t2 = new Tensor(shape2, data2);
//	std::cout << "t1\n";
//	t1->display();
//	std::cout << "t2\n";
//	t2->display();
//
//	// 生成计算节点
//	OperatorNode* p1 = new Parameter("Parameter", "1", "0", t1);
//	OperatorNode* p2 = new Parameter("Parameter", "2", "0", t2);
//	OperatorNode* add = new Add("Add", "1", "0");
//	OperatorNode* minus = new Minus("Minus", "1", "0");
//	OperatorNode* mult = new Mult("Mult", "1", "0");
//	OperatorNode* sigmoid = new Sigmoid("Sigmoid", "1", "0");
//	OperatorNode* square_sum = new SquareSum("SquareSum", "1", "0");
//	
//	//p1 p2
//
//	// 生成计算图
//	ComputeGraph cg;
//	cg.add_node("", p1);
//	//cg.add_node("", p2);
//	//// 测试加法
//	//cg.add_node(p1->get_name(), add);
//	//cg.add_node(p2->get_name(), add); 
//	//测试减法
//	/*cg.add_node(p1->get_name(), minus);
//	cg.add_node(p2->get_name(), minus);*/
//	// 测试乘法
//	/*cg.add_node(p1->get_name(), mult);
//	cg.add_node(p2->get_name(), mult);*/
//	//// 测试sigmoid
//	//cg.add_node(p1->get_name(), sigmoid);
//	// 测试SquareSum
//	cg.add_node(p1->get_name(), square_sum);
//
//
//	// 构建转置图
//	cg.build_reverse_graph();
//
//	// 前向传播
//	std::cout << "result of forward propagation\n";
//	std::vector<Tensor*> result;
//	cg.forward_propagation(result);
//	result[0]->display();//前向结果
//
//	//反向传播
//
//
//	std::cout << "learning rate : m_a == 0.01\n";
//	std::cout << "result of back propagation\n";
//	cg.back_propagation();
//	std::cout << "p1->sum_grad:\n";
//	p1->m_sum_grad->display();
//	/*std::cout << "p2->sum_grad:\n";
//	p2->m_sum_grad->display();*/
//	std::cout << "p1:\n";
//	p1->m_output->display();
//	/*std::cout << "p2:\n";
//	p2->m_output->display();*/
//}
//
//
//int main() {
//	//tensor_test();
//	//graph_test();
//	//operatorNode_test();
//	
//	return 1;
//}