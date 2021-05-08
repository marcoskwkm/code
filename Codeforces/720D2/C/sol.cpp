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

template<class T = int> inline T read() {
    T x;
    cin >> x;
    return x;
}

template<class T, class C = vector<T>> inline void printArray(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? '\n' : ' ');
    }
}

int getMax(int i, int j, int n) {
    printf("? 1 %d %d %d\n", i + 1, j + 1, n - 1);
    fflush(stdout);
    int resp = read();
    if (resp == -1)
        exit(0);
    if (resp == n - 1) {
        printf("? 1 %d %d %d\n", j + 1, i + 1, n - 1);
        fflush(stdout);
        int resp2 = read();
        if (resp2 == -1)
            exit(0);
        return resp2;
    }
    return resp;
}

int getMin(int i, int j, int n) {
    printf("? 2 %d %d %d\n", i + 1, j + 1, 1);
    fflush(stdout);
    int resp = read();
    if (resp == -1)
        exit(0);
    if (resp == 2) {
        printf("? 2 %d %d %d\n", j + 1, i + 1, 1);
        fflush(stdout);
        int resp2 = read();
        if (resp2 == -1)
            exit(0);
        return resp2;
    }
    return resp;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int t = read(); t--;) {
        int n;
        cin >> n;
        vector<int> v(n);

        auto solve3 = [&](int i) {
            int max_l = getMax(i, i + 1, n);
            int max_r = getMax(i + 1, i + 2, n);

            if (max_l < max_r) {
                v[i + 2] = max_r;
                int min_r = getMin(i + 1, i + 2, n);
                v[i + 1] = min_r;
                if (min_r != max_l) {
                    v[i] = max_l;
                } else {
                    int min_l = getMin(i, i + 1, n);
                    v[i] = min_l;
                }
            } else if (max_l == max_r) {
                v[i + 1] = max_l;
                v[i] = getMin(i, i + 1, n);
                v[i + 2] = getMin(i + 1, i + 2, n);
            } else {
                v[i] = max_l;
                int min_l = getMin(i, i + 1, n);
                v[i + 1] = min_l;
                if (min_l != max_r) {
                    v[i + 2] = max_r;
                } else {
                    int min_r = getMin(i + 1, i + 2, n);
                    v[i + 2] = min_r;
                }
            }
        };

        for (int i = 0; i + 2 < n; i += 3) {
            solve3(i);
        }

        if (n % 3)
            solve3(n - 3);

        printf("!");
        for (int x : v)
            printf(" %d", x);
        printf("\n");
        fflush(stdout);
    }
    return 0;
}
