#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXL = 210;

string s;
size_t pos;

int dp_set[MAXL][MAXL], dp_list[MAXL][MAXL], dp_elem[MAXL][MAXL];

bool is_list(int, int);
bool is_element(int, int);

bool is_set(int l, int r) {
    if (l > r) return 0;
    if (dp_set[l][r] != -1) return dp_set[l][r];
    if (s[l] != '{' || s[r] != '}') return dp_set[l][r] = 0;
    if (r - l == 1) return dp_set[l][r] = 1;
    return dp_list[l][r] = is_list(l + 1, r - 1);
}

bool is_list(int l, int r) {
    if (l > r) return 0;
    if (dp_list[l][r] != -1) return dp_list[l][r];
    if (is_element(l, r)) return dp_list[l][r] = 1;
    for (int i = l; i <= r; i++) {
        if (s[i] != ',') continue;
        if (is_element(l, i - 1) && is_list(i + 1, r))
            return dp_list[l][r] = 1;
    }
    return dp_list[l][r] = 0;
}

bool is_element(int l, int r) {
    if (l > r) return 0;
    if (l == r) return 1;
    if (dp_elem[l][r] != -1) return dp_elem[l][r];
    return dp_elem[l][r] = is_set(l, r);
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        cin >> s;
        printf("Word #%d: ", t);
        memset(dp_set, -1, sizeof(dp_set));
        memset(dp_list, -1, sizeof(dp_list));
        memset(dp_elem, -1, sizeof(dp_elem));
        printf("%sSet\n", is_set(0, s.size() - 1) ? "" : "No ");
    }
    return 0;
}
