#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

char st[MAXN];
int len;

int main() {
    string s;
    while (cin >> s) {
        len = 0;
        for (char c: s) {
            if (len > 0) {
                if (islower(c) && toupper(c) == st[len - 1]) {
                    len--;
                    continue;
                }
                else if(isupper(c) && tolower(c) == st[len - 1]) {
                    len--;
                    continue;
                }
                else st[len++] = c;
            }
            else st[len++] = c;
        }
        if (len == 0) printf("Vazia\n");
        else {
            for (int i = 0; i < len; i++)
                printf("%c", st[i]);
            printf("\n");
        }
    }
    return 0;
}
