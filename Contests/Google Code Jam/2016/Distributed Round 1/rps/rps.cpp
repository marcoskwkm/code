#include "rps.h"
#include <message.h>
#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int m = NumberOfNodes(), thisId = MyNodeId();
    int n = GetN(), nb = 0;
    int nbuckets = 0;
    if (thisId == 0) {
        while (nb + 1 < n && (1 << (nb + 1)) <= m) nb++;
        int q = (1 << (n - nb));
        nbuckets = (1 << nb);
        int cur = 0;
        for (int i = 0; i < nbuckets; i++) {
            PutInt(i, cur);
            PutInt(i, q);
            Send(i);
            cur += q;
        }
        for (int i = nbuckets; i < m; i++) {
            PutInt(i, -1);
            Send(i);
        }
    }

    int start, small_n;
    Receive(0);
    start = GetInt(0);
    if (start == -1) return 0;
    small_n = GetInt(0);
    vector<pair<char, int>> v(small_n);
    for (int i = 0; i < small_n; i++)
        v[i] = make_pair(GetFavoriteMove(i + start), i + start);
    char wins[300];
    wins['R'] = 'S';
    wins['S'] = 'P';
    wins['P'] = 'R';
    while (small_n > 1) {
        for (int i = 0; i < small_n; i += 2) {
            char l = v[i].first, r = v[i + 1].first;
            if (l == r || r == wins[l]) v[i / 2] = v[i];
            else v[i / 2] = v[i + 1];
        }
        small_n /= 2;
    }
    PutChar(0, v[0].first);
    PutInt(0, v[0].second);
    Send(0);

    if (thisId == 0) {
        vector<pair<char, int>> nv(nbuckets);
        for (int i = 0; i < nbuckets; i++) {
            Receive(i);
            char c = GetChar(i);
            int id = GetInt(i);
            nv[i] = make_pair(c, id);
        }
        while (nbuckets > 1) {
            for (int i = 0; i < nbuckets; i += 2) {
                char l = nv[i].first, r = nv[i + 1].first;
                if (l == r || r == wins[l]) nv[i / 2] = nv[i];
                else nv[i / 2] = nv[i + 1];
            }
            nbuckets /= 2;
        }
        printf("%d\n", nv[0].second);
    }    
    
    return 0;
}
