#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "src/CGraph.h"

using namespace std;

// if I want to use this static var I need use this
int ** CGraph::init_adjacency_matrix = NULL;
CGraph * CGraph::max_bigraph = NULL;


int main(int argc, char* argv[]) {

    int my_rank, vertices_cnt;
    CGraph * max_bigraph, * init_graph;

    /* start up MPI */
    MPI_Init( &argc, &argv);

    /* find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // master
    if (my_rank == 0) {
        // load arguments
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " seq/par file_path " << std::endl;
            return 1;
        }
    }

    // load init graph
    init_graph = CGraph::load_graph(argv[2]);
    vertices_cnt = init_graph->vertices_cnt;

    // get max bigraph from init graph
    if (strcmp(argv[1], "seq") == 0) {
        max_bigraph = CGraph::get_max_bigraph_by_stack(init_graph);
    } else if (strcmp(argv[1], "par") == 0) {
//         max_bigraph = CGraph::get_max_bigraph_by_parallel_stack(init_graph);
        max_bigraph = CGraph::get_max_bigraph_by_cluster(init_graph);
    }
//    CGraph * max_bigraph = CGraph::get_max_bigraph_by_recursion(init_graph);
//    CGraph * max_bigraph = CGraph::get_max_bigraph_by_parallel_recursion(init_graph);

    /* shut down MPI */
    MPI_Finalize();

    if (my_rank == 0) {

        cout << "============================================================================" << endl;
        cout << * max_bigraph << endl;
        // init_graph is deleted by get_max_bigraph()
        // static variable CGraph::max_bigraph is deleted here
        delete max_bigraph;

        for (int i = 0; i < vertices_cnt; ++i) {
            delete[] CGraph::init_adjacency_matrix[i];
        }
        delete[] CGraph::init_adjacency_matrix;
    }

    return 0;
}
