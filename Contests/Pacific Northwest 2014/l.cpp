#include <bits/stdc++.h>
using namespace std;

#define sq(x) ((x)*(x))

typedef long long lint;
typedef pair<int ,int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const int MAXN = 100;

lint x[MAXN], y[MAXN], z[MAXN];
pair<int, int> wh[MAXN];
long double d[MAXN][MAXN];

double dist(int u, int v) {
    return sqrt(sq(x[u] - x[v]) + sq(y[u] - y[v]) + sq(z[u] - z[v]));
}

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
	printf("Case %d:\n", t);
	int n;
	scanf("%d", &n);
	map<string, int> idx;
	for (int i = 0; i < n; i++) {
	    string name;
	    cin >> name >> x[i] >> y[i] >> z[i];
	    idx[name] = i;
	}
	for (int i = 0; i < n; i++)
	    for (int j = 0; j < n; j++)
		d[i][j] = dist(i, j);
	int w;
	scanf("%d", &w);
	for (int i = 0; i < w; i++) {
	    string from, to;
	    cin >> from >> to;
	    d[idx[from]][idx[to]] = 0;
	}
	for (int k = 0; k < n; k++)
	    for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
	    string from, to;
	    cin >> from >> to;
	    int u = idx[from], v = idx[to];
	    printf("The distance from %s to %s is %lld parsecs.\n",
		   from.c_str(), to.c_str(), lint(d[u][v] + 0.5));
	}
    }	
    return 0;
}
   
