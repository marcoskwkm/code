#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;

lint modexp(int b, int e) {
    lint ret = 1;
    for (int i = 0; i < e; i++)
        ret = ret * b % MOD;
    return ret;
}

int main() {
    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        string folds, cut;
        cin >> folds >> cut;
        for (char &c: folds) {
            if (c == 'T') c = 0;
            else if (c == 'L') c = 1;
            else if (c == 'R') c = 2;
            else c = 3;
        }
        for (char &c: cut) {
            if (c == 'T') c = 0;
            else if (c == 'L') c = 1;
            else if (c == 'R') c = 2;
            else c = 3;
        }
        
        int nV = 0, nH = 0;
        char lastV = 0, lastH = 0;
        for (char c: folds) {
            if (c == 0 || c == 3) {
                nH++;
                lastH = c;
            }
            else {
                nV++;
                lastV = c;
            }
        }
        if (cut[0] + cut[1] == 3) {
            if (cut[0] == 0 || cut[1] == 0)
                cout << (modexp(2, nV) + 1) % MOD << endl;
            else
                cout << (modexp(2, nH) + 1) % MOD << endl;
        }
        else {
            lint ansV = 1, ansH = 1;
            if (nV > 0) {
                ansV = modexp(2, nV - 1);
                if (cut[0] == 3 - lastV || cut[1] == 3 - lastV) ansV++;
            }
            if (nH > 0) {
                ansH = modexp(2, nH - 1);
                if (cut[0] == 3 - lastH || cut[1] == 3 - lastH) ansH++;
            }
            cout << (ansV * ansH + 1) % MOD << endl;
        }
    }        
    return 0;
}
