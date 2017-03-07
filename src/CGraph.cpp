#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <iomanip>
#include "CGraph.h"

using namespace std;

// TODO: pole sousednosti udelat static a predavat si pouze pole vektoru
// TODO: podle me je lepsi BFS, protoze hned prvni vysledek je ten nejlepsi

CGraph::CGraph(int vertices_cnt, int edges_cnt, bool * edges, int stack_depth):
        vertices_cnt(vertices_cnt), edges_cnt(edges_cnt), edges(edges), stack_depth(stack_depth) {
    vertices_colors = new short int[vertices_cnt];
}

CGraph::~CGraph() {
    delete[] edges;
    delete[] vertices_colors;
}

CGraph * CGraph::load_graph(const char * path) {

    ifstream file(path);
    string line;
    int vertices_cnt;
    bool ** adjacency_matrix;

    if (!file.is_open()) {
        cout << "Unable to open file!" << endl;
        exit(EXIT_FAILURE);
    }

    // load count of vertices
    getline(file, line);
    vertices_cnt = stoi(line);

    // load adjacency matrix
    CGraph::init_adjacency_matrix = new int*[vertices_cnt];
    for(int i = 0; i < vertices_cnt; ++i) {
        CGraph::init_adjacency_matrix[i] = new int[vertices_cnt];
    }
    int edge_index = 0, diagonal_index = 0;
    for(int i = 0; i < vertices_cnt; ++i, ++diagonal_index) {
        getline(file, line);
        for (int j = diagonal_index + 1; j < line.length(); ++j) {
            int value = 0;
            if (line[j] == '1') {
                value = ++edge_index;
            }
            CGraph::init_adjacency_matrix[i][j] = value;
            CGraph::init_adjacency_matrix[j][i] = value;
        }
    }

    int edges_cnt = edge_index;

    file.close();

    bool * edges = new bool [edges_cnt];
    for (int i = 0; i < edges_cnt; ++i) {
        edges[i] = true;
    }

    cout << "LOAD: Count of vertices: " << vertices_cnt;
    cout << ", edges: " << edges_cnt << endl;

    return new CGraph(
            vertices_cnt,
            edges_cnt,
            edges
    );
}

ostream & operator << (ostream & os, const CGraph & graph) {
    os << "Colors of graph: ";
    for (int i = 0; i < graph.vertices_cnt; ++i) {
        os << graph.vertices_colors[i];
    }
    os << ", number of edges: " << graph.edges_cnt << endl;
    for (int i = 0; i < graph.vertices_cnt; i++) {
        for (int j = 0; j < graph.vertices_cnt; j++) {
            os << graph.adjacency_matrix[i][j] << " ";
        }
        os << endl;
    }

    return os;
}

bool **CGraph::get_adjacency_matrix() {
    // get adjacency matrix from vector of edges and init matrix

    bool **adjacency_matrix = new bool *[vertices_cnt];
    for (int i = 0; i < vertices_cnt; ++i) {
        adjacency_matrix[i] = new bool[vertices_cnt];
        for (int j = 0; j < vertices_cnt; ++j) {
            adjacency_matrix[i][j] = false;
        }
    }

    int diagonal_index = 0;
    for(int i = 0; i < vertices_cnt; ++i, ++diagonal_index) {
        for (int j = diagonal_index + 1; j < vertices_cnt; ++j) {
            int edge_index = CGraph::init_adjacency_matrix[i][j];
            if (edge_index != 0 && edges[edge_index - 1]) {
                adjacency_matrix[i][j] = true;
                adjacency_matrix[j][i] = true;
            }
        }
    }

    return adjacency_matrix;
}

bool CGraph::is_bipartite_graph() {

    // get adjacency matrix from vector of edges
    adjacency_matrix = get_adjacency_matrix();

    // array with vertices and their colors
    for (int i = 0; i < vertices_cnt; ++i) {
        // all vertex set uncolored
        vertices_colors[i] = -1;
    }

    // check all components
    for (int i = 0; i < vertices_cnt; ++i) {
        if (vertices_colors[i] == -1) {
            // if vertex is still uncolored I check it and its all neighbours
            if (!component_is_bigraph(i)) {
                return false;
            }
        }
    }

    return true;
}

bool CGraph::component_is_bigraph(int vertex_index) {

    // color first vertex
    vertices_colors[vertex_index] = 1;
    queue <int> q;
    q.push(vertex_index);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        // check all neighbours
        for (int v = 0; v < vertices_cnt; ++v) {
            if (adjacency_matrix[u][v] && vertices_colors[v] == -1) {
                // if vertex is still uncolored it gets second color
                vertices_colors[v] = (short) ((1 + vertices_colors[u]) % 2);
                // or = 1 - vertices_colors[u];
                q.push(v);
            } else if (adjacency_matrix[u][v] &&
                       vertices_colors[v] == vertices_colors[u]) {
                // vertex and its neighbour has the same color
                return false;
            }
        }
    }

    return true;
}

CGraph * CGraph::get_max_bigraph(CGraph *init_graph) {

    if (init_graph->is_bipartite_graph()) {
        return init_graph;
    }

    // stack of pointers
    stack <CGraph*> s;
    s.push(init_graph);
    CGraph * best_graph = NULL;

    // debug print into file
    // freopen("output.txt","w",stdout);

    int steps_cnt = 0, total_edges_cnt = init_graph->edges_cnt;

    while (!s.empty()) {

        steps_cnt++;

        CGraph * graph = s.top();
        s.pop();

        if (best_graph != NULL && best_graph->edges_cnt >= graph->edges_cnt) {
            // branch and bound: here is not necessary take away next edges
            delete graph;
            continue;
        }

        // save better result
        if (graph->is_bipartite_graph()) {
            if (best_graph == NULL) {
                // first result
                best_graph = graph;
                cout << "first solution: " << best_graph->edges_cnt << endl;
            } else if (graph->edges_cnt > best_graph->edges_cnt) {
                // better result
                best_graph = graph;
                cout << "better solution: " << best_graph->edges_cnt << endl;
            }
            continue;
        }

        int solved_by_others_index = 0;
        for (int i = total_edges_cnt - 1; i >= 0; --i) {
            if (!graph->edges[i]) {
                solved_by_others_index = i;
                break;
            }
        }

//        cout << solved_by_others_index << endl;
        for (int i = solved_by_others_index; i < total_edges_cnt; ++i) {

            if (graph->edges[i]) {

                bool * reduced_edges = new bool [total_edges_cnt];
                for (int j = 0; j < total_edges_cnt; ++j) {
                    reduced_edges[j] = graph->edges[j];
                }
                // remove one edge
                reduced_edges[i] = false;

//                cout << "push: ";
//                for (int k = 0; k < total_edges_cnt; ++k) {
//                    cout << reduced_edges[k] << ",";
//                } cout << endl;

                CGraph *subgraph = new CGraph(
                    graph->vertices_cnt,
                    graph->edges_cnt - 1,
                    reduced_edges,
                    graph->stack_depth + 1
                );

                s.push(subgraph);

            }
        }

        delete graph;
    }

    cout << "steps counter: " << steps_cnt << endl;

    return best_graph;
}

