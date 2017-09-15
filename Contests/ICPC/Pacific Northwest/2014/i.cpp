#include <bits/stdc++.h>
using namespace std;

typedef long long lint;
typedef pair<int ,int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const int MAXN = (int)1e6 + 10;

vector<int> subs[MAXN];
int tree_l[4 * MAXN], tree_r[4 * MAXN];
pii tree[4 * MAXN];
int who[MAXN];
int salary[MAXN];
int lazy[4 * MAXN];

int cnt;
void dfs(int v) {
    tree_l[v] = cnt;
    for (int sub: subs[v])
	dfs(sub);
    who[cnt] = v;
    tree_r[v] = cnt++;
}

pii merge(pii a, pii b) { return pii(max(a.first, b.first), min(a.second, b.second)); }

pii build(int i, int l, int r) {
    lazy[i] = 0;
    if (l == r)
	return tree[i] = pii(salary[who[l]], salary[who[r]]);
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
    return tree[i] = merge(build(L, l, mid), build(R, mid + 1, r));
}

void refresh(int i, int l, int r) {
    tree[i].first += lazy[i];
    tree[i].second += lazy[i];
    if (l != r) {
	int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
	lazy[L] += lazy[i];
	lazy[R] += lazy[i];
    }
    lazy[i] = 0;
}

pii update(int i, int l, int r, int ql, int qr, int x) {
    refresh(i, l, r);
    if (l > qr || ql > r) return tree[i];
    if (ql <= l && r <= qr) {
	lazy[i] += x;
	refresh(i, l, r);
	return tree[i];
    }
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
    return tree[i] = merge(update(L, l, mid, ql, qr, x),
			   update(R, mid + 1, r, ql, qr, x));
}

pii query(int i, int l, int r, int ql, int qr) {
    refresh(i, l, r);
    if (l > qr || ql > r) return pii(0, INF);
    if (ql <= l && r <= qr) return tree[i];
    int L = 2*i + 1, R = 2*i + 2, mid = (l + r) / 2;
    return merge(query(L, l, mid, ql, qr), query(R, mid + 1, r, ql, qr));
}    

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	    subs[i].clear();
	
	for (int k = 2; k <= n; k++) {
	    int sup;
	    scanf("%d", &sup);
	    subs[sup].push_back(k);
	}
	for (int k = 1; k <= n; k++)
	    scanf("%d", &salary[k]);

	cnt = 0;
	dfs(1);

	build(0, 0, n - 1);
	int q;
	for (scanf("%d", &q); q--;) {
	    char op;
	    scanf(" %c", &op);
	    if (op == 'R') {
		int i, x;
		scanf("%d%d", &i, &x);
		update(0, 0, n - 1, tree_l[i], tree_r[i], x);
	    }
	    else {
		int i;
		scanf("%d", &i);
		pii got = query(0, 0, n - 1, tree_l[i], tree_r[i]);
		printf("%d\n", got.first - got.second);
	    }
	}
    }	
    return 0;
}
   
