#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int N = 100, Q = 10000;

int question[N][Q];
lint difficulty[Q];

int main() {
    int t = 1, T;

    scanf("%d%*d", &T);
    for (; t <= T; t++) {
        memset(difficulty, 0, sizeof(difficulty));
        for (int i = 0; i < N; i++) {
            for (int q = 0; q < Q; q++) {
                char c;
                scanf(" %c", &c);
                question[i][q] = (c == '1');
                difficulty[q] += 1 - question[i][q];
            }
        }

        lint cheater = -1;
        double factor = 100;
        for (int i = 0; i < N; i++) {
            double diff_right = 0, diff_wrong = 0;
            int cnt_right = 0, cnt_wrong = 0;
            for (int q = 0; q < Q; q++) {
                if (question[i][q]) {
                    diff_right += difficulty[q];
                    cnt_right++;
                } else {
                    diff_wrong += difficulty[q];
                    cnt_wrong++;
                }
            }

            double cur_factor = diff_wrong / cnt_wrong - diff_right / cnt_right;

            if (cur_factor < factor) {
                factor = cur_factor;
                cheater = i;
            }
            // printf("%3d: %12lf\n", i + 1, cur_factor);
        }

        printf("Case #%d: %lld\n", t, cheater + 1);
    }
    return 0;
}
