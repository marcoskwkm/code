#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXL = 1010;

char word[MAXL];
char nxt[MAXL];
bool capital[MAXL];
int len;

void transform() {
    for (int i = 0; i < len; i++)
        capital[i] = isupper(word[i]);
    if (len & 1) {
        for (int i = 0; i < len; i++)
            nxt[i] = word[len - 1 - i];
    }
    else {
        for (int i = 0; i < len; i++)
            nxt[i] = word[(i + len/2) % len];
    }
    for (int i = 0; i < len; i++)
        printf("%c", capital[i] ? toupper(nxt[i]) : tolower(nxt[i]));
}    

int main() {
    char c;
    while (scanf("%c", &c) != EOF) {
        if (isalpha(c)) word[len++] = c;
        else {
            transform();
            printf("%c", c);
            len = 0;
        }
    }
    transform();
    return 0;
}
