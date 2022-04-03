#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readArray(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int THRESHOLD = 316;

void read(int &v) {
    scanf("%d", &v);
    if (v == -1) {
        abort();
    }
}

int rooms[MAXN];
bool seen[MAXN];

int main() {
    srand(42069);
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        int N, K;
        read(N);
        read(K);

        memset(seen, 0, sizeof(seen));
        int room, degree;
        long double deg_sum = 0, w_sum = 0;
        int cnt = 0;

        for (int r = 0; r < N; r++) {
            rooms[r] = r;
        }
        random_shuffle(rooms, rooms + N - 1);

        int at = 0;
        for (int i = 0; i < K + 1 && at < N; i++) {
            read(room);
            read(degree);

            if (!seen[room - 1]) {
                seen[room - 1] = 1;
                long double w = (long double)(1) / pow(degree, 0.33);
                deg_sum += degree * w;
                w_sum += w;
                cnt++;
            }

            if (i == K) {
                break;
            }

            if (i % 10 == 9) {
                while (at < N - 1 && seen[rooms[at]]) {
                    at++;
                }

                if (at == N - 1) {
                    break;
                }

                printf("T %d\n", rooms[at++] + 1);
            } else {
                printf("W\n");
            }

            fflush(stdout);
        }

        long double expected_degree = deg_sum / w_sum;
        printf("E %.0Lf\n", round(expected_degree * N / 2));
        fflush(stdout);
    }

    return 0;
}
