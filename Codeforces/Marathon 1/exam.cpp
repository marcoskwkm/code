#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

const int N = 5000, K = 2000, X = 100;

char str[N + 10];
vector<int> guessed;

int main() {
    srand(42);
    for (int i = 0; i < N; i++)
        str[i] = '0' + rand() % 2;
    str[N] = 0;
    int nxt = 0, last_guessed = -1;
    for (int step = 0; step < X; step++) {
        printf("%s\n", str);
        fflush(stdout);
        int at;
        scanf("%d", &at);
        if (at == N + 1) return 0;
        if (last > nxt) {
            if (last_guessed != -1)
                guessed.pop_back();
            while (nxt < at)
                guessed.push_back(nxt++);
        }
    
    return 0;
}
