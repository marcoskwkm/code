#include <bits/stdc++.h>
using namespace std;

typedef long long lint;
typedef pair<int ,int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const int MAXM = 110;

bool seen[2 * MAXM];
double a, b, c, d, r;
double alpha[2 * MAXM], beta[2 * MAXM];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
	int n, m;
	cin >> n >> m >> a >> b >> c >> d >> r;
	memset(seen, 0, sizeof(seen));
	vector<int> path;
	alpha[n + MAXM] = 0;
	beta[n + MAXM] = 1;
	while (1) {
	    seen[n + MAXM] = 1;
	    int nxt;
	    double aa, bb;
	    if (n <= 0) {
		nxt = -m - 2*n;
		aa = a / r;
		bb = b/r + double(n*n)/(m*m);
	    }
	    else {
		nxt = m - 2*n;
		aa = c / r;
		bb = d/r + double(n*n)/(m*m);
	    }
	    if (seen[nxt + MAXM]) {
		double a1 = alpha[n + MAXM] + beta[n + MAXM]*aa;
		double b1 = bb*beta[n + MAXM];
		double a2 = alpha[nxt + MAXM];
		double b2 = beta[nxt + MAXM];
		double x = (a2 - a1) / (b1 - b2);
		printf("%.9f\n", a2 + b2*x);
		break;
	    }
	    alpha[nxt + MAXM] = alpha[n + MAXM] + beta[n + MAXM]*aa;
	    beta[nxt + MAXM] = bb*beta[n + MAXM];
	    n = nxt;
	}
    }	
    return 0;
}
   
