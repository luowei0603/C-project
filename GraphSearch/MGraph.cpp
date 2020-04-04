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
        Edge tmp;
        tmp.start = x < y ? x : y;
        tmp.end = x > y ? x : y;
        edges.push_back(make_pair(tmp, weight)); //按照开始结束放入边集数组
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

int MGraph::Cmp(const pair<Edge, int> &lhs, const pair<Edge, int> &rhs)
{
    return lhs.second < rhs.second;
}

void MGraph::MiniSpanTreeKruskal()
{
    cout << "最小生成树为：" << endl;
    sort(edges.begin(), edges.end(), Cmp); // 将边集数组按权值从小到大排列
    int parent[MAXVEX];                    // 定义一个一维数组来判断是否形成环路
    for (int i = 0; i < numVertexes; i++)
    {
        parent[i] = 0;
    }
    for (int i = 0; i < numEdges; i++)
    {
        int n = Find(parent, edges[i].first.start);
        int m = Find(parent, edges[i].first.end);
        if (n != m)
        {                  // 如果n和m不相等，说明此边没有和现有生成树形成环路
            parent[n] = m; //将此边的结尾顶点放到下标为起点的parent中，表示此边已在生成树集合中
            cout << "(" << edges[i].first.start << "," << edges[i].first.end << "):" << edges[i].second << endl;
        }
    }
}

int MGraph::Find(int *parent, int f)
{
    while (parent[f] > 0)
    {
        f = parent[f];
    }
    return f;
}

void MGraph::ShortestPathDijkstra(int p)
{
    for (int i = 0; i < numVertexes; i++)
    {
        for (int j = 0; j < numVertexes; j++)
        {
            if (arc[i][j] == INFINITY)
            {
                cout << 'M' << " ";
            }
            else
            {
                cout << arc[i][j] << " ";
            }
        }
        cout << endl;
    }
    int k;
    int min;
    int patharc[numVertexes];         //用于存储最短路径下标的数组
    int shortPatchTable[numVertexes]; //用于存储到各点最短路径的权值和
    int final[numVertexes];           // final[w]=1，表示求得p到w的最短路径
    for (int i = 0; i < numVertexes; i++)
    {
        final[i] = 0;                   //全部顶点初始化为未知最短路径的状态
        shortPatchTable[i] = arc[p][i]; //将与p点有连线的顶点加上权值
        patharc[i] = 0;                 //初始化路径数组为0
    }
    shortPatchTable[p] = 0; //p到p的路径为0
    final[p] = 1;           //p到p不需要求路径

    //开始主循环，每次求得p至某个顶点i的最短路径
    for (int i = 1; i < numVertexes; i++)
    {
        min = INFINITY; //当前所知离p的最近距离
        for (int j = 0; j < numVertexes; j++)
        { //寻找距离p最近的点
            if (!final[j] && shortPatchTable[j] < min)
            {
                k = j;
                min = shortPatchTable[j]; // j点距离p更近
            }
        }
        final[k] = 1; //目前找到的最近的顶点置为1
        //修正当前最短路径及距离,此时已经找到了p和k的最短路径，对k与其他顶点的边进行计算，得到p与他们当前的最短距离
        for (int j = 0; j < numVertexes; j++)
        {
            // 如果经过顶点k的路径比现在这条路径的长度短的话
            if (!final[j] && (min + arc[k][j] < shortPatchTable[j]))
            {
                //说明找到了更短的路径，修改shortPatchTable和patharc;
                shortPatchTable[j] = min + arc[k][j];
                patharc[j] = k;
            }
        }
    }
    cout << "最短路径数组为：" << endl;
    for (int i = 0; i < numVertexes; i++)
    {
        cout << patharc[i] << " ";
    }
    cout << endl;
    cout << "最短路径权值数组为：" << endl;
    for (int i = 0; i < numVertexes; i++)
    {
        cout << shortPatchTable[i] << " ";
    }
    cout << endl;
    for (int i = 1; i < numVertexes; i++)
    {
        cout << "V0 -> V" << i << " weight: " << shortPatchTable[i];
        cout << " path：" << i;
        int k = i;
        while (k != 0)
        { //k不是起点坐标
            cout << " <- " << patharc[k];
            k = patharc[k];
        }
        cout << endl;
    }
}

void MGraph::ShortestPathFlyod()
{
    int pathMatrix[numVertexes][numVertexes];
    int shortPathTable[numVertexes][numVertexes];
    for (int v = 0; v < numVertexes; v++)
    {
        for (int w = 0; w < numVertexes; w++)
        {
            shortPathTable[v][w] = arc[v][w]; //shortPathTable[v][w]的值即为对应点间的权值
            pathMatrix[v][w] = w;
        }
    }

    for (int k = 0; k < numVertexes; k++)
    {
        for (int v = 0; v < numVertexes; v++)
        {
            for (int w = 0; w < numVertexes; w++)
            {
                if (shortPathTable[v][w] > shortPathTable[v][k] + shortPathTable[k][w])
                {
                    //如果经过下标为k顶点路径比原先两点间路径更短，将当前两点间的权值设置为更小的一个
                    shortPathTable[v][w] = shortPathTable[v][k] + shortPathTable[k][w];
                    pathMatrix[v][w] = pathMatrix[v][k]; //路径设置为经过下标k的顶点
                }
            }
        }
    }
    cout << "最短路径权值矩阵为：" << endl;
    for (int v = 0; v < numVertexes; v++)
    {
        for (int w = 0; w < numVertexes; w++)
        {
            cout << shortPathTable[v][w] << " ";
        }
        cout << endl;
    }
    cout << "最短路径矩阵为：" << endl;
    for (int v = 0; v < numVertexes; v++)
    {
        for (int w = 0; w < numVertexes; w++)
        {
            cout << pathMatrix[v][w] << " ";
        }
        cout << endl;
    }
    // 显示最短路径
    for (int v = 0; v < numVertexes; v++)
    {
        for (int w = v + 1; w < numVertexes; w++)
        {
            cout << "V" << v << "-"
                 << "V" << w << " weight: " << shortPathTable[v][w];
            int k = pathMatrix[v][w];
            cout << " path: " << v; // 打印源点
            while (k != w)
            { //如果路径顶点下标不是终点
                cout << " -> " << k;
                k = pathMatrix[k][w];
            }
            cout << " -> " << w << endl;
        }
    }
}
