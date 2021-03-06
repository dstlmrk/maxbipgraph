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
    static CGraph * get_max_bigraph(CGraph * init_graph, int num_threads);
    static CGraph *get_max_bigraph_by_cluster(CGraph *init_graph, int num_threads);
    friend ostream & operator << (ostream & os, const CGraph & graph);

    int vertices_cnt, edges_cnt, total_edges_cnt;
    // bitmap of edges
    bool * edges;
    bool ** adjacency_matrix;
    short int * vertices_colors;
    static int ** init_adjacency_matrix;
    static CGraph * max_bigraph;

private:
    static void _get_max_bigraph(CGraph * graph);
    int get_solved_by_others_index();
    bool ** get_adjacency_matrix();
    bool component_is_bigraph(int vertex_index);
    bool is_bipartite_graph();
    static CGraph * recover_graph(vector<int> graph_serialization, int vertices_cnt);
    static vector<int> serialize_graph(CGraph * graph);
};


#endif //MAXBIPGRAPH_CGRAPH_H
