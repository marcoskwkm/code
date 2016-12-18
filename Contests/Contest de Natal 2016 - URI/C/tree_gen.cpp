#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int main(int argc, char* argv[]) {
    srand(time(0));
    int n;
    sscanf(argv[1], "%d", &n);
    printf("%d\n", n);
    vector<pii> edges;
    for (int v = 2; v <= n; v++) {
        int u = rand() % (v - 1) + 1;
        edges.push_back(pii(u, v));
    }
    vector<int> idx;
    for (int i = 1; i <= n; i++)
        idx.push_back(i);
    random_shuffle(idx.begin(), idx.end());
    for (pii p: edges)
        printf("%d %d\n", idx[p.first - 1], idx[p.second - 1]);
    return 0;
}
