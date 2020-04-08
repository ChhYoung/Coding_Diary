#ifndef  TENSOR_H_
#define  TENSOR_H_
#include <vector>

namespace AG{

class Tensor{
public:
    std::vector<int> m_shape; // tensor的形状，3x3矩阵则 {3,3}
    int m_size;  // 总容量, [3,3,2] 则容量： 3x3x2 = 18
    float* m_tensor; // 存储时以一位数组的形式,逻辑顺序xyz，存储顺序为zyx，例如3x4x5中[1,0,0]为m_tensor[20]

    Tensor(std::vector<int> shape, int need_init = 1);
    Tensor(std::vector<int> shape,float data[]);// 按行存储

    float get_value(std::vector<int> idxs);
    void set_value(std::vector<int> idxs, float value);
    Tensor* matrix_mult(Tensor* tensor); //二维矩阵乘法
    Tensor* scalar_mult(float scalar); // 标量乘法
    void add(Tensor* tensor, Tensor* result); // 累加 
    Tensor* add(Tensor* tensor);//普通加法
    void init(); //随机初始化 
    void display();

    ~Tensor();

};

}
#endif // ! TENSOR_H_
