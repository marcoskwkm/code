#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// Supports *find_by_order() and order_of_key()
template<class T> using OrderedSet = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

int v[MAXN];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    OrderedSet<pii> s;
    int ans = 0;
    for (int i = 0; i < k; i++) {        
        scanf("%d", &v[i]);
        s.insert(pii(v[i], i));
    }
    ans = s.find_by_order(k / 2)->first;
    for (int i = k; i < n; i++) {
        s.erase(pii(v[i - k], i - k));
        scanf("%d", &v[i]);
        s.insert(pii(v[i], i));
        ans = max(ans, s.find_by_order(k / 2)->first);
    }
    printf("%d\n", ans);        
    return 0;
}
