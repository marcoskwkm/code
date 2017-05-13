#include <bits/stdc++.h>
using namespace std;

#include "../Graph.h"
#include "../TopSort.h"

int main() {
    Graph g(8);
    vector<pair<int, int>> edges = {
        {0, 3},
        {6, 3},
        {3, 5},
        {3, 1},
        {2, 5},
        {5, 1},
        {5, 7},
        {1, 7},
        {7, 4},              
    };
    for (auto p: edges) g.add_edge(p.first, p.second);
    TopSort ts(g);
    for (int v: ts.ord) printf("%d ", v);
    printf("\n");
    // expected: 0 2 6 3 5 1 7 4 or similar
    return 0;
}
