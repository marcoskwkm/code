#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

bool is_prime(lint n) {
    if (n < 2) return 0;
    for (lint d = 2; d * d <= n; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

int main() {
    lint a, b;
    cin >> a >> b;
    set<lint> avail;
    avail.insert(a);
    avail.insert(2);
    for (int i = -2; i <= 2; i += 4) {
        if (is_prime(a + i)) avail.insert(a + i);
        if (is_prime(b + i)) avail.insert(b + i);
    }
        
    map<lint, lint> prv;
    queue<lint> q({b});
    avail.erase(b);
    while (!q.empty()) {
        lint v = q.front();
        q.pop();
        vector<lint> trash;
        for (lint nxt: avail) {
            if (is_prime(abs(nxt - v))) {
                q.push(nxt);
                trash.push_back(nxt);
                prv[nxt] = v;
            }
        }
        for (lint x: trash) avail.erase(x);
    }

    if (prv.find(a) == prv.end()) printf("Unlucky Benny\n");
    else {
        printf("%lld", a);
        lint cur = prv[a];
        while (cur != 0) {
            printf("->%lld", cur);
            cur = prv[cur];
        }
        printf("\n");
    }        
    return 0;
}
