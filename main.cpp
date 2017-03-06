#include <iostream>
#include "src/CGraph.h"

using namespace std;

int main(int argc, char* argv[]) {

    // load arguments
    if (argc < 2) {
        // std::cerr << "Usage: " << argv[0] << " file_path" << std::endl;
        // return 1;
//        argv[1] = (char *) "/home/marek/Dropbox/skola/mi/pdp/maxbipgraph/generator/graf.out";
        argv[1] = (char *) "/home/marek/Dropbox/skola/mi/pdp/maxbipgraph/data/graph4.txt";
//        argv[1] = (char *) "/home/marek/Dropbox/skola/mi/pdp/maxbipgraph/data/graph10_5.txt";
    }

    // load init graph
    CGraph * init_graph = CGraph::load_graph(argv[1]);

    // get max bigraph from init graph
    CGraph * max_bigraph = CGraph::get_max_bigraph(init_graph);

    cout << "RESULT: " << * max_bigraph << endl;

    // init_graph is deleted by get_max_bigraph()
    delete max_bigraph;

    return 0;
}
