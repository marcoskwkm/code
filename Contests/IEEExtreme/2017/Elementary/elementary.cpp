#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

// From https://iupac.org/what-we-do/periodic-table-of-elements/
const set<string> elements = {
    "h", "li", "na", "k", "rb", "cs", "fr",
    "be", "mg", "ca", "sr", "ba", "ra",
    "sc", "y",
    "ti", "zr", "hf", "rf",
    "v", "nb", "ta", "db",
    "cr", "mo", "w", "sg",
    "mn", "tc", "re", "bh",
    "fe", "ru", "os", "hs",
    "co", "rh", "ir", "mt",
    "ni", "pd", "pt", "ds",
    "cu", "ag", "au", "rg",
    "zn", "cd", "hg", "cn",
    "b", "al", "ga", "in", "tl", "nh",
    "c", "si", "ge", "sn", "pb", "fl",
    "n", "p", "as", "sb", "bi", "mc",
    "o", "s", "se", "te", "po", "lv",
    "f", "cl", "br", "i", "at", "ts",
    "he", "ne", "ar", "kr", "xe", "rn", "og",
    "la", "ce", "pr", "nd", "pm", "sm", "eu", "gd", "tb", "dy", "ho", "er", "tm", "yb", "lu",
    "ac", "th", "pa", "u", "np", "pu", "am", "cm", "bk", "cf", "es", "fm", "md", "no", "lr"
};

int main() {
    int t;
    for (cin >> t; t--;) {
        string s;
        cin >> s;
        vector<int> dp(s.size() + 1);
        dp[0] = 1;
        for (size_t i = 1; i <= s.size(); i++) {
            if (elements.find(s.substr(i - 1, 1)) != elements.end())
                dp[i] += dp[i - 1];
            if (i > 1 && elements.find(s.substr(i - 2, 2)) != elements.end())
                dp[i] += dp[i - 2];
        }
        printf("%d\n", dp[s.size()]);
    }    
    return 0;
}
