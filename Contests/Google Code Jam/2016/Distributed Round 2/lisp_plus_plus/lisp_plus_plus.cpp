#include "lisp_plus_plus.h"
#include <message.h>
#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e7 + 10;

int seq[MAXN];
int pos[MAXN];
int len;

int main() {
    int m = NumberOfNodes(), thisId = MyNodeId();
    int N = GetLength();
    int n = (N + m - 1) / m;
    int nrem = N % m;

    int cur = 0;
    int L = thisId * n, R = min(N, (thisId + 1) * n);
    for (int i = L; i < R; i++) {
        char c = GetCharacter(i);
        if (c == '(') cur++;
        else {
            cur--;
            if (len == 0 || seq[len - 1] > cur) {
                seq[len] = cur;
                pos[len] = i;
                len++;
            }
        }
    }
//    debug("node %d (%d to %d): cur = %d\n", thisId, L, R - 1, cur);

    int from_left = 0;
    if (thisId > 0) {
        Receive(thisId - 1);
        from_left = GetInt(thisId - 1);
//        debug("node %d: from_left = %d\n", thisId, from_left);
        if (from_left < 0) {
            if (thisId + 1 < m) {
                PutInt(thisId + 1, -1);
                Send(thisId + 1);
            }
            return 0;
        }
    }


    int l = 0, r = len - 1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (seq[mid] + from_left >= 0) l = mid + 1;
        else r = mid;
    }
//    debug("node %d: seq[l] + from_left = %d\n", thisId, seq[l] + from_left);
    
    if (len == 0 || seq[l] + from_left >= 0) {
        if (thisId + 1 < m) {
            PutInt(thisId + 1, from_left + cur);
            Send(thisId + 1);
        }
        else {
            if (cur + from_left == 0) {
                printf("-1\n");
            }
            else {
                printf("%d\n", N);
            }
        }
    }
    else {
        if (thisId + 1 < m) {
            PutInt(thisId + 1, -1);
            Send(thisId + 1);
        }
        printf("%d\n", pos[l]);
    }    
    return 0;
}
