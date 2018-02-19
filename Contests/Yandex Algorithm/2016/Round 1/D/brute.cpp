#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, w, p;
    scanf("%d%d%d", &m, &w, &p);
    vector<int> v;
    for (int i = 0; i < p; i++) {
        v.push_back(2*i);
        v.push_back(2*i + 1);
    }
    int cur = p;
    for (int i = 0; i < m - p; i++)
        v.push_back(2*cur++);
    for (int i = 0; i < w - p; i++)
        v.push_back(2*cur++ + 1);
    int ans = 0;
    do {
        bool ok = 1;
        int last = v[0];
        for (int i = 0; i + 1 < (int)v.size(); i++) {
            if (v[i] % 2 == v[i + 1] % 2) continue;
            if ((v[i] ^ 1) != v[i + 1]) {
                ok = 0;
                break;
            }
        }
        if (ok) ans++;
    } while (next_permutation(v.begin(), v.end()));
    printf("%d\n", ans);
    return 0;
}
