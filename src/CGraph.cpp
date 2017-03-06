#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include "CGraph.h"

using namespace std;

// TODO: pokud vim, kolik mam na zacatku hran, tak pak to nemusim pocitat pokazde, kdyz nejakou odeberu
// TODO: jen si to musim nekde pamatovat

CGraph::CGraph(int vertices_cnt, int edges_cnt, bool ** adjacency_matrix):
        vertices_cnt(vertices_cnt), edges_cnt(edges_cnt), adjacency_matrix(adjacency_matrix) {}

CGraph::~CGraph() {
    for(int i = 0; i < vertices_cnt; ++i) {
        delete[] adjacency_matrix[i];
    }
    delete[] adjacency_matrix;
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
    adjacency_matrix = new bool*[vertices_cnt];
    for (int i = 0; i < vertices_cnt; i++) {
        adjacency_matrix[i] = new bool[vertices_cnt];
        getline(file, line);
        for (int j = 0; j < line.length(); j++) {
            adjacency_matrix[i][j] = line[j] == '1';
        }
    }

    file.close();

    // debug print
    cout << "============================" << endl;
    cout << "Count of vertices = " << vertices_cnt << endl;
    for (int i = 0; i < vertices_cnt; i++) {
        for (int j = 0; j < vertices_cnt; j++) {
            cout << adjacency_matrix[i][j];
           }
        cout << endl;
    }
    cout << "============================" << endl;

    return new CGraph(
            vertices_cnt,
            get_edges_cnt(vertices_cnt, adjacency_matrix),
            adjacency_matrix
    );
}



//
//
//CResult * CGraph::evaluate(vector<vector<bool>> & adjacency_matrix) {
//
//    int edges_cnt = get_edges_cnt(vertices_cnt, adjacency_matrix);
//
//    // array with vertices and their colors
//    int vertices_colors[vertices_cnt];
//    for (int i = 0; i < vertices_cnt; ++i) {
//        // all vertex aren't colored
//        vertices_colors[i] = -1;
//    }
//
//    // check all components
//    for (int i = 0; i < vertices_cnt; ++i) {
//        if (vertices_colors[i] == -1) {
//            // if vertex is still uncolored I check it and its all neighbours
//            if (!component_is_bigraph(adjacency_matrix, vertices_colors, i)) {
//                return new CResult(false, vertices_cnt, edges_cnt, vertices_colors);
//            }
//        }
//    }
//
//    return new CResult(true, vertices_cnt, edges_cnt, vertices_colors);
//}
//
//CResult CGraph::get_max_bigraph() {
//
//    CResult * graph = this->evaluate(this->adjacency_matrix);
//    if (graph->is_bigraph) {
//        cout << "Init graph is bigraph." << endl;
//        return *graph;
//    }
//
//    cout << "total edges: " << graph->edges_cnt << endl;
//
//    stack <vector<vector<bool>>> s;
//    s.push(this->adjacency_matrix);
//
//    int k = 0;
//    while (!s.empty()) {
//        vector<vector<bool>> adjacency_matrix;
//        adjacency_matrix = s.top();
//        s.pop();
//
////        if (best_result != NULL && get_edges_cnt(adjacency_matrix) <= best_result->edges_cnt) {
////            // branch and bound: here is not necessary take away next edges
////            continue;
////        }
//
////         TODO: neco je divne, protoze i s touto podminkou to hleda neumerne dlouho
////        if (best_result != NULL && get_edges_cnt(adjacency_matrix) <= 18) {
////            // branch and bound: here is not necessary take away next edges
////            continue;
////        }
//
//
//        // debug print
//        for (int i = 0; i < vertices_cnt; ++i) {
//            for (int j = 0; j < vertices_cnt; ++j) {
//                cout << adjacency_matrix[i][j];
//            } //cout << endl;
//        } cout << endl;
//
//
//        graph = evaluate(adjacency_matrix);
//
////        cout << graph->edges_cnt << " " << graph->is_bigraph << endl;
////        cout << "-------------" << endl;
//
//
//        if (graph->is_bigraph) {
//            if (best_result == NULL) {
//                // first result
//                best_result = graph;
//            } else if (graph->edges_cnt > best_result->edges_cnt) {
//                // better result
//                best_result = graph;
//                cout << best_result->edges_cnt << endl;
//            }
//        }
//
//        if (graph->edges_cnt < vertices_cnt - 1) {
//            // branch and bound: here is not necessary take away next edges
//            continue;
//        }
//
//        // loop over upper triangular matrix where is every edge only once
//        int diagonal_index = 0;
//            for (int j = diagonal_index + 1; j < vertices_cnt; ++j) {
//        for (int i = 0; i < vertices_cnt; ++i, ++diagonal_index) {
//                if (adjacency_matrix[i][j]) {
//                    vector<vector<bool>> constricted_adjacency_matrix = adjacency_matrix;
//                    constricted_adjacency_matrix[i][j] = false;
//                    constricted_adjacency_matrix[j][i] = false;
//                    s.push(constricted_adjacency_matrix);
//                }
//            }
//        }
//    }
//    return *best_result;
//}

int CGraph::get_edges_cnt(int vertices_cnt, bool ** adjacency_matrix) {
    // get count of edges
    int diagonal_index = 0, edges_cnt = 0;
    for (int i = 0; i < vertices_cnt; ++i, ++diagonal_index) {
        for (int j = diagonal_index + 1; j < vertices_cnt; ++j) {
            if (adjacency_matrix[i][j]) {
                ++edges_cnt;
            }
        }
    }
    return edges_cnt;
}

ostream & operator << (ostream & os, const CGraph & graph) {
    os << "Colors of graph: ";
    for (int i = 0; i < graph.vertices_cnt; ++i) {
        os << graph.vertices_colors[i];
    }
    os << ", number of edges: " << graph.edges_cnt;
    return os;
}

bool CGraph::is_bipartite_graph() {

    // array with vertices and their colors
    vertices_colors = new short int[vertices_cnt];
    for (int i = 0; i < vertices_cnt; ++i) {
        // all vertex set uncolored
        vertices_colors[i] = -1;
    }

    // check all components
    for (int i = 0; i < vertices_cnt; ++i) {
        if (vertices_colors[i] == -1) {
            // if vertex is still uncolored I check it and its all neighbours
            if (!component_is_bigraph(i)) {
                is_bigraph = false;
                return false;
            }
        }
    }

    is_bigraph = true;
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