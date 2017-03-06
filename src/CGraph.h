#ifndef MAXBIPGRAPH_CGRAPH_H
#define MAXBIPGRAPH_CGRAPH_H

#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class CGraph {
public:
    CGraph(int vertices_cnt, int edges_cnt, bool ** adjacency_matrix);
    ~CGraph();
    static CGraph * load_graph(const char * path);
    static CGraph * get_max_bigraph(CGraph * init_graph);
    friend ostream & operator << (ostream & os, const CGraph & graph);

    int vertices_cnt, edges_cnt;
    bool ** adjacency_matrix;
    bool is_bigraph;
    short int * vertices_colors;

private:
    static int get_edges_cnt(int vertices_cnt, bool ** adjacency_matrix);
    bool component_is_bigraph(int vertex_index);
    bool is_bipartite_graph();
};


#endif //MAXBIPGRAPH_CGRAPH_H
