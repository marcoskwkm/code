#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct Interval {
    int size;
    int l, r;
    lint sum;

    Interval() {}
    Interval(int ll, int rr) {
        l = ll; r = rr;
        size = abs(r - l) + 1;
        sum = lint(l + r)*size/2;
    }
    void reverse() {
        swap(l, r);
    }
    Interval split(int len) {
        Interval pref;
        if (l < r) {
            pref = Interval(l, l + len - 1);
            size -= pref.size;
            sum -= pref.sum;
            l = l + len;
        }
        else {
            pref = Interval(l, l - len + 1);
            size -= pref.size;
            sum -= pref.sum;
            l = l - len;
        }
        return pref;
    }
};

pii split(vector<Interval> &v, int l, int r) {
    int i = 0;
    int size = 0;
    while (size + v[i].size < l) size += v[i++].size;
    if (size < l - 1) {
        v.insert(v.begin() + i, v[i].split(l - 1 - size));
        size += v[i++].size;
    }
    assert(size == l - 1);
    int ll = i;
    while (size + v[i].size < r) size += v[i++].size;
    if (size + v[i].size > r)
        v.insert(v.begin() + i, v[i].split(r - size));
    size += v[i].size;
    assert(size == r);
    return pii(ll, i);
}

void reverse(vector<Interval> &v, int l, int r) {
    pii p = split(v, l, r);
    int ll = p.first, rr = p.second;
    while (ll < rr) {
        v[ll].reverse();
        v[rr].reverse();
        swap(v[ll], v[rr]);
        ll++; rr--;
    }
    if (ll == rr) v[ll].reverse();
}

lint sum(vector<Interval> &v, int l, int r) {
    pii p = split(v, l, r);
    lint ret = 0;
    for (int i = p.first; i <= p.second; i++)
        ret += v[i].sum;
    return ret;
}    

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<Interval> v = {Interval(1, n)};
    while (m--) {
        char op;
        int l, r;
        scanf(" %c%d%d", &op, &l, &r);
        if (op == 'I') reverse(v, l, r);
        else printf("%lld\n", sum(v, l, r));
    }    
    return 0;
}
