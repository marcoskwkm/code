#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    string line;
    int n, q;
    getline(cin, line);
    map<string, string> translation;
    for (sscanf(line.c_str(), "%d", &n); n--;) {
        string lang, expr;
        getline(cin, lang);
        getline(cin, expr);
        translation[lang] = expr;
    }
    getline(cin, line);
    for (sscanf(line.c_str(), "%d", &q); q--;) {
        string name, lang;
        getline(cin, name);
        getline(cin, lang);
        printf("%s\n%s\n\n", name.c_str(), translation[lang].c_str());
    }    
    return 0;
}
