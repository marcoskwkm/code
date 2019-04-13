#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct Subproblem {
    int step, l, r;
    int size, broken, responseSize;
    
    Subproblem(int _step, int _l, int _r) : step(_step), l(_l), r(_r) {
        size = r - l + 1;
    }

    void setBroken(int n_broken) {
        broken = n_broken;
        responseSize = size - broken;
    }
};

int main() {
    int t;
    for (cin >> t; t--;) {
        int n, b, f;
        cin >> n >> b >> f;
        vector<Subproblem> subproblems;
        for (int i = 0; i < n; i += 16)
            subproblems.push_back(Subproblem(0, i, min(n, i + 16) - 1));        
        for (size_t i = 0; i < subproblems.size(); i++)
            for (int j = 0; j < subproblems[i].size; j++)
                printf("%lu", i & 1);
        printf("\n");
        fflush(stdout);

        string response;
        cin >> response;
        int at = 0;
        for (Subproblem &subproblem: subproblems) {
            int to = at + 1;
            while (to < n && response[to] == response[at])
                to++;
            subproblem.setBroken(subproblem.size - (to - at));
            at = to;
        }

        for (int step = 0; step < 4; step++) {
            string query;
            for (Subproblem &subproblem: subproblems) {
                int m = (subproblem.l + subproblem.r) / 2;
                for (int i = subproblem.l; i <= subproblem.r; i++)
                    query += (i <= m ? "0" : "1");                
            }
            cout << query << endl;
            fflush(stdout);

            vector<Subproblem> newSubproblems;
            cin >> response;
            int cur = 0;
            for (Subproblem &subproblem: subproblems) {
                string subResponse = response.substr(cur, subproblem.responseSize);
                cur += subproblem.responseSize;
                int q = count(subResponse.begin(), subResponse.end(), '0');
                int m = (subproblem.l + subproblem.r) / 2;
                Subproblem sub_l(step + 1, subproblem.l, m);
                sub_l.setBroken(sub_l.size - q);
                newSubproblems.push_back(sub_l);
                // debug("%d - %d (%d)\n", subproblem.l, m, sub_l.broken);
                if (m < subproblem.r) {
                    Subproblem sub_r(step + 1, m + 1, subproblem.r);
                    sub_r.setBroken(subproblem.broken - sub_l.broken);
                    newSubproblems.push_back(sub_r);
                    // debug("%d - %d (%d)\n", m + 1, subproblem.r, sub_r.broken);
                }
            }
            subproblems = newSubproblems;
        }

        for (Subproblem &subproblem: subproblems)
            if (subproblem.broken == 1)
                printf("%d ", subproblem.l);
        printf("\n");
        fflush(stdout);

        int verdict;
        cin >> verdict;
        if (verdict == -1) return 0;
    }
    
    return 0;
}
