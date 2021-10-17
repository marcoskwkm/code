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
        int n;
        cin >> n;
        vector<string> grid;
        for (int r = 0; r < n; r++) {
            string row;
            cin >> row;
            grid.push_back(row);
        }

        int ans = INF;
        set<set<pii>> sets;
        for (int r = 0; r < n; r++) {
            int cntX = 0, cntO = 0;
            set<pii> blanks;
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == 'X')
                    cntX++;
                else if (grid[r][c] == 'O')
                    cntO++;
                else
                    blanks.insert(pii(r, c));
            }
            if (cntO)
                continue;
            if ((int)blanks.size() < ans) {
                ans = blanks.size();
                sets.clear();
                sets.insert(blanks);
            } else if ((int)blanks.size() == ans) {
                sets.insert(blanks);
            }
        }

        for (int c = 0; c < n; c++) {
            int cntX = 0, cntO = 0;
            set<pii> blanks;
            for (int r = 0; r < n; r++) {
                if (grid[r][c] == 'X')
                    cntX++;
                else if (grid[r][c] == 'O')
                    cntO++;
                else
                    blanks.insert(pii(r, c));
            }
            if (cntO)
                continue;
            if ((int)blanks.size() < ans) {
                ans = blanks.size();
                sets.clear();
                sets.insert(blanks);
            } else if ((int)blanks.size() == ans) {
                sets.insert(blanks);
            }
        }

        if (ans == INF) {
            printf("Case #%d: Impossible\n", t);
        } else {
            printf("Case #%d: %d %d\n", t, ans, (int)sets.size());
        }
    }

    return 0;
}
