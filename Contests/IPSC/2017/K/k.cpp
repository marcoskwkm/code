#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)4e6 + 10;
const int NBITS = 4;

int main() {
    string line;
    for (int l = 0; l < 2; l++) {
        if (l == 1) continue;
        cin >> line;
        vector<int> bits;
        for (char c: line) {
            c -= 33;
            stack<int> st;
            for (int j = 0; j < 4; j++) {
                st.push(c % 3);
                c /= 3;
            }
            while (!st.empty()) {
                bits.push_back(st.top());
                st.pop();
            }
        }

        vector<int> v;
        for (int i = 0; i < 4000000; i += NBITS) {
            int x = 0;
            for (int j = 0; j < NBITS; j++) {
                if (bits[i + j] == 2) {
                    x = -1;
                    break;
                }
                x = (x << 1) + bits[i + j];
            }
            v.push_back(x);
            printf("%d\n", x);
        }

        return 0;
        for (int a = 1; a < 16; a++) {
            for (int b = 0; b < 16; b++) {
                for (int x0 = 0; x0 < 16; x0++) {
                    bool ok = 1;
                    int x = x0;
                    for (int e: v) {
                        if (x != e && e != 2) {
                            ok = 0;
                            break;
                        }
                        x = (a*x + b) % 16;
                    }
                    if (ok) {
                        printf("Found %d %d %d\n", a, b, x0);
                    }
                }
            }
        }
    }            
    return 0;
}
