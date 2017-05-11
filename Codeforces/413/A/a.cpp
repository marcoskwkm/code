#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int n, t, k, d;

int simul(multiset<int> s, int q) {
    int rem = n;
    int ret = 0;
    while (rem > 0) {
        int cur_t = 0;
        if (s.size() == q) {
            cur_t = *s.begin();
            s.erase(s.begin());
        }
        ret = max(ret, cur_t + t);
        s.insert(ret);
        rem -= k;
    }
    return ret;
}       

int main() {
    cin >> n >> t >> k >> d;
    multiset<int> s;
    int t1 = simul(s, 1);
    s.insert(d);
    int t2 = simul(s, 2);
    printf("%s\n", t1 <= t2 ? "NO" : "YES");    
    return 0;
}
