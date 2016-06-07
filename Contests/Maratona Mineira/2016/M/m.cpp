#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int getscore(char c) { return c == 'X' ? 10 : c - '0'; }
int pos[10];

int main() {
    string scores = "";
    int rem = 0;
    for (int i = 0; i < 10; i++) {
        string inning;
        cin >> inning;
        pos[i] = scores.size();
        scores += inning;
        if (i == 9) {
            if (inning[0] == 'X') rem = 2;
            else if (inning[1] == '/') rem = 1;
        }
    }
    int score = 0;
    int len = scores.size();
    for (int i = 0; i < len - rem; i++) {
        if (scores[i] != '/') score += getscore(scores[i]);
        else score += 10 - getscore(scores[i - 1]);
        if (scores[i] == 'X') {
            if (scores[i + 2] == '/') score += 10;
            else score += getscore(scores[i + 1]) + getscore(scores[i + 2]);
        }
        else if (scores[i] == '/') {
            score += getscore(scores[i + 1]);
        }
    }
    printf("%d\n", score);                
    return 0;
}
