#ifndef MAXBIPGRAPH_CGRAPH_H
#define MAXBIPGRAPH_CGRAPH_H

#include "CResult.h"
#include <vector>
using namespace std;

class CGraph {
public:
    CGraph(int vertices_cnt, int edges_cnt, bool ** adjacency_matrix);
    ~CGraph();
    bool is_bipartite_graph();
    static CGraph * load_graph(const char * path);
    friend ostream & operator << (ostream & os, const CGraph & graph);

//    CResult get_max_bigraph();

    int vertices_cnt, edges_cnt;
    bool ** adjacency_matrix;
    bool is_bigraph;
    short int * vertices_colors;

private:
    static int get_edges_cnt(int vertices_cnt, bool ** adjacency_matrix);
    bool component_is_bigraph(int vertex_index);
//    CResult * evaluate(vector<vector<bool>> & adjacency_matrix);

};


#endif //MAXBIPGRAPH_CGRAPH_H
