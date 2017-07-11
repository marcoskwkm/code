#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = 110;

enum Result {FIRST, SECOND, ROWAN, COLLETE, WTF};

Result result[MAXD][MAXD];

Result get_result(int r, int c) {
    if (r == 1) {
        if (c == 1) return SECOND;
        return COLLETE;
    }
    else if (c == 1) {
        if (r == 1) return SECOND;
        return ROWAN;
    }
    if (result[r][c] != WTF) return result[r][c];

    // Collete plays
    int collete = 0;
    for (int cc = 1; cc < c; cc++) {
        Result r1 = get_result(r, cc), r2 = get_result(r, c - cc);
        if (r1 == SECOND || r1 == COLLETE || r2 == SECOND || r2 == COLLETE) {
            collete = 1;
            break;
        }
    }

    // Rowan plays
    int rowan = 0;
    for (int rr = 1; rr < r; rr++) {
        Result r1 = get_result(rr, c), r2 = get_result(r - rr, c);
        if (r1 == SECOND || r1 == ROWAN || r2 == SECOND || r2 == ROWAN) {
            
    
}

int main() {
    
    return 0;
}
