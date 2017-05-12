#include "mpi.h"
#include "src/CGraph.h"

using namespace std;

// if I want to use this static var I need use this
int ** CGraph::init_adjacency_matrix = NULL;
CGraph * CGraph::max_bigraph = NULL;


int main(int argc, char* argv[]) {

    int my_rank, vertices_cnt;
    double t1, t2;
    CGraph * max_bigraph, * init_graph;

    /* start up MPI */
    MPI_Init( &argc, &argv);

    /* find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* time measuring - start */
    t1 = MPI_Wtime();

    // master
    if (my_rank == 0) {
        // load arguments
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " num_threads file_path " << std::endl;
            return 1;
        }
    }

    int num_threads = atoi(argv[1]);

    // load init graph
    init_graph = CGraph::load_graph(argv[2]);
    vertices_cnt = init_graph->vertices_cnt;

    max_bigraph = CGraph::get_max_bigraph_by_cluster(init_graph, num_threads);

    if (my_rank == 0) {
        cout << * max_bigraph << endl;
        // init_graph is deleted by get_max_bigraph()
        // static variable CGraph::max_bigraph is deleted here
        delete max_bigraph;

        for (int i = 0; i < vertices_cnt; ++i) {
            delete[] CGraph::init_adjacency_matrix[i];
        }
        delete[] CGraph::init_adjacency_matrix;
    }

    /* time measuring - stop */
    t2 = MPI_Wtime();

    if (my_rank == 0) {
        printf("[master] Elapsed time is %f seconds\n", t2 - t1);
    }

    /* shut down MPI */
    MPI_Finalize();

    return 0;
}
