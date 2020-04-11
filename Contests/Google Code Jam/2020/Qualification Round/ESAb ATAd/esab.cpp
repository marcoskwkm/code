#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXB = 110;

char read() {
    char resp;
    scanf(" %c", &resp);
    if (resp == 'N') exit(0);
    return resp;
}

int cnt = 0;
char get(int idx) {
    cnt++;
    printf("%d\n", idx + 1);
    fflush(stdout);
    return read();
}

int B;
int v[MAXB];

void flip(int lim) {
    for (int i = 0; i < lim; i++) {
        v[i] ^= 1;
        v[B - 1 - i] ^= 1;
    }
}

void reverse(int lim) {
    for (int i = 0; i < lim; i++) {
        swap(v[i], v[B - 1 - i]);
    }
}

int main() {
    int t = 1, T;
    for (cin >> T >> B; t <= T; t++) {
        cnt = 0;
        int eIdx = -1, dIdx = -1;

        for (int i = 0; 2 * i < B; i++) {
            v[i] = get(i) - '0';
            v[B - 1 - i] = get(B - 1 - i) - '0';
            if (cnt > 2 && cnt % 10 == 2) {
                if (eIdx == -1) eIdx = dIdx;
                if (dIdx == -1) dIdx = eIdx;

                int ed = get(eIdx) - '0';
                int dd = get(dIdx) - '0';
                if (ed == v[eIdx] && dd == v[dIdx]) {
                    // no changes
                } else if (ed == v[eIdx] && dd != v[dIdx]) {
                    // rev
                    reverse(i);
                } else if (ed != v[eIdx] && dd == v[dIdx]) {
                    // flip + rev
                    flip(i);
                    reverse(i);
                } else {
                    // flip
                    flip(i);
                }
            }

            if (v[i] == v[B - 1 - i]) {
                eIdx = i;
            } else {
                dIdx = i;
            }
        }

        for (int i = 0; i < B; i++) {
            printf("%d", v[i]);
        }
        printf("\n");
        fflush(stdout);

        read();
    }
    return 0;
}
