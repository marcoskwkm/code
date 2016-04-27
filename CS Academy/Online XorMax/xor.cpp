#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int MAXND = (int)3e7 + 10;
const int LOG = 29;

struct Node {
    int q;
    Node *l, *r; // 0, 1
};

int data_cnt;
Node data[MAXND];
Node *newnode() {
    if (data_cnt == MAXND) while (1);
    data[data_cnt].q = 0;
    data[data_cnt].l = data[data_cnt].r = NULL;
    return &data[data_cnt++];
}

int v[MAXN], p[MAXN], x[MAXN];
bool avail[MAXN];

Node *trieL[MAXN], *trieR[MAXN];

void add(Node *trie, int n) {
    trie->q++;
    for (int i = LOG; i >= 0; i--) {
        if (n & (1 << i)) {
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

int getmax(Node *trie, int n) {
    int ret = 0;
    for (int i = LOG; i >= 0; i--) {
        if (n & (1 << i)) {
            if (trie->l != NULL) {
                trie = trie->l;
                ret ^= (1 << i);
            }
            else trie = trie->r;
        }
        else {
            if (trie->r != NULL) {
                trie = trie->r;
                ret ^= (1 << i);
            }
            else trie = trie->l;
        }
    }
    return ret;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        x[i] = v[i] ^ x[i - 1];
        trieL[i] = trieR[i] = NULL;
    }
    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);
    stack<int> st;
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        avail[p[i]] = 1;
        ans = max(ans, v[p[i]]);
        if (!avail[p[i] - 1] && !avail[p[i] + 1]) {
            trieL[p[i]] = newnode();
            trieR[p[i]] = newnode();
            add(trieL[p[i]], x[p[i] - 1]);
            add(trieR[p[i]], x[p[i]]);
        }
        else if (avail[p[i] - 1] && avail[p[i] + 1]) {
            if (trieL[p[i] - 1]->q < trieL[p[i] + 1]->q) {
                for (int j = p[i]; avail[j]; j--) {
                    ans = max(ans, getmax(trieR[p[i] + 1], x[j - 1]));
                    trieL[j] = trieL[p[i] + 1];
                    trieR[j] = trieR[p[i] + 1];
                    add(trieL[j], x[j - 1]);
                    add(trieR[j], x[j]);
                }
            }
            else {
                for (int j = p[i]; avail[j]; j++) {
                    ans = max(ans, getmax(trieL[p[i] - 1], x[j]));
                    trieL[j] = trieL[p[i] - 1];
                    trieR[j] = trieR[p[i] - 1];
                    add(trieL[j], x[j - 1]);
                    add(trieR[j], x[j]);
                }
            }
        }
        else if(avail[p[i] - 1]) {
            ans = max(ans, getmax(trieL[p[i] - 1], x[p[i]]));
            trieL[p[i]] = trieL[p[i] - 1];
            trieR[p[i]] = trieR[p[i] - 1];
            add(trieL[p[i]], x[p[i] - 1]);
            add(trieR[p[i]], x[p[i]]);
        }
        else if (avail[p[i] + 1]) {
            ans = max(ans, getmax(trieR[p[i] + 1], x[p[i] - 1]));
            trieL[p[i]] = trieL[p[i] + 1];
            trieR[p[i]] = trieR[p[i] + 1];
            add(trieL[p[i]], x[p[i] - 1]);
            add(trieR[p[i]], x[p[i]]);
        }
        st.push(ans);
    }
    while (!st.empty()) {
        printf("%d\n", st.top());
        st.pop();
    }
    return 0;
}
