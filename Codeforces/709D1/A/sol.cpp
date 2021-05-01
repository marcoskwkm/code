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

template <class T, class C = vector<T>> inline void printArray(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? '\n' : ' ');
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    for (cin >> t; t--;) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> days(m);
        map<int, int> freq;
        for (int i = 0; i < m; i++) {
            int q;
            cin >> q;
            vector<int> day(q);
            readArray(day, q);
            freq[day[0]]++;
            days[i] = day;
        }

        int most_freq = -1, f = -1;
        for (auto x : freq) {
            if (x.second > f) {
                f = x.second;
                most_freq = x.first;
            }
        }

        if (f > (m + 1) / 2) {
            for (auto &day : days) {
                if (f > (m + 1) / 2 && day.size() > 1 && day[0] == most_freq) {
                    swap(day[0], day[1]);
                    f--;
                }
            }
        }

        if (f > (m + 1) / 2) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for (int i = 0; i < m; i++)
                cout << days[i][0] << ' ';
            cout << '\n';
        }
    }
    return 0;
}
