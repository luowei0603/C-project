#include "MGraph.h"
#include "GraphAdjList.h"

int main()
{
    MGraph a;
    a.CreateMGraph();
    // a.MiniSpanTreePrim();
    a.MiniSpanTreeKruskal();
    /* a.DFSTraverse();
    a.BFSTraverse();

    GraphAdjList b;
    b.CreateALGraph();
    b.DFSTraverse();
    b.BFSTraverse();*/
}