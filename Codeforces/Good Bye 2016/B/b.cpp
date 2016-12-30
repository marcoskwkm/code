#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n;
    scanf("%d", &n);    
    int pos = 0;
    bool ok = 1;
    for (int i = 0; i < n; i++) {
        int d;
        string dir;
        cin >> d >> dir;
        if (dir == "North") {
            pos -= d;
            if (pos < 0) ok = 0;
        }
        else if (dir == "South") {
            pos += d;
            if (pos > 20000) ok = 0;
        }
        else if (dir == "East" || dir == "West") {
            if (pos == 0 || pos == 20000) ok = 0;
        }
    }

    if (pos != 0) ok = 0;
    printf("%s\n", ok ? "YES" : "NO");        
    return 0;
}
