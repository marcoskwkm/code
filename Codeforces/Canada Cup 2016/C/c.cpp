#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int seen[300];
char ans[2][30];
int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};

bool test(string s) {
    memset(seen, 0, sizeof(seen));
    int at = 0;
    for (int c = 0; c < 13; c++) {
        if (seen[s[at]]) {
            c--;
            at++;
            continue;
        }
        seen[s[at]] = 1;
        ans[0][c] = s[at++];
    }
    for (int c = 12; c >= 0; c--) {
        if (seen[s[at]]) {
            c++;
            at++;
            continue;
        }
        seen[s[at]] = 1;
        ans[1][c] = s[at++];
    }

    int r = 0, c = 0;
    for (int i = 1; i < (int)s.size(); i++) {
        bool ok = 0;
        for (int j = 0; j < 8; j++) {
            int nr = r + dr[j], nc = c + dc[j];
            if (nr < 0 || nc < 0 || nr >= 2 || nc >= 13)
                continue;
            if (ans[nr][nc] == s[i]) {
                ok = 1;
                r = nr, c = nc;
                break;
            }
        }
        if (!ok) return 0;
    }
    return 1;
}        

int main() {
    string s;
    cin >> s;
    for (int i = 0; i < 26; i++) {
        if (s[i] == s[i + 1]) {
            printf("Impossible\n");
            return 0;
        }
    }
    for (int i = 0; i < 27; i++) {
        if (test(s)) {
            printf("%s\n%s\n", ans[0], ans[1]);
            return 0;
        }
        rotate(s.begin(), s.begin() + 1, s.end());
    }
    printf("Impossible\n");        
    return 0;
}
