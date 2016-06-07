#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const double PI = 3.14159265358979, E = 2.71828182845905;
const int MAXN = 100;
const double EPS = 1e-9;

string name[MAXN];
double A[MAXN], C[MAXN], P[MAXN];
double IMAD[MAXN];
int idx[MAXN];

double choose(int n, int k) {
    k = min(k, n - k);
    if (k < 0) return 0;
    double ret = 1;
    for (int i = 0; i < k; i++)
        ret *= double(n - i) / (i + 1);
    return ret;
}

void get_imad(int i) {
    int T = name[i].size();
    int nv = 0, nc = 0;
    for (char c: name[i]) {
        c = tolower(c);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            nv++;
        else
            nc++;
    }
    double f1 = 0;
    for (int k = 1; k <= T; k++)
        f1 += pow(P[i], 1./k) * cos(k * PI);

    f1 = fabs(f1);
    double f2 = choose(max(nv, nc) + 1, min(nv, nc) - 1);
    double f3 = ceil(sqrt(pow(nv, E) + pow(nc, E))) / floor(PI + log(1 + A[i]*C[i]));
    IMAD[i] = f1 * f2 * f3;
}    

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cin >> name[i] >> A[i] >> C[i] >> P[i];
        get_imad(i);
        idx[i] = i;
    }
    sort(idx, idx + n, [](int a, int b) {
        if (fabs(IMAD[a] - IMAD[b]) < EPS) return name[a] < name[b];
        return IMAD[a] < IMAD[b];
    });
    char buff[100];
//    printf("%.2f\n%.2f\n", IMAD[0], IMAD[1]);
    for (int i = 0; i < n; i++) {
        printf("%s", name[idx[i]].c_str());
        sprintf(buff, "%.0f", fabs(IMAD[idx[i]]));
        int len = strlen(buff);
        for (int j = 0; j < len; j++) printf("!");
        printf("\n");
    }        
    return 0;
}
