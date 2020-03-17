#include "GraphAdjList.h"
void GraphAdjList::CreateALGraph()
{
    cout << "请输入顶点数，边数：";
    cin >> numVertexes >> numEdges;
    cout << "输入顶点" << endl;
    for (int i = 0; i < numVertexes; i++)
    {
        cin >> vertexNode[i].data;
        vertexNode[i].firstEdge = NULL;
    }
    cout << "输入边（vi,vj）的顶点序号和权重：" << endl;
    for (int i = 0; i < numEdges; i++)
    {
        int x, y;
        EdgeType weight;
        cin >> x >> y >> weight;
        /* 头插法 */
        Edgenode *e = new Edgenode(y, weight, vertexNode[x].firstEdge);
        vertexNode[x].firstEdge = e;

        Edgenode *p = new Edgenode(x, weight, vertexNode[y].firstEdge);
        vertexNode[y].firstEdge = p;
    }
}

void GraphAdjList::DFSTraverse()
{
    for (int i = 0; i < numVertexes; i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < numVertexes; i++)
    {
        if (!visited[i])
        {
            DFS(i);
        }
    }
    cout << endl;
}

void GraphAdjList::DFS(int i)
{
    visited[i] = true;
    cout << vertexNode[i].data << " ";
    Edgenode *p = vertexNode[i].firstEdge;
    while (p)
    {
        if (!visited[p->adjvex])
        {
            DFS(p->adjvex);
        }
        p = p->next;
    }
}

void GraphAdjList::BFSTraverse()
{
    for (int i = 0; i < numVertexes; i++)
    {
        visited[i] = false;
    }
    deque<int> myQue;
    for (int i = 0; i < numVertexes; i++)
    {

        if (!visited[i])
        {
            visited[i] = true;
            cout << vertexNode[i].data << " ";
            myQue.push_back(i);
            while (!myQue.empty())
            {
                int top = myQue.front();
                Edgenode *p = vertexNode[top].firstEdge;
                myQue.pop_front();
                while (p)
                {
                    if (!visited[p->adjvex])
                    {
                        visited[p->adjvex] = true;
                        cout << vertexNode[p->adjvex].data << " ";
                        myQue.push_back(p->adjvex);
                    }
                    p = p->next;
                }
            }
        }
    }
    cout << endl;
}