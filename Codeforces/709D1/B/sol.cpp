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
const int MAXN = (int)1e5 + 10;

template <class T, class C = vector<T>> inline void printArray(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? '\n' : ' ');
    }
}

struct Node {
    Node *nxt;
    Node *skip;
    int a, idx;
};

array<int, MAXN> ans;

Node *find(Node *node, Node *start) {
    if (__gcd(node->a, node->nxt->a) == 1) {
        return node;
    }

    if (node->skip == start) {
        return NULL;
    }

    return node->skip = find(node->skip, start);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        vector<Node> data(n);
        for (int i = 0; i < n; i++) {
            cin >> data[i].a;
            data[i].nxt = &data[(i + 1) % n];
            data[i].skip = data[i].nxt;
            data[i].idx = i + 1;
        }

        int n_ans = 0;
        Node *start = &data[0];
        while (n_ans < n) {
            Node *node = find(start, start);
            if (node == NULL)
                break;
            ans[n_ans++] = node->nxt->idx;
            if (node->skip == node->nxt)
                node->skip = node->nxt->nxt;
            node->nxt = node->nxt->nxt;
            start = node->nxt;
        }
        cout << n_ans << ' ';
        for (int i = 0; i < n_ans; i++)
            cout << ans[i] << ' ';
        cout << endl;
    }

    return 0;
}
