#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct Node {
    int val;
    Node *l, *r;
    Node(int x) { val = x; l = r = NULL; }
    void add(int x) {
        if (x < val) {
            if (l == NULL) l = new Node(x);
            else l->add(x);
        }
        else {
            if (r == NULL) r = new Node(x);
            else r->add(x);
        }
    }
};

void dfs(Node *node, string &s) {
    if (node->l != NULL) {
        s = s + "L";
        dfs(node->l, s);
    }
    if (node->r != NULL) {
        s = s + "R";
        dfs(node->r, s);
    }
    s = s + ".";
    return;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    set<string> cj;
    for (int i = 0; i < n; i++) {
        Node *tree;
        for (int j = 0; j < k; j++) {
            int x;
            scanf("%d", &x);
            if (!j) tree = new Node(x);
            else tree->add(x);
        }
        string rep = "";
        dfs(tree, rep);
        cj.insert(rep);
    }
    printf("%d\n", (int)cj.size());            
    return 0;
}
