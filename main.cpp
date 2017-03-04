#include <iostream>
#include "CGraph.h"
//#include <fstream>
//#include <string>

using namespace std;

//class CGraph {
//public:
//    CGraph(int n);
//    ~CGraph(void);
//    static load_graph(char const * path);
//    int vertices_cnt;
// CGraph() {};

//    CGraph::~CGraph() {}
// -----------------------------------------------------
//    CGraph(int n) : vertices_cnt(n) {}
// int** adjacency_matrix = new int*[vertices_cnt];
// for(int i = 0; i < vertices_cnt; ++i)
//     adjacency_matrix[i] = new int[vertices_cnt];
// }

//bool is_bigraph(CGraph graph) {
//    return true;
//}

int main() {
    cout << "Hello!" << endl;
    CGraph graph = CGraph::load_graph("/home/marek/Dropbox/skola/mi/pdp/maxbipgraph/data.txt");

    cout << graph.vertices_cnt << endl;
    return 0;
}