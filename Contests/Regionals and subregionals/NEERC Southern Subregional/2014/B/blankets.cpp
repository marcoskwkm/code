#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXK = 1010;

int color[MAXK], sol[MAXK];
vector<int> ids[MAXK];


int main() {
    int k, n;
    cin >> k >> n;
    map<int, int> freq;
    for (int i = 0; i < k; i++) {
        scanf("%d", &color[i]);
        if (color[i] == -1) color[i] = 1;
        ids[color[i]].push_back(i);
        freq[color[i]]++;
    }
    set<pii, greater<pii>> s;
    for (pii p: freq) s.insert(pii(p.second, p.first));
    int q = k / n;

    while (!s.empty()) {
        pii c1 = *s.begin();
        // debug("cur: %d %d\n", c1.first, c1.second);
        s.erase(c1);
        if (s.empty()) {
            for (int i = 0; i < q; i++) {
                int id = ids[c1.second].back();
                ids[c1.second].pop_back();
                sol[id] = c1.second;
            }
            c1.first -= q;
            if (c1.first > 0) s.insert(c1);
        }
        else {
            pii c2 = *s.rbegin();
            s.erase(c2);
            if (c2.first >= q) {
                for (int i = 0; i < q; i++) {
                    int id = ids[c2.second].back();
                    ids[c2.second].pop_back();
                    sol[id] = c2.second;
                }
                c2.first -= q;
                if (c2.first > 0) s.insert(c2);
                s.insert(c1);
            }
            else {
                assert(c1.first + c2.first >= q);
                int take = q - c2.first;
                c1.first -= take;

                for (int i = 0; i < take; i++) {
                    int id = ids[c1.second].back();
                    ids[c1.second].pop_back();
                    sol[id] = c2.second;
                }
                for (int i = 0; i < c2.first; i++) {
                    int id = ids[c2.second].back();
                    ids[c2.second].pop_back();
                    sol[id] = c1.second;
                }
                if (c1.first > 0) s.insert(c1);
            }
        }
    }

    printf("Yes\n");
    for (int i = 0; i < k; i++)
        printf("%d %d\n", color[i], sol[i]);        
    return 0;
}
