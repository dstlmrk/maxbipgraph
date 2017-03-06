#ifndef MAXBIPGRAPH_CRESULT_H
#define MAXBIPGRAPH_CRESULT_H

#include <iostream>
#include <sstream>

using namespace std;


class CResult {
public:
    CResult(bool is_bigraph, int vertices_cnt, int edges_cnt, int * vertices_colors);
    ~CResult();
    friend ostream & operator << (ostream & os, const CResult & result);

    int edges_cnt, vertices_cnt;
    int * vertices_colors;
    bool is_bigraph;
};

#endif //MAXBIPGRAPH_CRESULT_H
