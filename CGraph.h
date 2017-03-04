//
// Created by marek on 4.3.17.
//

#ifndef MAXBIPGRAPH_CGRAPH_H
#define MAXBIPGRAPH_CGRAPH_H


class CGraph {
public:
    CGraph(int vertices_cnt, bool** adjacency_matrix);
    ~CGraph();
    static CGraph load_graph(const char * path);

    int vertices_cnt;
    bool** adjacency_matrix;
};


#endif //MAXBIPGRAPH_CGRAPH_H
