#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXS = (int)2e5 + 10;

int dp[MAXS];

int main() {
    int n;
    cin >> n;
    vector<int> v;
    int gcd = 0;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        v.push_back(x);
        gcd = __gcd(gcd, x);
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        v[i] /= gcd;
        sum += v[i];
    }

    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int s = sum; s - v[i] >= 0; s--) {
            if (dp[s - v[i]]) {
                dp[s] = 1;
            }
        }
    }

    if (sum % 2 || dp[sum / 2] == 0) {
        printf("0\n");
    } else {
        printf("1\n");
        for (int i = 0; i < n; i++) {
            if (v[i] % 2) {
                printf("%d\n", i + 1);
                break;
            }
        }
    }

    return 0;
}
