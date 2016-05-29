#include <message.h>
#include "sandwich.h"
#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    if (MyNodeId() != 0) return 0;
    lint ans = 0, cur = 0, total = 0;
    for (int i = 0; i < GetN(); i++) {
        cur += GetTaste(i);
        total += GetTaste(i);
        ans = min(ans, cur);
        cur = min(cur, 0ll);
    }
    printf("%lld\n", total - ans);
    return 0;
}
