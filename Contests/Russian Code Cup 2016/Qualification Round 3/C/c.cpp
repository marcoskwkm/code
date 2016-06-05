#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n, k;
        scanf("%d%d", &n, &k);
        int start_x = 1000, start_y = 1500;
        int cur = 0;
        vector<pii> ans;
        int x = start_x, y = start_y;
        int big_x = 3000;
        int low_x = start_x, low_y = start_y, hi_y = start_y;
        while (n) {
            x = big_x;
            ans.push_back(pii(x, y));
            n--;
            big_x--;
            
            if (cur > k) {
                y -= 1 + 2 * k;
                k = 0;
            }
            else {
                y = low_y - 2;
                k -= cur;
            }
            ans.push_back(pii(x, y));
            n--;
            if (k == 0) break;
            cur++;            
            low_y -= 2;
            
            x = low_x + 1;
            low_x++;
            ans.push_back(pii(x, y));
            n--;

            if (cur > k) {
                y += 1 + 2 * k;
                k = 0;
            }
            else {
                y = hi_y + 2;
                k -= cur;
            }
            ans.push_back(pii(x, y));
            n--;
            if (k == 0) break;
            cur++;
            hi_y += 2;
        }
        if (n) {
            vector<pii> head;
            low_x = 1, low_y = 1, hi_y = start_y - 1;
            int hi_x = start_x - 1;
            x = start_x, y = start_y;
            n++;
            while (n) {
                x = low_x++;
                head.push_back(pii(x, y));
                if (--n == 0) break;

                y = low_y++;
                head.push_back(pii(x, y));
                if (--n == 0) break;

                x = hi_x--;
                head.push_back(pii(x, y));
                if (--n == 0) break;

                y = hi_y--;
                head.push_back(pii(x, y));
                if (--n == 0) break;
            }
            reverse(head.begin(), head.end());
            for (pii p: head) printf("%d %d\n", p.first, p.second);
        }
        else printf("%d %d\n", start_x, start_y);
        for (pii p: ans) printf("%d %d\n", p.first, p.second);
    }        
    return 0;
}
