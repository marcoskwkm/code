#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)5e4 + 10, MAXK = 20;

int best_all[MAXK], worst_win[MAXK];
int skill[MAXN][MAXK];

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++)
            scanf("%d", &skill[i][j]);
    for (int j = 0; j < k; j++)
        best_all[j] = worst_win[j] = skill[0][j];    
    
    int n_win = 1;
    printf("%d\n", n_win);
    for (int i = 1; i < n; i++) {
        bool enters = 0;
        bool pwns = 1;
        for (int j = 0; j < k; j++) {
            if (best_all[j] > skill[i][j]) pwns = 0;
            if (worst_win[j] < skill[i][j]) enters = 1;
        }
        // debug("%d %d\n", enters, pwns);
        if (enters) {
            if (pwns) n_win = 1;
            else n_win++;
            for (int j = 0; j < k; j++)
                worst_win[j] = min(worst_win[j], skill[i][j]);
        }
        for (int j = 0; j < k; j++)
            best_all[j] = max(best_all[j], skill[i][j]);
        printf("%d\n", n_win);
    }   
    return 0;
}
