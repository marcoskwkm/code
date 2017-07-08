#include <bits/stdc++.h>
using namespace std;

typedef long long lint;
typedef pair<int ,int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const int MAXN = 10;
const int MAXND = (int)1e6 + 10;

struct Node {
    Node *nxt[MAXN];
    Node *prv;
};

Node data[MAXND];
int data_cnt;

Node *newnode(Node *prv) {
    for (int i = 0; i < MAXN; i++)
        data[data_cnt].nxt[i] = NULL;
    data[data_cnt].prv = prv;
    return &data[data_cnt++];
}

char grid[MAXN][MAXN];
int sol[MAXN][MAXN];

Node *trie[MAXN][MAXN][MAXN];

void trie_add(Node *cur, vector<int> &p) {
    for (int x: p) {
        if (cur->nxt[x] == NULL)
            cur->nxt[x] = newnode(cur);
        cur = cur->nxt[x];
    }
}

pii count_visible(vector<int> &p) {
    int n = (int)p.size();
    int hi = p[0];
    pii ret(1, 1);
    for (int i = 1; i < n; i++)
        if (p[i] > hi)
            hi = p[i], ret.first++;
    hi = p[n - 1];
    for (int i = n - 2; i >= 0; i--)
        if (p[i] > hi)
            hi = p[i], ret.second++;    
    return ret;
}

void generate_tries() {
    for (int len = 3; len <= 5; len++) {
        vector<int> p;
        for (int i = 1; i <= len; i++)
            p.push_back(i);
        for (int i = 0; i <= len; i++)
            for (int j = 0; j <= len; j++)
                trie[len][i][j] = newnode(NULL);
        do {
            int vis, visrev;
            tie(vis, visrev) = count_visible(p);
            trie_add(trie[len][0][0], p);
            trie_add(trie[len][0][visrev], p);
            trie_add(trie[len][vis][0], p);
            trie_add(trie[len][vis][visrev], p);
        } while (next_permutation(p.begin(), p.end()));
    }
}

vector< vector<int> > perm[MAXN][MAXN][MAXN];

void dfs(Node *t, vector<int> &p, int n, int i, int j) {
    bool is_leaf = 1;
    for (int k = 0; k < MAXN; k++) {
        if (t->nxt[k] != NULL) {
            p.push_back(k);
            dfs(t->nxt[k], p, n, i, j);
            p.pop_back();
            is_leaf = 0;
        }
    }
    if (is_leaf) perm[n][i][j].push_back(p);
}


void generate_perms() {
    for (int len = 3; len <= 5; len++) {
        for (int i = 0; i <= len; i++) {
            for (int j = 0; j <= len; j++) {
                vector<int> p;
                dfs(trie[len][i][j], p, len, i, j);
            }
        }
    }
}

bool solve(int row, int n, vector<Node*> &nodes) {
    if (row > n) return 1;
    int i = 0, j = 0;
    if (grid[row][0] != '-') i = grid[row][0] - '0';
    if (grid[row][n + 1] != '-') j = grid[row][n + 1] - '0';
    vector< vector<int> > &perms = perm[n][i][j];
    for (auto p: perms) {
        bool ok = 1;
        for (int col = 0; col < n; col++) {
            if ((grid[row][col + 1] != '-' &&
                 grid[row][col + 1] - '0' != p[col]) ||
                nodes[col]->nxt[p[col]] == NULL) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            for (int col = 0; col < n; col++)
                nodes[col] = nodes[col]->nxt[p[col]];
            if (solve(row + 1, n, nodes)) {
                for (int col = 0; col < n; col++)
                    sol[row][col + 1] = '0' + p[col];
                return 1;
            }
            for (int col = 0; col < n; col++)
                nodes[col] = nodes[col]->prv;
        }
    }
    return 0;
}

int main() {
    int t;
    generate_tries();
    generate_perms();
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i <= n + 1; i++)
            scanf("%s", grid[i]);
        vector<Node*> nodes;
        for (int c = 1; c <= n; c++) {
            int i = 0, j = 0;
            if (grid[0][c] != '-') i = grid[0][c] - '0';
            if (grid[n + 1][c] != '-') j = grid[n + 1][c] - '0';
            nodes.push_back(trie[n][i][j]);
        }
        if (!solve(1, n, nodes)) printf("no\n\n");
        else {
            for (int r = 1; r <= n; r++) {
                for (int c = 1; c <= n; c++)
                    printf("%c", sol[r][c]);
                printf("\n");
            }
            printf("\n");
        }
    }        
    return 0;
}
   
