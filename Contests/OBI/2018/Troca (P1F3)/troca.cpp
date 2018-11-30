#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int card[2][MAXN];
bool swapped[MAXN];

int main() {
    int N, Q;
    cin >> N >> Q;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &card[i][j]);
    bool all_swapped = 0;
    for (int q = 0; q < Q; q++) {
        int l, r;
        scanf("%d%d", &l, &r);
        if (2 * (r - l + 1) > N) {
            all_swapped = !all_swapped;
            for (int i = 0; i < l - 1; i++)
                swapped[i] = !swapped[i];
            for (int i = r; i < N; i++)
                swapped[i] = !swapped[i];
        }
        else {
            for (int i = l - 1; i < r; i++)
                swapped[i] = !swapped[i];
        }
    }
    for (int i = 0; i < N; i++)
        printf("%d ", card[swapped[i] ^ all_swapped][i]);
    printf("\n");
    return 0;
}
