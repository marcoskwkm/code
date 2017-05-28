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

template<class T> struct DynamicMedian {
    multiset<T> upper;
    multiset<T, greater<T>> lower;

    void insert(T x) {
        if (upper.empty() || x >= *upper.begin()) {
            upper.insert(x);
            if (upper.size() > lower.size() + 1) {
                lower.insert(*upper.begin());
                upper.erase(upper.begin());
            }
        }
        else {
            lower.insert(x);
            if (lower.size() > upper.size()) {
                upper.insert(*lower.begin());
                lower.erase(lower.begin());
            }
        }
    }

    void erase(T x) {
        if (upper.find(x) != upper.end()) {
            upper.erase(upper.find(x));
            if (lower.size() > upper.size()) {
                upper.insert(*lower.begin());
                lower.erase(lower.begin());
            }
        }
        else if (lower.find(x) != lower.end()) {
            lower.erase(lower.find(x));
            if (lower.size() + 1 < upper.size()) {
                lower.insert(*upper.begin());
                upper.erase(upper.begin());
            }
        }
    }

    T get_median() {
        return *upper.begin();
    }
};

int v[MAXN];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    DynamicMedian<int> median;
    int ans = 0;
    for (int i = 0; i < k; i++) {        
        scanf("%d", &v[i]);
        median.insert(v[i]);
    }
    ans = median.get_median();
    for (int i = k; i < n; i++) {
        median.erase(v[i - k]);
        scanf("%d", &v[i]);
        median.insert(v[i]);
        ans = max(ans, median.get_median());
    }
    printf("%d\n", ans);        
    return 0;
}
