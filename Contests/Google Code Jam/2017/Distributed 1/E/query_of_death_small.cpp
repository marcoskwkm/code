#include "query_of_death.h"
#include <bits/stdc++.h>
#include <message.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int thisId = MyNodeId();
    int N = GetLength();
    if (thisId >= 2) return 0;
    if (thisId == 1) {
        for (int i = 0; i < N; i++) {
            int value = GetValue(i);
            for (int j = 0; j < 99; j++) {
                if (value != GetValue(i)) {
                    PutInt(0, i);
                    Send(0);
                    return 0;
                }
            }
        }
    }
    else {
        Receive(1);
        int iod = GetInt(1);
        int ans = 0;
        for (int i = 0; i < N; i++) {
            if (i != iod)
                ans += GetValue(i);
        }
        ans += GetValue(iod);
        cout << ans << endl;
    }        
    return 0;
}
