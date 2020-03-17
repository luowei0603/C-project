/* 邻接表法表示图 */
#ifndef GRAPHADJILIST_H
#define GRAPHADJILIST_H
#include "comm.h"
struct Edgenode /* 边表节点 */
{
    int adjvex;      /* 邻接点域，存储该顶点对应的下标 */
    EdgeType weight; /* 存储权值 */
    Edgenode *next;  /* 链域，指向下一个邻接点 */
    Edgenode(int _adjvex, EdgeType _weight, Edgenode *_next) : adjvex(_adjvex),
                                                               weight(_weight), next(_next) {}
};
struct VertexNode /* 顶点表节点 */
{
    VertexType data;     /* 顶点域，存储顶点信息 */
    Edgenode *firstEdge; /* 边表头指针 */
};

class GraphAdjList
{
private:
    int numVertexes;               // 顶点数量
    int numEdges;                  // 边的数量
    VertexNode vertexNode[MAXVEX]; // 顶点数组
    bool visited[MAXVEX];          // 访问数组
    void DFS(int i);

public:
    GraphAdjList() {}
    ~GraphAdjList() {}
    void CreateALGraph();
    void DFSTraverse();
    void BFSTraverse();
};

#endif // !GRAPHADJILIST_H
