//
// Created by marek on 4.3.17.
//

#include <string>
#include <iostream>
#include <fstream>
#include "CGraph.h"

using namespace std;

CGraph::CGraph(int vertices_cnt, bool** adjacency_matrix):
        vertices_cnt(vertices_cnt), adjacency_matrix(adjacency_matrix) {}

CGraph::~CGraph() {}

CGraph CGraph::load_graph(const char * path) {
    string line;
    int vertices_cnt;
    ifstream file(path);
    bool** adjacency_matrix;
    if (file.is_open()) {

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
    } else {
        cout << "Unable to open file" << endl;
    }
    cout << "Count of vertices = " << vertices_cnt << endl;
    for (int i = 0; i < vertices_cnt; i++) {
        for (int j = 0; j < vertices_cnt; j++) {
            cout << adjacency_matrix[i][j];
        }
        cout << endl;
    }
    return CGraph(vertices_cnt, adjacency_matrix);
}

