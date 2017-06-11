#include "broken_memory.h"
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
    int qn = NumberOfNodes(), thisId = MyNodeId();
    int N = GetLength();
    for (int i = 0; i < N; i++)
        PutLL(0, GetValue(i));
    Send(0);
    if (thisId > 0) return 0;

    vector<int> values[20];
    for (int i = 0; i < qn; i++) {
        Receive(i);
        for (int j = 0; j < N; j++)
            values[i].push_back(GetLL(i));
    }
    int ans[20];
    for (int x = 0; x < N; x++) {
        int p1 = -1, p2 = -1;
        for (int i = 1; i < qn; i++) {
            if (values[0][x] != values[i][x]) {
                p2 = p1;
                p1 = i;
            }
        }
        if (p1 == -1) continue;
        if (p2 == -1) ans[p1] = x;
        else ans[0] = x;
    }
    for (int i = 0; i < qn; i++)
        printf("%d%c", ans[i], i + 1 == qn ? '\n' : ' ');    
    return 0;
}
