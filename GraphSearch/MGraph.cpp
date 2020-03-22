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
            if (i == j)
            {
                arc[i][j] = 0;
            }
            else
            {
                arc[i][j] = INFINITY;
            }
        }
    }
    cout << "输入边和权重：" << endl;
    for (int i = 0; i < numEdges; i++)
    {
        int x, y, weight;
        cin >> x >> y >> weight;
        arc[x][y] = weight;
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
        if (arc[i][j] != INFINITY && arc[i][j] != 0 && !visited[j])
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
                    if (arc[top][j] != INFINITY && arc[top][j] != 0 && !visited[j])
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

void MGraph::MiniSpanTreePrim()
{
    int min;
    int k;
    int j;
    int adjvex[MAXVEX];  //保存相关顶点下标
    int lowcost[MAXVEX]; //保存相关顶点间的权值
    lowcost[0] = 0;      //初始化第一个权值为0，即v0加入生成树，lowcost的值为0，就代表此下标的顶点已加入生成树
    adjvex[0] = 0;       //初始化第一个顶点下标为0

    for (int i = 1; i < numVertexes; i++)
    {
        lowcost[i] = arc[0][i]; //将v0顶点与之有边的权值存入数组
        adjvex[i] = 0;          //初始化都为v0的下标
    }

    for (int i = 1; i < numVertexes; i++)
    {
        min = INFINITY; //初始化最小权值为无穷大
        k = 0;
        j = 1;
        while (j < numVertexes)
        { //循环全部顶点
            if (lowcost[j] != 0 && lowcost[j] < min)
            {
                min = lowcost[j];
                k = j;
            }
            j++;
        }
        cout << "(" << adjvex[k] << "," << k << ")" << endl; //打印当前顶点中权值最小边
        lowcost[k] = 0;                                      //当前顶点的权值设置为0，表示此顶点已经完成任务
        for (j = 1; j < numVertexes; j++)                    //循环所有顶点
        {
            if (lowcost[j] != 0 && arc[k][j] < lowcost[j])
            {                           //若下标为k顶点各边权值小于此前这些顶点未被加入生成树权值
                lowcost[j] = arc[k][j]; //将较小权值加入到lowcost
                adjvex[j] = k;          //将下标为k的顶点存入adjvex
            }
        }
    }
}