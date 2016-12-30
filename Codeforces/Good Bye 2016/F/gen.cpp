#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int main(int argc, char* argv[]) {
    int h;
    sscanf(argv[1], "%d", &h);
    srand(time(0));
    vector<int> v;
    int n = (1 << h) - 1;
    for (int i = 1; i <= n; i++)
        v.push_back(i);
    random_shuffle(v.begin(), v.end());
    printf("%d\n", h);
    vector<pii> edges;
    for (int i = 0; i < (1 << (h - 1)) - 1; i++) {
        edges.push_back(pii(v[i], v[2*i + 1]));
        edges.push_back(pii(v[i], v[2*i + 2]));
    }
    random_shuffle(edges.begin(), edges.end());
    for (pii p: edges) {
        if (rand() & 1) printf("%d %d\n", p.first, p.second);
        else printf("%d %d\n", p.second, p.first);
    }
    return 0;
}
