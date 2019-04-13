#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010, MAXW = 50;
const int MAXND = MAXN * MAXW;

struct Node {
    int cnt;
    Node *nxt[30];
};
Node data[MAXND];
int data_cnt;

Node *newnode() {
    data[data_cnt].cnt = 0;
    memset(data[data_cnt].nxt, 0, sizeof(data[data_cnt].nxt));
    return &data[data_cnt++];
}

void add_word(const string &s, Node *node, size_t i) {
    node->cnt++;
    if (i == s.size()) return;
    
    if (node->nxt[s[i] - 'A'] == NULL)
        node->nxt[s[i] - 'A'] = newnode();
    
    add_word(s, node->nxt[s[i] - 'A'], i + 1);
}

int solve(Node *node, int depth = 0) {
    if (node == NULL) return 0;
    int ret = 0;
    for (int i = 0; i < 30; i++)
        ret += solve(node->nxt[i], depth + 1);

    // int val = ret + (node->cnt - ret >= 2 ? 2 : 0);
    // for (int i = 0; i < depth; i++) debug("\t");
    // debug("%d\n", val);
    
    return ret + (node->cnt - ret >= 2 ? 2 : 0);
}    

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        data_cnt = 0;
        Node *root = newnode();
        
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            string w;
            cin >> w;
            reverse(w.begin(), w.end());
            add_word(w, root, 0);
        }

        int ans = 0;
        for (int i = 0; i < 30; i++)
            ans += solve(root->nxt[i]);
        
        printf("Case #%d: %d\n", t, ans);
        // debug("--------------\n");
    }        
    return 0;
}
z
