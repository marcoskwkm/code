#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int T = 50, N = 100, M = 10000;

double S[N], Q[M];

int main() {
    uniform_real_distribution<double> unif(-3, 3);
    uniform_real_distribution<double> roll(0, 1);
    default_random_engine re;
    re.seed(time(0));
    srand(time(0));
    FILE *ans = fopen("gen.out", "w");

    printf("%d\n86\n", T);

    for (int t = 1; t <= T; t++) {
        int cheater = rand() % N;
        fprintf(ans, "Case #%d: %d\n", t, cheater + 1);

        for (int i = 0; i < N; i++)
            S[i] = unif(re);
        for (int i = 0; i < M; i++)
            Q[i] = unif(re);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (cheater == i && roll(re) < 0.5) {
                    printf("1");
                } else {
                    double p = double(1) / (1 + exp(-S[i] - Q[j]));
                    if (roll(re) < p) {
                        printf("1");
                    } else {
                        printf("0");
                    }
                }
            }
            printf("\n");
        }
    }
    return 0;
}
