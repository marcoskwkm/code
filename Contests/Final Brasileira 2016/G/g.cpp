#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int last[30];

struct KMP {
    vector<int> pattern;
    int len;
    vector<int> f;
    KMP(vector<int> p) {
        pattern = p;
        len = p.size();
        f.resize(len + 2);
        f[0] = f[1] = 0;
        for (int i = 2; i <= len; i++) {
            int now = f[i - 1];
            while (1) {
                int val = p[i - 1];
                if (val != -1 && val > now) val = -1;
                if (p[now] == val) {
                    f[i] = now + 1;
                    break;
                }
                if (now == 0) {
                    f[i] = 0;
                    break;
                }
                now = f[now];
            }
        }
    }

    vector<int> match(vector<int> text) {
        vector<int> ret;
        int size = text.size();
        int i = 0, j = 0;
        while (j < size) {
            int val = text[j];
            if (val != -1 && val > i) val = -1;
            if (val == pattern[i]) {
                i++, j++;
                if (i == len) {
                    ret.push_back(j - len);
                    i = f[i];
                }
            }
            else if (i > 0) i = f[i];
            else j++;
        }
        return ret;
    }
};    

int main() {
    string s;
    cin >> s;
    vector<int> str;
    memset(last, -1, sizeof(last));
    for (int i = 0; i < (int)s.size(); i++) {
        str.push_back(last[s[i] - 'a'] == -1 ? -1 : i - last[s[i] - 'a']);
        last[s[i] - 'a'] = i;
    }
    int n;
    scanf("%d", &n);
    vector<int> pat;
    memset(last, -1, sizeof(last));
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        pat.push_back(last[x] == -1 ? -1 : i - last[x]);
        last[x] = i;
    }

    KMP kmp(pat);
    printf("%d\n", (int)kmp.match(str).size());    
    return 0;
}
