#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readArray(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;
typedef pair<pii, string> pps;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    map<string, pii> f;
    string foo;
    getline(cin, foo);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            string s;
            getline(cin, s);
            auto it = f.find(s);
            if (it == f.end()) {
                f[s] = pii(1, (3 * i + j));
            } else {
                it->second.first++;
                it->second.second = 3 * i + j;
            }
        }
    }

    vector<pps> v;
    for (auto x: f) {
        v.push_back(pps(x.second, x.first));
    }

    sort(v.begin(), v.end(), greater<pps>());

    for (int i = 0; i < min<int>(k, v.size()); i++) {
        printf("%s\n", v[i].second.c_str());
    }

    return 0;
}
