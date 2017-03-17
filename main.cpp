#include <iostream>
#include "src/CGraph.h"
//#include <omp.h>

using namespace std;

// if I want to use this static var I need use this
int ** CGraph::init_adjacency_matrix = NULL;
CGraph * CGraph::max_bigraph = NULL;


int main(int argc, char* argv[]) {

    // load arguments
    if (argc < 2) {
        // std::cerr << "Usage: " << argv[0] << " file_path" << std::endl;
        // return 1;
//        argv[1] = (char *) "/home/marek/Dropbox/skola/mi/pdp/maxbipgraph/generator/graf.out";
//        argv[1] = (char *) "/home/marek/Dropbox/skola/mi/pdp/maxbipgraph/data/graph4.txt";
        argv[1] = (char *) "/home/marek/Dropbox/skola/mi/pdp/maxbipgraph/data/graph10_5.txt";
//        argv[1] = (char *) "/home/marek/Dropbox/skola/mi/pdp/maxbipgraph/data/graph6_4.txt";
//        argv[1] = (char *) "/home/marek/Dropbox/skola/mi/pdp/maxbipgraph/data/graph5_3.txt";
    }

    // load init graph
    CGraph * init_graph = CGraph::load_graph(argv[1]);
    int vertices_cnt = init_graph->vertices_cnt;

    // get max bigraph from init graph
//    CGraph * max_bigraph = CGraph::get_max_bigraph_by_stack(init_graph);
    CGraph * max_bigraph = CGraph::get_max_bigraph_by_recursion(init_graph);

    cout << * max_bigraph << endl;

    // init_graph is deleted by get_max_bigraph()
    // static variable CGraph::max_bigraph is deleted here
    delete max_bigraph;

    for (int i = 0; i < vertices_cnt; ++i){
        delete [] CGraph::init_adjacency_matrix[i];
    }
    delete[] CGraph::init_adjacency_matrix;

    return 0;
}
