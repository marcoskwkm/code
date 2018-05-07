#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

string resp[10];
vector<int> cnt(6);

int main() {
    vector<string> normal =
        {"great", "don't think so", "don't touch me", "not bad", "cool", "no"};
    for (int i = 0; i < 10; i++) {
        printf("%d\n", i);
        fflush(stdout);
        string s;
        getline(cin, s);
        for (int j = 0; j < 6; j++) {
            if (s.find(normal[j]) != string::npos) {
                cnt[j]++;
                break;
            }
        }
    }
    vector<int> sol = {1, 1, 1, 1, 1, 5};
    printf("%s\n", cnt == sol ? "normal" : "grumpy");
    fflush(stdout);
    // abort();
    return 0;
}
