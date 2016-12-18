#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

set<string> s[100];

int main() {
    int n;
    scanf("%d", &n);
    map<string, int> mp;
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        mp[name] = i;
        for (int j = 0; j < 3; j++) {
            string str;
            cin >> str;
            s[i].insert(str);
        }
    }
    string a, b;
    while (cin >> a >> b) {
        if (s[mp[a]].find(b) == s[mp[a]].end())
            printf("Tente Novamente!\n");
        else
            printf("Uhul! Seu amigo secreto vai adorar o/\n");
    }
    return 0;
}
