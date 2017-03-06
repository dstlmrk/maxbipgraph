#ifndef MAXBIPGRAPH_CGRAPH_H
#define MAXBIPGRAPH_CGRAPH_H

#include "CResult.h"
#include <vector>
using namespace std;

class CGraph {
public:
    static CGraph load_graph(const char * path);
    CResult get_max_bigraph();

    int vertices_cnt;
    vector<vector<bool>> adjacency_matrix;
    // pointer to instance
    CResult * best_result = NULL;

private:
    CGraph(int vertices_cnt, vector<vector<bool>> & adjacency_matrix);
    int get_edges_cnt(vector<vector<bool>> & adjacency_matrix);
    bool component_is_bigraph(
            vector<vector<bool>> & adjacency_matrix, int * vertices_colors, int vertex_index
    );
    CResult * evaluate(vector<vector<bool>> & adjacency_matrix);

};


#endif //MAXBIPGRAPH_CGRAPH_H
