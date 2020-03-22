#ifndef MGRAPH_H
#define MGRAPH_H

#include "comm.h"
class MGraph
{
private:
    VertexType vexs[MAXVEX];      // 顶点数组
    EdgeType arc[MAXVEX][MAXVEX]; // 邻接矩阵
    int numVertexes;              // 顶点数量
    int numEdges;                 // 边数量
    bool visited[MAXVEX];         // 已访问的数组
    void DFS(int i);

public:
    MGraph(){};
    ~MGraph(){};
    void CreateMGraph();
    void DFSTraverse();
    void BFSTraverse();
    void MiniSpanTreePrim();  
};

#endif