#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXV = (int)1e7 + 10;

int q[MAXV], q2[2 * MAXV];

int main() {
    vector<int> ls, v;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        q[x]++;
        ls.push_back(x);
        v.push_back(x);
    }
    sort(ls.begin(), ls.end());
    ls.erase(unique(ls.begin(), ls.end()), ls.end());
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            q2[v[i] + v[j]]++;

    lint ans = 0;

    // 1 + 1 + 2 + 2
    for (int length: ls) {
        lint ql = q[length], qp = q2[length];
        // printf("length = %d: ql = %lld, qp = %lld:\n", length, ql, qp);
        lint add = qp * (qp - 1) / 2;
        for (int rep: v) {
            if (rep >= length) continue;
            int rem = length - rep;
            lint qr = q[rem];
            if (rem == rep) qr--;
            add -= qr * (qr - 1) / 2;
        }
        // printf("add = %lld\n", add);
        for (int half: ls) {
            if (half >= length) break;
            if (2 * half < length) continue;
            if (2 * half == length) {
                lint qh = q[half];
                add -= 2 * qh * (qh - 1) * (qh - 2) * (qh - 3) / 24;
            }
            else {
                lint qhi = q[half], qlo = q[length - half];
                add -= qhi * (qhi - 1) / 2 * qlo * (qlo - 1) / 2;
            }
        }
        // printf("add = %lld\n", add);
        
        ans += add * ql * (ql - 1) / 2;
    }
    
    // 1 + 1 + 1 + 3
    for (int length: ls) {
        lint add = 0;
        for (int x: v) {
            if (x >= length) continue;
            lint got = q2[length - x];
            if (2 * x < length) {
                got -= q[length - 2*x];
                if (3 * x == length) got++;
            }
            // printf("x = %d: got = %lld\n", x, got);
            add += got;
        }
        lint ql = q[length];
        ans += ql * (ql - 1) * (ql - 2) / 6 * add / 3;
        // printf("length = %d, add = %lld\n", length, add);
    }
    
    cout << ans << endl;    
    return 0;
}
