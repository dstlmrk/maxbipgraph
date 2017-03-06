#include "CResult.h"


CResult::CResult(bool is_bigraph, int vertices_cnt, int edges_cnt, int * vertices_colors):
        is_bigraph(is_bigraph),
        vertices_cnt(vertices_cnt),
        edges_cnt(edges_cnt) {
    // copy of the array
    this->vertices_colors = new int[vertices_cnt];
    for (int i = 0; i < vertices_cnt; ++i) {
        this->vertices_colors[i] = vertices_colors[i];
    }
}


CResult::~CResult() {
    delete [] this->vertices_colors;
}


ostream & operator << (ostream & os, const CResult & result) {
    os << "colors of graph: ";
    for (int i = 0; i < result.vertices_cnt; ++i) {
        os << result.vertices_colors[i];
    }
    os << ", number of edges: " << result.edges_cnt;
    return os;
}
