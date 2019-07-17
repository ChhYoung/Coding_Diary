#ifndef _DSA_INCLUDE_SRC_GRAPH_H__
#define _DSA_INCLUDE_SRC_GRAPH_H__

#include"stack.h"
#include"queue.h"
#include<assert.h>
#include<limits.h> // INT_MAX

namespace DSA{

// 定点状态
enum class VertexStatus{
    // 未发现 undiscovered
    undiscovered,
    // 已发现
    discovered,
    // 已访问
    visited,
};

// 边的状态
enum class EdgeStatus{
    // 为处置
    undetermined,
    // 树边
    tree,
    // 跨边
    cross,
    // 前向边 : 祖先-->后代
    forward,
    // 后向边： 后代-->祖先
    backward,
};

// 图基类
template<typename Tv, typename Te>
class Graph{
public: 
    // 顶点总数
    int n;
    // 插入顶点， 返回编号
    virtual int insert(Tv const& v) = 0;
    // 删除顶点及其关联边， 返回该顶点
    virtual Tv remove(int v) = 0;
    // 顶点数据(该顶点的确存在)
    virtual Tv& vertex(int v) = 0;
    // 顶点的入度
    virtual int inDegree(int v) = 0;
    // 顶点的出度
    virtual int outDegree(int v) = 0;
    // 顶点的首个邻接顶点
    virtual int firstNbr(int v, int j) = 0;
    // 顶点v的(相对于顶点j)下一个邻接顶点
    virtual int nextNbr(int v, int j) = 0;
    // 顶点状态
    virtual VertexStatus& status(int v) = 0;
    // 顶点 discovered time 
    virtual int& dTime(int v) = 0;
    // 顶点 finished time 
    virtual int& fTime(int v) = 0;
    // 顶点在遍历树中的父亲
    virtual int& parent(int v) = 0;
    // 顶点在遍历树中的优先级
    virtual int& priority(int v) = 0;

    // 边总数
    int e;
    // 边(v,u)是否存在
    virtual bool exists(int v, int u) = 0;
    // 在顶点v,u之间插入权重为w的边e
    virtual void insert(Te const& e,int w,int v, int u) = 0;
    // 删除顶点v,u之间的边e,返回该边的信息
    virtual Te remove(int v, int e) = 0;
    // 边(v,u)的状态(该边存在时)
    virtual EdgeStatus& type(int v, int u) = 0;
    // 边(v,u)的权重
    virtual int& weight(int v, int u) = 0;

    // 算法接口
    // 广度优先
    void bfs(int s){
        // 初始化
        reset();
        int clock = 0;
        int v = s;
        // 逐一检查所有顶点
        // 一旦遇到未被发现的顶点则从该顶点出发做一次BFS
        do{
            if(VertexStatus::undiscovered == status(v)){
                BFS(v, clock);
            }
        }while(s != (v = (++v % n)));
    }

    // 深度优先搜索
    void dfs(int s){
        reset();
        int clock = 0;
        int v = s;
        do{
            if(VertexStatus::undiscovered == status(v)){
                DFS(v, clock);
            }
        }while(s != (v = (++v % n)));
    }

    // 基于深度优先的拓扑排序算法
    Stack<Tv>* tsort(int s){
        assert(0 <= s && s < n);
        reset();
        int clock = 0, v = s;
        auto S = new Stack<Tv>();
        do{
            if(status(v) == VertexStatus::undiscovered){
                if(!TSORT(v, clock, S)){
                    S->clear();
                    break;
                }
            }
        }while(s != (v = (++v % n)));
        return S;
    }
private: 
    // 所有顶点，边的辅助信息复位
    //  重置顶点，边的状态，时间，优先级等
    void reset(){
        for(int i=0; i<n; ++i){
            status(i) = VertexStatus::undiscovered;
            dTime(i) = fTime(i) = 0;
            parent(i) = -1;
            priority(i) = INT_MAX;
            for(int j=0; j<n; ++j){
                if(exists(i,j)){
                    type(i,j) = EdgeStatus::undetermined;
                }
            }
        }
    }    

    // BFS， 单个连通域的广度优先搜索
    // breadth first search
    void BFS(int v,int& clock){
        // 构造辅助栈
        Queue<int> queue;
        // 初始化起点
        status(v) = VertexStatus::discovered;
        queue.enqueue(v);
        // 在队列为空前，不断入队
        while(!queue.empty()){
            // 取出队首顶点
            int v = queue.dequeue();
            dTime(v) = ++clock;
            // 枚举v的所有邻接u
            for(int u=firstNbr(v); -1<u; u = nextNbr(v,u)){
                // 邻接未访问，则标记为discovered, 后入队
                // 同时改变其边(v,u)的状态
                if(status(u) == VertexStatus::undiscovered){
                    status(u) = VertexStatus::discovered;
                    queue.enqueue(u);
                    // 引入树边拓展支撑树
                    type(v,u) = EdgeStatus::tree;
                    parent(u) = v;
                }
                // 若顶点已经发现或访问完毕
                // 则边(v,u)是一个cross 跨边，
                //   两顶点间无直系的父子等关系
                else {
                    type(v,u) = EdgeStatus::cross;
                }
            }
            // 访问完毕
            status(v) = VertexStatus::visited;
        }
    }

    //  DFS   depth first search
    void DFS(int v, int& clock){
        // 发现当前节点
        // 设置discovered time
        dTime(v) = ++clock;
        status(v) = VertexStatus::discovered;
        // 枚举v的所有邻居
        for(int u=firstNbr(v); -1 < u; u=nextNbr(v,u)){
            switch(status(u)){
                // 若v的邻接u未被访问，则将u加入树中
                //  在递归的访问u的邻接
                case VertexStatus::undiscovered:
                    type(v,u) = EdgeStatus::tree;
                    parent(u) = v;
                    DFS(u,clock);
                    break;
                // 已经发现则将边设置为 backward
                //  即有回路产生
                case VertexStatus::discovered:
                    type(v,u) = EdgeStatus::backward;
                    break;
                // visited 情况： 根据dTime 来判断当前变得状态
                // dTime(v) < dTime(u) : 祖先指向后代的一条边 forward
                // dTime(v) > dTime(u) : 有两个无直系祖先后代关系的顶点产生关系
                //                      即跨边： cross
                default:
                    type(v,u) = dTime(v) < dTime(u) ? EdgeStatus::forward : EdgeStatus::cross;
                    break;
            }
        }
        // 邻接访问完毕，设置状态为visited , 记录 finished time
        status(v) = VertexStatus::visited;
        fTime(v) = ++clock;
    }
};


} // namespace DSA

#endif // _DSA_INCLUDE_SRC_GRAPH_H__