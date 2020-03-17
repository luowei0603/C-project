#include "MGraph.h"
void MGraph::CreateMGraph()
{
    cout << "输入顶点数和边数：" << endl;
    cin >> numVertexes >> numEdges;
    cout << "输入顶点:" << endl;
    for (int i = 0; i < numVertexes; i++)
    {
        cin >> vexs[i];
    }

    for (int i = 0; i < numVertexes; i++)
    {
        for (int j = 0; j < numVertexes; j++)
        {
            arc[i][j] = INFINITY;
        }
    }
    cout << "输入边和权重：" << endl;
    for (int i = 0; i < numEdges; i++)
    {
        int x, y, weight;
        cin >> x >> y >> weight;
        arc[x][y] = 1;
        arc[y][x] = arc[x][y];
    }
}

void MGraph::DFSTraverse()
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

void MGraph::DFS(int i)
{
    visited[i] = true;
    cout << vexs[i] << " ";
    for (int j = 0; j < numVertexes; j++)
    {
        if (arc[i][j] != INFINITY && !visited[j])
        {
            DFS(j);
        }
    }
}

void MGraph::BFSTraverse()
{
    deque<int> myQue;
    for (int i = 0; i < numVertexes; i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < numVertexes; i++)
    {
        if (!visited[i])
        {
            visited[i] = true;
            cout << vexs[i] << " ";
            myQue.push_back(i);
            while (!myQue.empty())
            {
                int top = myQue.front();
                myQue.pop_front();
                for (int j = 0; j < numVertexes; j++)
                {
                    if (arc[top][j] != INFINITY && !visited[j])
                    {
                        visited[j] = true;
                        cout << vexs[j] << " ";
                        myQue.push_back(j);
                    }
                }
            }
        }
    }
    cout << endl;
}