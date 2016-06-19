#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef pair<pll, int> ppi;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;
const int MAXND = (int)2e7 + 10;

struct Node {
    int l, r;
    lint sa, sb;
    Node *nxtl, *nxtr;
    Node(int ll = 0, int rr = 0, lint a = 0, lint b = 0) {
        l = ll, r = rr, sa = a, sb = b;
        nxtl = nxtr = NULL;
    }
};

Node data[MAXND];
int data_cnt;
Node *newnode(int l, int r, lint sa, lint sb) {
    assert(data_cnt < MAXND);
    data[data_cnt] = Node(l, r, sa, sb);
    return &data[data_cnt++];
}

Node* head[MAXN];

void build(Node *cur) {
    if (cur->l == cur->r) return;
    int mid = (cur->l + cur->r) / 2;
    cur->nxtl = newnode(cur->l, mid, 0, 0);
    cur->nxtr = newnode(mid + 1, cur->r, 0, 0);
    build(cur->nxtl); build(cur->nxtr);
}

Node* update(Node *cur, int pos, lint va, lint vb) {
    if (cur->l > pos || cur->r < pos) return cur;
    Node* newn = newnode(cur->l, cur->r, cur->sa, cur->sb);
    if (cur->l == cur->r) {
        newn->sa += va;
        newn->sb += vb;
    }
    else {
        newn->nxtl = update(cur->nxtl, pos, va, vb);
        newn->nxtr = update(cur->nxtr, pos, va, vb);
        newn->sa = newn->nxtl->sa + newn->nxtr->sa;
        newn->sb = newn->nxtl->sb + newn->nxtr->sb;
    }
    return newn;
}

lint query(Node *cur, int l, int r, lint c, lint d) {
    if (cur->l > r || cur->r < l) return 0;
    if (l <= cur->l && cur->r <= r) {
        return cur->sa * c - cur->sb * d;
    }
    return query(cur->nxtl, l, r, c, d) + query(cur->nxtr, l, r, c, d);
}

lint A[MAXN], B[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    vector<ppi> v;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &A[i]);
        assert(0 <= A[i]);
        assert(A[i] <= 1000000);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &B[i]);
        assert(0 <= B[i]);
        assert(B[i] <= 1000000);
    }
    for (int i = 0; i < n; i++) {
        if (A[i] || B[i]) v.push_back(ppi(pll(A[i], B[i]), i + 1));
    }
    sort(v.begin(), v.end(), [](ppi a, ppi b) {
        return a.first.second * b.first.first < b.first.second * a.first.first;
    });

    head[0] = newnode(1, n, 0, 0);
    build(head[0]);
    for (int i = 0; i < n; i++) {
        if (v[i].first.first == 0)
            head[i + 1] = update(head[i], v[i].second, 0, 0);
        else
        head[i + 1] = update(head[i], v[i].second, v[i].first.first, v[i].first.second);
    }

    int q;
    for (scanf("%d", &q); q--;) {
        lint l, r, c, d;
        scanf("%lld%lld%lld%lld", &l, &r, &c, &d);
        assert(0 <= c && c <= 1000000);
        assert(0 <= d && d <= 1000000);
        int ll = 0, rr = v.size();
        while (ll < rr) {
            int mid = (ll + rr + 1) / 2;
            if (v[mid - 1].first.second * d <= c * v[mid - 1].first.first)
                ll = mid;
            else
                rr = mid - 1;
        }
        printf("%lld\n", query(head[ll], l, r, c, d));
        fflush(stdout);
    }        
    return 0;
}
