#include "weird_editor.h"
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
const int MOD = (int)1e9 + 7;
const int MAXS = (int)2e7 + 10;

int v[MAXS];

lint modexp(lint b, lint e) {
    if (e == 0) return 1;
    lint aux = modexp(b, e / 2);
    if (e & 1) return aux * aux % MOD * b % MOD;
    return aux * aux % MOD;
}    

int main() {
    lint qn = NumberOfNodes(), thisId = MyNodeId();
    lint N = GetNumberLength();
    if (thisId >= N) return 0;
    qn = min(qn, N);
    lint size = N / qn;
    lint l = thisId * size, r = (thisId + 1) * size - 1;
    if (thisId + 1 == qn) r = N - 1;
    for (int i = l; i <= r; i++)
        v[i - l] = GetDigit(i);
    
    vector<pll> number;
    lint first_digit = 0;
    for (int d = 9; d > 0; d--) {
        if (thisId == 0) {
            for (int node = 0; node < qn; node++) {
                PutLL(node, first_digit);
                Send(node);
            }
        }
        Receive(0);
        lint first = GetLL(0);
        int cnt = 0;
        lint last = -1;
        for (int i = max(first, l); i <= r; i++) {
            if (v[i - l] == d) {
                cnt++;
                last = i;
            }
        }
        PutLL(0, cnt);
        PutLL(0, last);
        Send(0);

        if (thisId == 0) {
            int total_cnt = 0;
            for (int node = 0; node < qn; node++) {
                Receive(node);
                total_cnt += GetLL(node);
                first_digit = max(first_digit, GetLL(node));
            }
            number.push_back(pll(d, total_cnt));
        }
    }

    if (thisId != 0) return 0;
    int n_digits = 0;
    lint ans = 0;
    const lint inv9 = modexp(9, MOD - 2);
    for (pll p: number) {
        lint add = modexp(10, p.second);
        ans = (ans * add) % MOD;
        add = ((add - 1) * inv9 % MOD * p.first % MOD + MOD) % MOD;
        ans = (ans + add) % MOD;
        n_digits += p.second;
    }
    ans = (ans * modexp(10, N - n_digits)) % MOD;
    cout << ans << endl;    
    return 0;
}
