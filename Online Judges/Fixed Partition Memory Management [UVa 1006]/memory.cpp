#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 12, MAXM = 60;

const int NREP = 100;
const int NMOVES = 10000;

int memory[MAXN];
int length[MAXM][MAXN];

multiset<int> ms[MAXN];
int location[MAXM];
int n, m;

lint get() {
    lint ret = 0;
    for (int i = 0; i < n; i++) {
        lint acc = 0;
        for (int x: ms[i]) {
            ret += acc + x;
            acc += x;
        }
    }
    return ret;
}

int main() {
    while (scanf("%d%d", &n, &m) && n) {
        for (int i = 0; i < n; i++)
            scanf("%d", &memory[i]);
        for (int i = 0; i < m; i++) {
            int k;
            scanf("%d", &k);
            vector<pii> v;
            for (int j = 0; j < k; j++) {
                int a, b;
                scanf("%d%d", &a, &b);
                v.push_back(pii(a, b));
            }
            for (int j = 0 ; j < n; j++) {
                length[i][j] = INF;
                for (int l = 0; l < k; l++) {
                    if (v[l].first > memory[j]) break;
                    length[i][j] = v[l].second;
                }
            }
        }

        lint ans = LINF;
        for (int nrep = 0; nrep < NREP; nrep++) {
            for (int i = 0; i < n; i++)
                ms[i].clear();
            for (int i = 0; i < m; i++) {
                int sel = rand() % n;
                ms[sel].insert(length[i][sel]);
                location[i] = sel;
            }

            ans = min(ans, get());
            
        
    return 0;
}
