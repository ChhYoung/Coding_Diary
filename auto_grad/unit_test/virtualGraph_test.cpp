//#include "../include/VirtualGraph.h"
//#include "../include/ComputeGraph.h"
//#include "../include/VirtualNode.h"
//#include "../include/op_node/SquareSum.h"
//#include "MyBranch.h"
//#include "MyLoop.h"
//#include "../include/Tensor.h"
//#include <iostream>
//#include <unordered_map>
//using namespace std;
//using namespace AG;
//int main() {
//    vector<int> shape; shape.push_back(2); shape.push_back(2);
//    float data1[] = { 1,1,1,1 };
//    Tensor* t1 = new Tensor(shape, data1);
//
//    // ׼������ڵ�
//    VirtualNode* parameter = new VirtualNode("Parameter", "1");
//    parameter->m_data = t1;
//    VirtualNode* square_sum = new VirtualNode("SquareSum", "1");
//    BranchNode* branch = new MyBranch("Branch", "1");
//    LoopNode* loop_node = new MyLoop("Loop", "1");
//    // ����������ͼ��ѭ����
//    loop_node->m_sub_vgraph->add_node("", branch);
//    loop_node->m_sub_vgraph->add_node(branch->get_name(), square_sum);
//    // ��������ͼ
//    VirtualGraph vg;
//    vg.add_node("", parameter);
//    vg.add_node(parameter->get_name(), loop_node);
//
//    // ǰ�򴫲������ɼ���ͼ
//    ComputeGraph compute_graph;
//    vg.build_compute_graph(&compute_graph);
//    // ��������ڵ��ֵ
//    cout << "after FP:------------------" << endl;
//    ((OperatorNode*)compute_graph.get_node("Parameter:1:0:"))->m_output->display();
//    ((OperatorNode*)compute_graph.get_node("SquareSum:1:0:"))->m_output->display();
//    ((OperatorNode*)compute_graph.get_node("SquareSum:1:1:"))->m_output->display();
//    ((OperatorNode*)compute_graph.get_node("SquareSum:1:2:"))->m_output->display();
//    ((OperatorNode*)compute_graph.get_node("SquareSum:1:3:"))->m_output->display();
//    compute_graph.build_reverse_graph();
//    // ���򴫲�
//    compute_graph.back_propagation();
//    // ������º��ֵ
//    cout << "after BP:------------------" << endl;
//    cout << "sum_grad:" << endl;
//    ((OperatorNode*)compute_graph.get_node("Parameter:1:0:"))->m_sum_grad->display();
//    ((OperatorNode*)compute_graph.get_node("SquareSum:1:0:"))->m_sum_grad->display();
//    ((OperatorNode*)compute_graph.get_node("SquareSum:1:1:"))->m_sum_grad->display();
//    ((OperatorNode*)compute_graph.get_node("SquareSum:1:2:"))->m_sum_grad->display();
//    cout << "output:" << endl;
//    ((OperatorNode*)compute_graph.get_node("Parameter:1:0:"))->m_output->display();
//    ((OperatorNode*)compute_graph.get_node("SquareSum:1:0:"))->m_output->display();
//    ((OperatorNode*)compute_graph.get_node("SquareSum:1:1:"))->m_output->display();
//    ((OperatorNode*)compute_graph.get_node("SquareSum:1:2:"))->m_output->display();
//    ((OperatorNode*)compute_graph.get_node("SquareSum:1:3:"))->m_output->display();
//    compute_graph.release_tensor();
//
//}