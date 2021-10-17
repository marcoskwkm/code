#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readArray(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXND = 1e7;

template<class Fun> class y_combinator_result {
    Fun fun_;

  public:
    template<class T> explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}

    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return fun_(ref(*this), forward<Args>(args)...);
    }
};

template<class Fun> decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
}

template<class T = int> inline T read() {
    T x;
    cin >> x;
    return x;
}

template<class T, class C = vector<T>> inline void printArray(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? "" : " ");
    }
    cout << '\n';
}

struct Node {
    int s;
    Node *l, *r;
};

Node nodes[MAXND];
int nodes_cnt = 0;

Node *newnode(Node *cur) {
    Node *node = &nodes[nodes_cnt++];

    if (cur == NULL) {
        node->s = 0;
        node->l = node->r = NULL;
    } else {
        node->s = cur->s;
        node->l = cur->l;
        node->r = cur->r;
    }

    return node;
}

Node *update(Node *node, int l, int r, int x, int val) {
    Node *nxtnode = newnode(node);

    if (x < l || x > r) {
        return nxtnode;
    }

    nxtnode->s += val;

    if (l < r) {
        int m = (l + r) / 2;
        nxtnode->l = update(nxtnode->l, l, m, x, val);
        nxtnode->r = update(nxtnode->r, m + 1, r, x, val);
    }

    return nxtnode;
}

int query(Node *node, int l, int r, int ql, int qr) {
    if (node == NULL || r < ql || qr < l) {
        return 0;
    } else if (ql <= l && r <= qr) {
        return node->s;
    }

    int m = (l + r) / 2;
    return query(node->l, l, m, ql, qr) + query(node->r, m + 1, r, ql, qr);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<Node *> history;
    history.push_back(newnode(NULL));

    string foo;
    getline(cin, foo);
    for (int i = 0; i < n; i++) {
        Node *tree = history.back();

        string line;
        getline(cin, line);
        stringstream ss(line);
        string token;
        while (ss >> token) {
            char op;
            int x;
            sscanf(token.c_str(), " %c%d", &op, &x);
            tree = update(tree, 0, n - 1, x, op == '+' ? 1 : -1);
        }
        history.push_back(tree);
    }

    int x = 0;
    for (int i = 0; i < n; i++) {
        int d;
        cin >> d;
        x = (x + query(history[d], 0, n - 1, x, n - 1)) % n;
    }

    cout << x << endl;
    return 0;
}
