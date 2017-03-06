//
// Created by marek on 6.3.17.
//

#include <stack>
#include "CMaxBigraph.h"

// TODO: az tohle dopisu, rozmyslet se, jestli to nedat pod CGraph s tim, ze to bude staticka metoda
// TODO: ona totiz vsechno ziska na vstupu, pouze vrati ten nejlepsi stav, ktery vytvori az tady
CGraph * CMaxBigraph::evaluate(CGraph * init_graph) {

    if (init_graph->is_bipartite_graph()) {
        return init_graph;
    }

    // stack of pointers
    stack <CGraph*> s;
    s.push(init_graph);

    CGraph * best_graph = NULL;

    while (!s.empty()) {
        CGraph * graph = s.top();
        s.pop();

//        if (best_result != NULL && get_edges_cnt(adjacency_matrix) <= best_result->edges_cnt) {
//            // branch and bound: here is not necessary take away next edges
//            continue;
//        }

//         TODO: neco je divne, protoze i s touto podminkou to hleda neumerne dlouho
//        if (best_result != NULL && get_edges_cnt(adjacency_matrix) <= 18) {
//            // branch and bound: here is not necessary take away next edges
//            continue;
//        }

        // debug print
        for (int i = 0; i < graph->vertices_cnt; ++i) {
            for (int j = 0; j < graph->vertices_cnt; ++j) {
                cout << graph->adjacency_matrix[i][j];
            }
        } cout << endl;

        // save better result
        if (graph->is_bipartite_graph()) {
            if (best_graph == NULL) {
                // first result
                best_graph = graph;
            } else if (graph->edges_cnt > best_graph->edges_cnt) {
                // better result
                best_graph = graph;
                cout << "BETTER RESULT: " << best_graph->edges_cnt << endl;
            }
        }

        cout << graph->edges_cnt << " " << graph->is_bigraph << endl;
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
//        TODO: musim v konstruktoru pridat pocet edges, abych si to nemusel sam vypocitavat
        // loop over upper triangular matrix where is every edge only once
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
    }

    return best_graph;
}
