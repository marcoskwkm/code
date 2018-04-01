#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXND = (int)1e7 + 10;
const int MAXN = (int)3e5 + 10;
const int LOG = 30;

struct Node {
    int q;
    Node *l, *r;
};

Node data[MAXND];

Node* newnode() {
    static int cnt = 0;
    data[cnt].q = 0;
    data[cnt].l = data[cnt].r = NULL;
    return &data[cnt++];
}

void trie_add(Node* trie, int p) {
    for (int i = LOG; i >= 0; i--) {
        if (p & (1 << i)) {
            if (trie->r == NULL) trie->r = newnode();
            trie = trie->r;
        }
        else {
            if (trie->l == NULL) trie->l = newnode();
            trie = trie->l;
        }
        trie->q++;
    }
}

int v[MAXN];

int main() {
    Node *trie = newnode();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    for (int i = 0; i < n; i++) {
        int p;
        scanf("%d", &p);
        trie_add(trie, p);
    }

    for (int i = 0; i < n; i++) {
        int res = 0;
        Node *cur = trie;
        for (int j = LOG; j >= 0; j--) {
            if (v[i] & (1 << j)) {
                if (cur->r && cur->r->q) cur = cur->r;
                else {
                    cur = cur->l;
                    res ^= (1 << j);
                }
            }
            else {
                if (cur->l && cur->l->q) cur = cur->l;
                else {
                    cur = cur->r;
                    res ^= (1 << j);
                }
            }
            cur->q--;
        }
        printf("%d ", res);
    }
    
    printf("\n");
    return 0;
}
