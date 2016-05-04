#include <bits/stdc++.h>
using namespace std;

vector<int> ans[110];

void go(vector<int> &v, set<int> &has, int i, int k, int cur) {
    if (i == k) {
        has.insert(cur);
        return;
    }
    go(v, has, i + 1, k, cur);
    go(v, has, i + 1, k, cur + v[i]);
    go(v, has, i + 1, k, cur - v[i]);
}

int main() {
    int k = 15;
    vector<int> v;
    for (int i = 1; i <= 100; i++)
        v.push_back(i);
    int needs = 100;
    while (needs) {
        random_shuffle(v.begin(), v.end());
        for (int i = 0; i < k; i++)
            fprintf(stderr, "%d ", v[i]);
        fprintf(stderr, "...");
        set<int> has;
        go(v, has, 0, k, 0);
        fprintf(stderr, "done\n");
        for (int n = 1; n <= 100; n++) {
            if (!ans[n].empty()) continue;
            if (has.find(n) != has.end()) {
                continue;
            }
            needs--;
            fprintf(stderr, "needs = %d\n", needs);
            for (int i = 0; i < k; i++)
                ans[n].push_back(v[i]);
        }
    }
    for (int n = 1; n <= 100; n++) {
        printf("%d ", n);
        for (int i = 0; i < k; i++) printf(" %d", ans[n][i]);
        printf("\n");
    }
    return 0;
}
