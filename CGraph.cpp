//
// Created by marek on 4.3.17.
//

#include <string>
#include <iostream>
#include <fstream>
#include "CGraph.h"

using namespace std;

CGraph::CGraph() {

}

CGraph CGraph::load_graph(const char * path) {
    string line;
    ifstream my_file(path);
    if (my_file.is_open()) {
        while (getline(my_file, line)) {
            cout << line << endl;
        }
        my_file.close();
    } else {
        cout << "Unable to open file";
    }
    return CGraph();
}
