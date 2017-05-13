#include <bits/stdc++.h>
using namespace std;

int main() {
    Graph g(8);
    vector<pair<int, int>> edges = {
        {2, 3},
        {1, 3},
        {3, 6},
        {6, 1},
        {1, 7},
        {6, 7},
        {6, 4},
        {7, 5},
        {5, 7},
    };
    for (auto p: edges) g.add_edge(p.first, p.second);
    Tarjan t(g);
    assert(set<int>(t.cmp[t.cmp_id[0]].begin(), t.cmp[t.cmp_id[0]].end()) == (set<int> {0}));    
    assert(set<int>(t.cmp[t.cmp_id[1]].begin(), t.cmp[t.cmp_id[1]].end()) == (set<int> {1, 3, 6}));
    assert(set<int>(t.cmp[t.cmp_id[2]].begin(), t.cmp[t.cmp_id[2]].end()) == (set<int> {2}));    
    assert(set<int>(t.cmp[t.cmp_id[4]].begin(), t.cmp[t.cmp_id[4]].end()) == (set<int> {4}));    
    assert(set<int>(t.cmp[t.cmp_id[5]].begin(), t.cmp[t.cmp_id[5]].end()) == (set<int> {5, 7}));
    fprintf(stderr, "Test passed!\n");
    return 0;
}
