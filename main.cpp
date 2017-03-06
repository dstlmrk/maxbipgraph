#include <iostream>
#include "src/CGraph.h"

using namespace std;


int main() {
    CGraph graph = CGraph::load_graph("/home/marek/Dropbox/skola/mi/pdp/maxbipgraph/generator/graf.out");
//    CGraph graph = CGraph::load_graph("/home/marek/Dropbox/skola/mi/pdp/maxbipgraph/data.txt");
    cout << graph.get_max_bigraph() << endl;
    return 0;
}
