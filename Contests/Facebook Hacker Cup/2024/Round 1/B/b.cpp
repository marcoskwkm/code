#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define read_array(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e7 + 10;

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

template<class T> inline vector<T> read_vector(int n) {
    vector<T> v(n);
    read_array(v, n);
    return v;
}

template<class T> vector<T> make_vector(size_t size, T initialValue) {
    return vector<T>(size, initialValue);
}

template<class T, class... Args> auto make_vector(size_t head, Args &&...rem) {
    auto inner = make_vector<T>(rem...);
    return vector<decltype(inner)>(head, inner);
}

template<class T, class C = vector<T>> inline void print_array(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? "" : " ");
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<bool> sieve(MAXN);
    sieve[0] = sieve[1] = 1;    
    vector<lint> primes;
    for (lint n = 2; n <= MAXN; n++) {
        if (!sieve[n]) {
            primes.push_back(n);
            for (lint m = n * n; m <= MAXN; m += n) {
                sieve[m] = 1;
            }
        }
    }

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int N;
        cin >> N;

        set<lint> sols;
        for (int i = 1; i < (int)primes.size() && primes[i] <= N; i++) {
            if (!sieve[primes[i] - 2]) {
                sols.insert(primes[i] - 2);
            }
            if (primes[i] - primes[i - 1] == 2) {
                sols.insert(2);
            }
        }

        printf("Case #%d: %d\n", t, (int)sols.size());
    }

    return 0;
}
