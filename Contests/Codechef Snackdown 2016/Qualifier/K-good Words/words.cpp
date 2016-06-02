#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int freq[30];
int acc[30];

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        string s;
        int k;
        cin >> s >> k;
        memset(freq, 0, sizeof(freq));
        for (char c: s)
            freq[c - 'a']++;
        sort(freq, freq + 26);
        for (int i = 25; i >= 0; i--)
            acc[i] = acc[i + 1] + freq[i];
        int ans = INF, cur = 0, j = 0;
        for (int i = 0; i < 26; i++) {
            while (j + 1 < 26 && freq[j + 1] - freq[i] <= k) j++;
            ans = min(ans, cur + acc[j + 1] - (26 - j - 1) * (freq[i] + k));
            cur += freq[i];
        }
        printf("%d\n", ans);
    }        
    return 0;
}
