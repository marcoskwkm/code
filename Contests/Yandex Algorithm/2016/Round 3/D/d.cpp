#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

char start;

bool guess(lint x) {
    printf("? %lld\n", x);
    fflush(stdout);
    char got;
    scanf(" %c", &got);
    return got == start;
}

int main() {
    printf("? 0\n");
    fflush(stdout);
    scanf(" %c", &start);
    
    lint right = 0;
    int i;
    for (i = 0; i < 63; i++) {
        if (guess(1LL << i)) right = (1LL << i);
        else break;
    }
    lint l = right, r = (1LL << i) - 1;
    while (l < r) {
        lint mid = (l + r + 1) / 2;
        if (guess(mid)) l = mid;
        else r = mid - 1;
    }
    right = l;

    lint left = 0;

    for (i = 0; i < 63; i++) {
        if (guess(-(1LL << i))) left = (1LL << i);
        else break;
    }
    l = left, r = (1LL << i) - 1;
    while (l < r) {
        lint mid = (l + r + 1) / 2;
        if (guess(-mid)) l = mid;
        else r = mid - 1;
    }
    left = -l;

    printf("! %lld\n", right - left + 1);    
    return 0;
}
