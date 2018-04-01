#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int accS[MAXN], accT[MAXN];
char S[MAXN], T[MAXN];

int trailing_as(char *s, int *acc, int i) {
    int l = 1, r = i;
    while (l < r) {
        int mid = (l + r) / 2;
        if (acc[i] - acc[mid - 1] == i - (mid - 1))
            r = mid;
        else
            l = mid + 1;
    }
    return i - l + 1;
}

int main() {
    scanf("%s", S + 1);
    scanf("%s", T + 1);
    int lenS = strlen(S + 1), lenT = strlen(T + 1);
    for (int i = 1; i <= lenS; i++)
        accS[i] = accS[i - 1] + (S[i] == 'A');
    for (int i = 1; i <= lenT; i++)
        accT[i] = accT[i - 1] + (T[i] == 'A');

    int q;
    for (cin >> q; q--;) {
        int ls, rs, lt, rt;
        scanf("%d%d%d%d", &ls, &rs, &lt, &rt);
        int len_s = rs - ls + 1, len_t = rt - lt + 1;
        int qas = accS[rs] - accS[ls - 1], qat = accT[rt] - accT[lt - 1];
        int qbs = len_s - qas, qbt = len_t - qat;
        int tas = 0, tat = 0;
        if (S[rs] == 'A')
            tas = min(trailing_as(S, accS, rs), len_s);
        if (T[rs] == 'A')
            tat = min(trailing_as(T, accT, rt), len_t);
        if (tas < tat) {
            printf("0");
            continue;
        }
        qas -= tat, qat -= tat;
        if (tas > tat && (tas - tat) % 3 > 0) {
            qas--, qbs += 2;
        }
        if ((qbs & 1) != (qbt & 1)) {
            printf("0");
            continue;
        }
        if (qbs <= qbt) printf("1");
        else printf("0");
    }
    printf("\n");    
    return 0;
}
