#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

vector<string> v = {"Danil", "Olya", "Slava", "Ann", "Nikita"};

int main() {
    string s;
    cin >> s;
    int cnt = 0;
    for (auto name: v) {
        for (size_t i = 0; i + name.size() <= s.size(); i++)
            if (s.substr(i, name.size()) == name)
                cnt++;
    }
    printf("%s\n", cnt == 1 ? "YES" : "NO");
    return 0;
}
