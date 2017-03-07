#ifndef MAXBIPGRAPH_CGRAPH_H
#define MAXBIPGRAPH_CGRAPH_H

#include <vector>
#include <iostream>
#include <sstream>
#include <bitset>

using namespace std;

class CGraph {
public:
    CGraph(int vertices_cnt, int edges_cnt, bool * edges, int stack_depth = 0);
    ~CGraph();
    static CGraph * load_graph(const char * path);
    static CGraph * get_max_bigraph(CGraph * init_graph);
    friend ostream & operator << (ostream & os, const CGraph & graph);

    int vertices_cnt, edges_cnt, stack_depth;
    bool * edges;
    bool ** adjacency_matrix;
    short int * vertices_colors;
    static int ** init_adjacency_matrix;

private:
    bool ** get_adjacency_matrix();
    bool component_is_bigraph(int vertex_index);
    bool is_bipartite_graph();
};


#endif //MAXBIPGRAPH_CGRAPH_H
