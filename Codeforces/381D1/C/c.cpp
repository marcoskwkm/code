#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;
typedef pair<int, pii> Hill;
typedef pair<pii, int> InvHill;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)3e5 + 10;

lint d[MAXN];

inline int sign(lint x) { return x > 0 ? 1 : x < 0 ? -1 : 0; }

int n;
set<Hill> hills;
set<InvHill> invhills;

pii get(int pos) {
    if (pos < 1 || pos > n) return pii(pos, pos);
    debug("get %d\n", pos);
    pii p = prev(invhills.lower_bound(InvHill(pii(pos, INF), INF)))->first;
    debug("[%d, %d]\n", p.first, p.second);
    return prev(invhills.lower_bound(InvHill(pii(pos, INF), INF)))->first;
}

void upd(int pos, int val) {
    if (pos == 0 || pos > n) return;
    pii before = get(pos);
    // debug("before(%d) = [%d, %d]\n", pos, before.first, before.second);
    if (d[pos] == 0) {
        hills.erase(Hill(0, pii(pos, pos)));
        invhills.erase(InvHill(pii(pos, pos), 0));
    }
    else {
        hills.erase(Hill(before.second - before.first + 1, before));
        invhills.erase(InvHill(before, before.second - before.first + 1));
    }
    
    pii to_left = get(pos - 1), to_right = get(pos + 1);
    d[pos] += val;
    if (d[pos] == 0) {
        hills.insert(Hill(0, pii(pos, pos)));
        invhills.insert(InvHill(pii(pos, pos), 0));
    }
    pii after = get(pos);
    // debug("after(%d) = [%d, %d]\n", pos, after.first, after.second);
    if (before.first == pos && after.first < pos) {
        // debug("extend left\n");
        hills.erase(Hill(to_left.second - to_left.first + 1, to_left));
        invhills.erase(InvHill(to_left, to_left.second - to_left.first + 1));
    }
    if (before.second == pos && after.second > pos) {
        // debug("extend right\n");
        hills.erase(Hill(to_right.second - to_right.first + 1, to_right));
        invhills.erase(InvHill(to_right, to_right.second - to_right.first + 1));
    }
    if (before.first < after.first) {
        hills.insert(Hill(pos - before.first, pii(before.first, pos - 1)));
        invhills.insert(InvHill(pii(before.first, pos - 1), pos - before.first));
    }
    if (before.second > after.second) {
        hills.insert(Hill(before.second - pos, pii(pos + 1, before.second)));
        invhills.insert(InvHill(pii(pos + 1, before.second), before.second - pos));
    }
    if (d[pos] != 0) {
        hills.insert(Hill(after.second - after.first + 1, after));
        invhills.insert(InvHill(after, after.second - after.first + 1));
    }
}

void print_hills() {
    debug("List of hills:\n");
    for (int i = 1; i <= n; i++) debug("%3lld ", d[i]);
    debug("\n");
    for (Hill h: hills) debug("[%d, %d] (%d)\n", h.second.first, h.second.second, h.first);
    debug("Inverted hills:\n");
    for (InvHill h: invhills) debug("[%d, %d] (%d)\n", h.first.first, h.first.second, h.second);
    debug("---\n");
}    
            
int main() {
    scanf("%d", &n);
    int last;
    scanf("%d", &last);
    for (int i = 1; i < n; i++) {
        int x;
        scanf("%d", &x);
        d[i] = x - last;
        last = x;
    }
    n--;

    for (int i = 1; i <= n;) {
        if (d[i] == 0) {
            hills.insert(Hill(0, pii(i, i)));
            invhills.insert(InvHill(pii(i, i), 0));
            i++;
            continue;
        }
        int j = i;
        if (d[i] > 0) while (j + 1 <= n && d[j + 1] > 0) j++;
        while (j + 1 <= n && d[j + 1] < 0) j++;
        hills.insert(Hill(j - i + 1, pii(i, j)));
        invhills.insert(InvHill(pii(i, j), j - i + 1));
        i = j + 1;
    }
    print_hills();
    
    int q;
    for (scanf("%d", &q); q--;) {
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        upd(l - 1, x);
        upd(r, -x);
        print_hills();
        if (n == 0) printf("1\n");
        else printf("%d\n", hills.rbegin()->first + 1);
    }    
    return 0;
}
