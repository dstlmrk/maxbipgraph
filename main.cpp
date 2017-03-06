#include <iostream>
#include "src/CGraph.h"
#include "src/CMaxBigraph.h"

using namespace std;


int main(int argc, char* argv[]) {

    // load arguments
    if (argc < 2) {
        // std::cerr << "Usage: " << argv[0] << " file_path" << std::endl;
        // return 1;
//        argv[1] = (char *) "/home/marek/Dropbox/skola/mi/pdp/maxbipgraph/generator/graf.out";
        argv[1] = (char *) "/home/marek/Dropbox/skola/mi/pdp/maxbipgraph/data.txt";
    }

    // load init graph
    CGraph * graph = CGraph::load_graph(argv[1]);

    // get max bigraph from init graph
    CMaxBigraph max_bigraph_alg = CMaxBigraph();
    CGraph * max_bigraph = max_bigraph_alg.evaluate(graph);

    cout << "RESULT: " << *max_bigraph << endl;
    return 0;
}
