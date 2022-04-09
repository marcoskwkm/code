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

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        string s;
        cin >> s;
        vector<char> nxt(s.size() + 1);
        nxt[s.size()] = 'A' - 1;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (i == s.size() - 1 || s[i + 1] == s[i]) {
                nxt[i] = nxt[i + 1];
            } else {
                nxt[i] = s[i + 1];
            }
        }

        printf("Case #%d: ", t);
        for (size_t i = 0; i < s.size(); i++) {
            printf("%c", s[i]);
            if (nxt[i] > s[i]) {
                printf("%c", s[i]);
            }
        }
        printf("\n");
    }
    return 0;
}
