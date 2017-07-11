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
    int l, r;
    cin >> n >> l >> r;
    if (n < 10) {
        lint x = 1;
        for (int i = 1; i < n; i++)
            x = 10*x + 1;
        x *= x;
        vector<int> ans;
        while (x) {
            ans.push_back(x % 10);
            x /= 10;
        }
        reverse(ans.begin(), ans.end());
        for (int i = l; i <= r; i++)
            printf("%d", ans[i - 1]);
        printf("\n");
        return 0;
    }
    n--;
    lint q = n / 9;
    lint l_rep_l = 0, l_rep_r = 9 * q - 1;
    vector<int> mid;
    int rem = n % 9;
    if (rem > 0) {
        for (int i = 1; i <= rem + 1; i++)
            mid.push_back(i);
        for (int i = rem; i >= 2; i--)
            mid.push_back(i);
    }
    lint r_rep_l = l_rep_r + mid.size() + 1;
    lint r_rep_r = r_rep_l + 9 * q - 1;

    // printf("[%lld, %lld] (%d) [%lld, %lld]\n",
    //        l_rep_l, l_rep_r, (int)mid.size(), r_rep_l, r_rep_r);

    for (int i = l - 1; i <= r - 1; i++) {
        if (i <= l_rep_r) {
            printf("%c", "123456790"[i % 9]);
        }
        else if (i < r_rep_l) {
            printf("%d", mid[i - l_rep_r - 1]);
        }
        else if (i <= r_rep_r) {
            printf("%c", "098765432"[(i - r_rep_l) % 9]);
        }
        else printf("1");
    }
    printf("\n");
    return 0;
}
