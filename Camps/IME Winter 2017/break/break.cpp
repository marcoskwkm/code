#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (cin >> t; t--;) {
        lint a, b, c;
        cin >> a >> b >> c;
        if (a * b == c) {
            printf("0\n");
            continue;
        }
        if (c % a == 0 || c % b == 0) {
            printf("1\n");
            continue;
        }
        bool found = 0;
        if (a > b) swap(a, b);
        for (lint d = 1; d * d <= c; d++) {
            if (c % d) continue;
            if (d <= a && c / d <= b) {
                printf("2\n");
                found = 1;
                break;
            }
        }
        if (found) continue;
        c = a * b - c;
        for (lint d = 1; d * d <= c; d++) {
            if (c % d) continue;
            if (d <= a && c / d <= b) {
                printf("2\n");
                found = 1;
                break;
            }
        }
        if (found) continue;
        printf("3\n");
    }        
    return 0;
}
