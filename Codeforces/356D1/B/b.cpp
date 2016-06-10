#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

inline lint cube(lint n) { return n*n*n; }

int main() {
    lint m;
    cin >> m;
    int n = 0;
    lint v = 0;
    bool cont = 1;
    vector<lint> cubes;
    for (lint size = 1; cont; size++) {
        cont = 0;
        while (v + cube(size) < cube(size + 1) && v + cube(size) <= m) {
            cont = 1;
            v += cube(size);
            n++;
            cubes.push_back(size);
        }
    }
    reverse(cubes.begin(), cubes.end());
    for (lint &c: cubes) {
        while (1) {
            lint delta = cube(c + 1) - cube(c);
            if (v + delta <= m) {
                c++;
                v += delta;
            }
            else break;
        }
    }
    printf("%d %lld\n", n, v);
    for (lint c: cubes) printf("%lld ", cube(c));
    printf("\n");
    return 0;
}
