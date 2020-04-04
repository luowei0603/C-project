#ifndef MGRAPH_H
#define MGRAPH_H

#include "comm.h"
struct Edge
{
    int start;
    int end;
    int weight;
};

class MGraph
{
private:
    VertexType vexs[MAXVEX];       // 顶点数组
    EdgeType arc[MAXVEX][MAXVEX];  // 邻接矩阵
    int numVertexes;               // 顶点数量
    int numEdges;                  // 边数量
    bool visited[MAXVEX];          // 已访问的数组
    vector<pair<Edge, int>> edges; // 边集数组
    void DFS(int i);
    static int Cmp(const pair<Edge, int> &lhs, const pair<Edge, int> &rhs);
    int Find(int *parent, int f); //查找连线顶点的尾部下标
public:
    MGraph(){};
    ~MGraph(){};
    void CreateMGraph();
    void DFSTraverse();
    void BFSTraverse();
    void MiniSpanTreePrim();
    void MiniSpanTreeKruskal();
    void ShortestPathDijkstra(int p);
    void ShortestPathFlyod();  // Floyd算法，求网图中各顶点v到其余顶点w的最短lujingP[v][w]以及带权长度D[v][w]
};

#endif