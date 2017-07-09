#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

const vector<string> color = {"white", "black"};
const vector<string> piece = {
    "pawn",
    "rook",
    "knight",
    "bishop",
    "queen",
    "king"
};

int needs[2][10];

int main() {
    int n1, n2;
    scanf("%d%d", &n1, &n2);
    map<string, int> color_m, piece_m;
    for (int i = 0; i < 2; i++)
        color_m[color[i]] = i;
    for (int i = 0; i < 6; i++)
        piece_m[piece[i]] = i;

    for (int c = 0; c < 2; c++) {
        for (int p = 0; p < 6; p++) {
            if (p == 0) needs[c][p] = 8;
            else if (p >= 4) needs[c][p] = 1;
            else needs[c][p] = 2;
        }
    }            

    int rem = 32;
    for (int i = 0; i < n1; i++) {
        string c, p;
        cin >> c >> p;
        int ic = color_m[c], ip = piece_m[p];
        if (needs[ic][ip] > 0) {
            needs[color_m[c]][piece_m[p]]--;
            rem--;
        }
    }
    vector< pair<string, string> > ans;
    for (int i = 0; i < n2; i++) {
        string c, p;
        cin >> c >> p;
        int ic = color_m[c], ip = piece_m[p];
        if (needs[ic][ip] > 0) {
            ans.push_back(make_pair(c, p));
            needs[ic][ip]--;
            rem--;
        }
    }

    if (rem > 0) printf("impossible\n");
    else {
        for (auto ps: ans)
            cout << ps.first << " " << ps.second << endl;
    }    
    return 0;
}
