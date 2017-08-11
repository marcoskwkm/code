#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;
typedef tuple<lint, lint, lint> tlll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct Segment {
    int x1, x2, y1, y2, a, b;
    Segment(int _x1 = 0, int _x2 = 0, int _y1 = 0, int _y2 = 0, int _a = 0, int _b = 0) {
        x1 = _x1, x2 = _x2, y1 = _y1, y2 = _y2, a = _a, b = _b;
    }
};

tlll operator+(tlll a, tlll b) {
    lint a0, a1, a2, b0, b1, b2;
    tie(a0, a1, a2) = a;
    tie(b0, b1, b2) = b;
    return tlll(a0 + b0, a1 + b1, a2 + b2);
}

struct PersistentSegmentTree {
    static const int MAXND = (int)2e7 + 10;
    struct Node {
        lint a, b, y;
        Node *l, *r;
    };
    static Node data[MAXND];
    static int data_cnt = 0;

    int n;

    Node* newnode(lint a = 0, lint b = 0, lint y = 0) {
        data[data_cnt].a = a;
        data[data_cnt].b = b;
        data[data_cnt].y = y;
        return &data[data_cnt++];
    }

    vector<Node*> history;

    PersistentSegmentTree(int _n) : n(_n) {
        history.push_back(build(0, n - 1));
    }

    Node* build(int l, int r) {
        Node* node = newnode();
        if (l < r) {
            int mid = (l + r) / 2;
            node->l = build(l, mid);
            node->r = build(mid + 1, r);
        }
        return node;
    }

    Node* update(Node *tree, int l, int r, int x, int a, int b, int y) {
        if (x < l || x > r) return tree;
        Node* node = newnode();
        if (l == r) {
            node->a = tree->a + a;
            node->b = tree->b + b;
            node->y = tree->y + y;
        }
        else {
            int mid = (l + r) / 2;
            node->l = update(tree->l, l, mid, x, a, b);
            node->r = update(tree->r, mid + 1, r, x, a, b);
        }
        return node;
    }
    void update(int x, int a, int b, int y) {
        history.push_back(update(history.back(), 0, n - 1, x, a, b, y));
    }

    tlll query(Node *tree, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) return tlll(0, 0, 0);
        if (ql <= l && r <= qr) return tlll(tree->a, tree->b, tree->y);
        int mid = (l + r) / 2;
        return query(tree->l, l, mid, ql, qr) + query(tree->r, mid + 1, r, ql, qr);
    }
    
    tlll query(int i, int l, int r) {
        return query(history[i], 0, n - 1, l, r);
    }
};    

int main() {
    int n;
    cin >> n;
    lint sum_a = 0, sum_b = 0;
    const int MAXX = 2e5 + 10;
    PersistentSegmentTree tx1(MAXX), tx2(MAXX);
    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2, a, b;
        scanf("%d%d%d%d%d%d", &x1, &x2, &y1, &a, &b, &y2);
        sum_a += a, sum_b += b;
        tx1.update(x1, a, b, y1);
        tx2.update(x2, a, b, y2);
    }
    lint last = 0;
    int q;
    for (cin >> q; q--;) {
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        x = (x + last) % 1000000000;
        lint sa = sum_a, sb = sum_b;
        tlll got = tx1.query(r, x + 1, MAXX);
    
    
        
    return 0;
}
