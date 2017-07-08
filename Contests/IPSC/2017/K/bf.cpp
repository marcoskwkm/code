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
        cin >> line;
        vector<int> bits;
        vector<int> q;
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

        int n = bits.size();
        for (int i = 0; i < n; i++) {
            if (bits[i] == 2)
                q.push_back(i);
        }
        
        for (int i = 1; i < n; i++) {
            bool ok = 1;
            for (int j = 0; i + j < n; j++) {
                if (bits[j] != bits[i + j] && bits[i + j] != 2 && bits[j] != 2) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                debug("pwned i = %d\n", i);
                for (int j = 0; j < i; j++) {
                    vector<int> d;
                    for (int k = j; k < n; k += i)
                        d.push_back(bits[k]);
                    sort(d.begin(), d.end());
                    for (int k = j; k < n; k += i) {
                        if (d[0] == 2) bits[k] = rand() % 2;
                        else bits[k] = d[0];
                    }
                }
                for (int qq: q) printf("%d", bits[qq]);
                printf("\n");
                break;
            }                
        }
    }            
    return 0;
}
