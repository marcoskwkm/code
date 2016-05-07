#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10, MAXK = 55;

double dp[2][MAXN];
double t[MAXN];
double E[MAXN], St[MAXN], Sinv[MAXN];

struct Line {
    double a, b;
    double left_x;
    double get(double x) { return a + b*x; }
    Line(){}
    Line(double a, double b) : a(a), b(b), left_x(-LINF) {}
};

Line deq[MAXN];
int deq_l, deq_r;

double get_x(Line r, Line s) {
    return double(s.a - r.a) / (r.b - s.b);
}

// a + bx
void add_line(double a, double b) {
    Line newline(a, b);
    while (deq_r > deq_l && get_x(newline, deq[deq_r - 1]) < deq[deq_r - 1].left_x) deq_r--;
    if (deq_r > deq_l) newline.left_x = get_x(newline, deq[deq_r - 1]);
    deq[deq_r++] = newline;
}

double get(double x) {
    if (deq_l >= deq_r) return -LINF;
    while (deq_l + 1 < deq_r && deq[deq_l + 1].left_x <= x) {
        deq_l++;
    }
    return deq[deq_l].get(x);
}    

int main() {
    int N, K;
    scanf("%d%d", &N, &K);
    for (int i = 1; i <= N; i++) {
        scanf("%lf", &t[i]);
        St[i] = St[i - 1] + t[i];
        Sinv[i] = Sinv[i - 1] + 1./t[i];
        E[i] = E[i - 1] + St[i]/t[i];
    }
    for (int i = 0; i < 2; i++)
        for (int j = 0; j <= N; j++)
            dp[i][j] = LINF;
    dp[0][0] = 0;
    int cur = 1, prv = 0;
    for (int k = 1; k <= K; k++) {
        deq_l = deq_r = 0;
        if (k == 1) add_line(0, 0);
        for (int n = 1; n <= N; n++) {
            dp[cur][n] = E[n] - get(Sinv[n]);
            add_line(E[n] - St[n]*Sinv[n] - dp[prv][n], St[n]);
        }
        cur ^= 1;
        prv ^= 1;
    }
    printf("%.12f\n", dp[prv][N]);    
    return 0;
}
