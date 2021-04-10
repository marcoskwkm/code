#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

void solve() {
    int n;
    cin >> n;
    vector<string> v;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        v.push_back(s);
    }

    int ans = 0;
    for (int i = 1; i < n; i++) {
        if (v[i - 1].size() < v[i].size()) {
            continue;
        }

        bool is_greater = 0;
        bool is_equal = 1;
        for (size_t j = 0; j < v[i].size(); j++) {
            if (v[i - 1][j] != v[i][j]) {
                is_equal = 0;
                if (v[i - 1][j] < v[i][j]) {
                    is_greater = 1;
                }
                break;
            }
        }

        if (is_equal) {
            bool is_all_9 = 1;
            for (size_t j = v[i].size(); j < v[i - 1].size(); j++) {
                if (v[i - 1][j] != '9') {
                    is_all_9 = 0;
                }
            }

            if (is_all_9) {
                while (v[i].size() <= v[i - 1].size()) {
                    v[i] += '0';
                    ans++;
                }
            } else {
                ans += v[i - 1].size() - v[i].size();
                v[i] = v[i - 1];
                v[i].back()++;
                for (size_t j = v[i].size() - 1; j > 0; --j) {
                    if (v[i][j] > '9') {
                        v[i][j] = '0';
                        v[i][j - 1]++;
                    } else {
                        break;
                    }
                }
            }
        } else {
            if (is_greater) {
                while (v[i].size() < v[i - 1].size()) {
                    v[i] += '0';
                    ans++;
                }
            } else {
                while (v[i].size() <= v[i - 1].size()) {
                    v[i] += '0';
                    ans++;
                }
            }
        }
    }
    printf(" %d\n", ans);
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d:", t);
        solve();
    }
    return 0;
}
