#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;

map<string, int> mp;
string rev[MAXN];
int get_idx(const string &s) {
    static int cnt = 1;
    auto it = mp.find(s);
    if (it == mp.end()) {
        rev[cnt] = s;
        return mp[s] = cnt++;
    }
    return it->second;
}

vector<int> adj[2][MAXN];
bool has[2][MAXN];

void dfs(int v, int k) {
    has[k][v] = 1;
    // debug("has[%d][%s] = 1\n", k, rev[v].c_str());
    for (int nxt: adj[k][v])
        if (!has[k ^ 1][nxt])
            dfs(nxt, k ^ 1);
}        

int main() {
    vector<string> input;
    string w;
    while (cin >> w) {
        string trim = w.substr(0, w.size() - 1);
        if (w.back() == '.') {
            input.push_back(trim);
            input.push_back(". ");
        }
        else if (w.back() == ',') {
            input.push_back(trim);
            input.push_back(", ");
        }
        else {
            input.push_back(w);
            input.push_back(" ");
        }
    }

    for (int i = 0; i + 2 < (int)input.size(); i += 2) {
        int u = get_idx(input[i]), v = get_idx(input[i + 2]);
        if (input[i + 1] != ". ") {
            adj[0][u].push_back(v);
            adj[1][v].push_back(u);
        }
    }

    for (int i = 0; i + 2 < (int)input.size(); i += 2) {
        int u = get_idx(input[i]), v = get_idx(input[i + 2]);
        if (input[i + 1] == ", ") {
            if (!has[0][u]) {
                // debug("dfs %s\n", rev[u].c_str());
                dfs(u, 0);
            }
        }
    }

    for (int i = 0; i < (int)input.size(); i += 2) {
        int idx = get_idx(input[i]);
        if (i + 1 < (int)input.size() && has[0][idx] && input[i + 1] != ". ")
            input[i + 1] = ", ";
        if (i - 1 >= 0 && has[1][idx] && input[i - 1] != ". ")
            input[i - 1] = ", ";
    }

    for (int i = 0; i + 1 < (int)input.size(); i++)
        printf("%s", input[i].c_str());
    printf(".\n");
    
    return 0;
}
