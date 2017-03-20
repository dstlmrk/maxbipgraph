#ifndef MAXBIPGRAPH_CGRAPH_H
#define MAXBIPGRAPH_CGRAPH_H

#include <vector>
#include <iostream>
#include <sstream>
#include <bitset>


using namespace std;

class CGraph {
public:
    CGraph(int vertices_cnt, int edges_cnt, int total_edges_cnt, bool * edges);
    ~CGraph();
    static CGraph * load_graph(const char * path);
    static CGraph * get_max_bigraph_by_stack(CGraph * init_graph);
    static CGraph * get_max_bigraph_by_recursion(CGraph * init_graph);
    static CGraph * get_max_bigraph_by_parallel_recursion(CGraph * init_graph);
    friend ostream & operator << (ostream & os, const CGraph & graph);

    int vertices_cnt, edges_cnt, total_edges_cnt;
    // bitmap of edges
    bool * edges;
    bool ** adjacency_matrix;
    short int * vertices_colors;
    static int ** init_adjacency_matrix;
    static CGraph * max_bigraph;

private:
    static void _get_max_bigraph_by_recursion(CGraph * graph);
    static void _get_max_bigraph_by_parallel_recursion(CGraph * graph);
    int get_solved_by_others_index();
    bool ** get_adjacency_matrix();
    bool component_is_bigraph(int vertex_index);
    bool is_bipartite_graph();
};


#endif //MAXBIPGRAPH_CGRAPH_H
