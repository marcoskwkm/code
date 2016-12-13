#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXL = (int)1e6 + 10;

char ans[MAXL];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        int aa = 0, ab = 0, ba = 0, bb = 0;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            if (s == "aa") aa++;
            else if (s == "ab") ab++;
            else if (s == "ba") ba++;
            else bb++;
        }
        int size = 0;
        while (aa >= 2) {
            ans[size++] = 'a';
            ans[size++] = 'a';
            aa -= 2;
        }
        while (ab > 0 && ba > 0) {
            ans[size++] = 'a';
            ans[size++] = 'b';
            ab--; ba--;
        }
        while (bb >= 2) {
            ans[size++] = 'b';
            ans[size++] = 'b';
            bb -= 2;
        }
        ans[size] = 0;
        printf("%s", ans);
        if (aa > 0) printf("aa");
        else if (bb > 0) printf("bb");
        reverse(ans, ans + size);
        printf("%s\n", ans);
    }        
    return 0;
}
