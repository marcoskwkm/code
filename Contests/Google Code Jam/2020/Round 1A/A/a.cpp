#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 55;

string pat[MAXN];
int firstAsterisk[MAXN], lastAsterisk[MAXN];

void proc(int idx) {
    firstAsterisk[idx] = -1;
    for (size_t i = 0; i < pat[idx].size(); i++) {
        if (pat[idx][i] == '*') {
            if (firstAsterisk[idx] == -1) firstAsterisk[idx] = i;
            lastAsterisk[idx] = i;
        }
    }
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d: ", t);

        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> pat[i];
            proc(i);
        }

        bool ok = 1;

        string largestPref = "", largestSuff = "";
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                string prefA = pat[i].substr(0, firstAsterisk[i]);
                string prefB = pat[j].substr(0, firstAsterisk[j]);
                if (prefA.size() > prefB.size()) swap(prefA, prefB);
                if (prefA != prefB.substr(0, prefA.size())) {
                    ok = 0;
                    break;
                }

                string suffA = pat[i].substr(lastAsterisk[i] + 1, string::npos);
                string suffB = pat[j].substr(lastAsterisk[j] + 1, string::npos);
                if (suffA.size() > suffB.size()) swap(suffA, suffB);
                if (suffA != suffB.substr(suffB.size() - suffA.size(), string::npos)) {
                    ok = 0;
                    break;
                }

                if (prefB.size() > largestPref.size()) largestPref = prefB;
                if (suffB.size() > largestSuff.size()) largestSuff = suffB;
            }
        }

        if (!ok) {
            printf("*\n");
            continue;
        }

        string sol = largestPref;
        for (int i = 0; i < n; i++) {
            for (int j = firstAsterisk[i] + 1; j < lastAsterisk[i]; j++) {
                if (pat[i][j] != '*') sol += pat[i][j];
            }
        }

        sol += largestSuff;
        printf("%s\n", sol.c_str());
    }
    return 0;
}
