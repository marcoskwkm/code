#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n;
    cin >> n;
    map<int, vector<string>> names;
    for (int i = 0; i < n; i++) {
        string name;
        int h;
        cin >> name >> h;
        names[h].push_back(name);
    }
    int cur = 1;
    for (auto f: names) {
        sort(f.second.begin(), f.second.end());
        for (string s: f.second) printf("%s ", s.c_str());
        printf("%d %d\n", cur, cur + f.second.size() - 1);
        cur += f.second.size();
    }
    return 0;
}
