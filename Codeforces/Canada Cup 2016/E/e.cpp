#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

map<int, int> mp;
vector<pii> coins;
int next_idx[MAXN];

bool test(int sum, int k) {
    // printf("test %d %d\n", sum, k);
    int last = INF;
    while (sum > 0) {
        if (k > sum) k = 0;
        pii p(k, 1);
        int id = min(last, next_idx[sum]);
        // printf("sum = %d, id = %d\n", sum, id);
        if (id >= 0) {
            // printf("cur coin: %d, k = %d\n", coins[id].first, k);
            if (coins[id].first > k) {
                p = coins[id];
                last = id - 1;
            }
            else if (coins[id].first == k) {
                p.second += coins[id].second;
                last = id - 1;
                k = 0;
            }
            else k = 0;
        }        
        // printf("%d %d %d\n", sum, p.first, last);
        if (p.first == 0) return 1;        
        int take = min(sum / p.first, p.second);
        sum -= p.first * take;
    }
    return 0;
}

int main() {
    int sum;
    scanf("%d", &sum);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int coin;
        scanf("%d", &coin);
        mp[coin]++;
    }

    for (pii p: mp) {
        coins.push_back(p);
        // printf("coin: %d %d\n", p.first, p.second);
    }
    
    for (int c = 1; c <= sum; c++) {
        int id = lower_bound(coins.rbegin(), coins.rend(), pii(c, INF), greater<pii>()) - coins.rbegin();
        next_idx[c] = coins.size() - id - 1;
    }
    
    for (int ans = 1; ans < sum; ans++) {
        if (test(sum, ans)) {
            printf("%d\n", ans);
            return 0;
        }
    }
    printf("Greed is good\n");            
    return 0;
}
