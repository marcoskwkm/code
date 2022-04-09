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
const int MAXB = 1000000000;

template<class Fun> class y_combinator_result {
    Fun fun_;

  public:
    template<class T> explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}

    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return fun_(ref(*this), forward<Args>(args)...);
    }
};

template<class Fun> decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
}

template<class T = int> inline T read() {
    T x;
    cin >> x;
    return x;
}

template<class T, class C = vector<T>> inline void printArray(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? "" : " ");
    }
    cout << '\n';
}

void read(int &x) {
    cin >> x;
    if (x == -1) {
        exit(-1);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, T;
    for (read(T); t <= T; t++) {
        int N;
        cin >> N;
        set<int, greater<int>> s;
        lint sum = 0;

        for (int i = 0; i < 30; i++) {
            s.insert(1 << i);
        }
        for (int i = 0; i < 70; i++) {
            s.insert(MAXB - i);
        }

        for (int x: s) {
            printf("%d ", x);
            sum += x;
        }
        printf("\n");
        fflush(stdout);

        for (int i = 0; i < N; i++) {
            int x;
            read(x);
            s.insert(x);
            sum += x;
        }

        sum /= 2;

        set<int> ans;
        for (auto it = s.begin(); it != s.end(); it++) {
            if (*it <= sum) {
                sum -= *it;
                ans.insert(*it);
            }
        }

        for (int x: ans) {
            printf("%d ", x);
        }
        printf("\n");
        fflush(stdout);
    }
    return 0;
}
