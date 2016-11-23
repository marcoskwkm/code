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
    return prev(invhills.lower_bound(InvHill(pii(pos, INF), INF)))->first;
}

inline void add(int l, int r, int k) {
    hills.insert(Hill(k, pii(l, r)));
    invhills.insert(InvHill(pii(l, r), k));
}

inline void rem(int l, int r, int k) {
    hills.erase(Hill(k, pii(l, r)));
    invhills.erase(InvHill(pii(l, r), k));
}

inline bool compat(lint a, lint b) {
    if (!a || !b) return 0;
    return sign(a) == sign(b) || (a > 0 && b < 0);
}

void upd(int pos, int val) {
    // debug("upd %d\n", pos);
    if (pos == 0 || pos > n) return;
    int before_l, before_r;
    tie(before_l, before_r) = get(pos);
    int left_l, left_r, right_l, right_r;
    tie(left_l, left_r) = get(pos - 1);
    tie(right_l, right_r) = get(pos + 1);

    if (d[pos] == 0) rem(pos, pos, 0);
    else rem(before_l, before_r, before_r - before_l + 1);
    d[pos] += val;
    // debug("[%d, %d], [%d, %d]\n", left_l, left_r, right_l, right_r);
    if (d[pos] == 0) {
        add(pos, pos, 0);
        if (before_l < pos)
            add(before_l, pos - 1, pos - before_l);
        if (before_r > pos)
            add(pos + 1, before_r, before_r - pos);            
    }
    else {
        int after_l = pos, after_r = pos;
        if (pos > 1 && compat(d[pos - 1], d[pos])) {
            after_l = left_l;
            if (left_r < pos) rem(left_l, left_r, left_r - left_l + 1);
        }
        else if (before_l < pos)
            add(before_l, pos - 1, pos - before_l);
        if (pos < n && compat(d[pos], d[pos + 1])) {
            after_r = right_r;
            if (right_l > pos) rem(right_l, right_r, right_r - right_l + 1);
        }
        else if (before_r > pos)
            add(pos + 1, before_r, before_r - pos);
        // debug("after = [%d, %d]\n", after_l, after_r);
        add(after_l, after_r, after_r - after_l + 1);
    }        
}

void print_hills() {
    // debug("List of hills:\n");
    // for (int i = 1; i <= n; i++) debug("%3lld ", d[i]);
    // debug("\n");
    // for (Hill h: hills) debug("[%d, %d] (%d)\n", h.second.first, h.second.second, h.first);
    // debug("Inverted hills:\n");
    // for (InvHill h: invhills) debug("[%d, %d] (%d)\n", h.first.first, h.first.second, h.second);
    // debug("---\n");
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
        print_hills();
        upd(r, -x);
        print_hills();
        if (n == 0) printf("1\n");
        else printf("%d\n", hills.rbegin()->first + 1);
    }    
    return 0;
}
