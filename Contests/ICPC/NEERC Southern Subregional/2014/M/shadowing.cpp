#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 30;

struct Occurence {
    int r, c, s;
    Occurence(int _r, int _c, int _s) : r(_r), c(_c), s(_s) {}
};

stack<Occurence> occ[MAXN];

int main() {
    int cur_scope = 0;
    int lines;
    cin >> lines;
    string line;
    getline(cin, line);
    for (int row = 1; row <= lines; row++) {
        getline(cin, line);
        for (int col = 0; col < (int)line.size(); col++) {
            if (isspace(line[col])) continue;
            if (line[col] == '{') cur_scope++;
            else if (line[col] == '}') {
                for (int i = 0; i < MAXN; i++)
                    if (!occ[i].empty() && occ[i].top().s == cur_scope)
                        occ[i].pop();
                cur_scope--;
            }
            else {
                int i = line[col] - 'a';
                if (!occ[i].empty()) {
                    printf("%d:%d: warning: shadowed declaration of %c, the shadowed position is %d:%d\n",
                           row, col + 1, line[col], occ[i].top().r, occ[i].top().c);
                }
                occ[i].push(Occurence(row, col + 1, cur_scope));
            }
        }
    }        
    return 0;
}
