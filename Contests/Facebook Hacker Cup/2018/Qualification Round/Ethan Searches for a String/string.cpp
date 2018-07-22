#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

bool ethan(const string &A, const string &B) {
    int i = 0, j = 0;
    while (1) {
        if (i == (int)A.size()) {
            return 1;
        }
        if (j == (int)B.size()) return 0;
        if (A[i] == B[j]) {
            i++, j++;
            continue;
        }
        if (i == 0) j++;
        else i = 0;
    }
    return 0;
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d: ", t);
        string A;
        cin >> A;
        bool found = 0;
        for (int i = 1; i < (int)A.size(); i++) {
            if (A[i] != A[0]) continue;
            string B = A.substr(0, i) + A;
            if (!ethan(A, B)) {
                printf("%s\n", B.c_str());
                found = 1;
                break;
            }
        }
        if (!found) printf("Impossible\n");
    }
    return 0;
}
