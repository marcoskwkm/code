#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

bool done[MAXN];

int main() {
    vector<int> primes;
    for (int p = 2; p < MAXN; p++) {
        if (!done[p]) {
            primes.push_back(p);
            for (int q = p * p; q < MAXN; q += p)
                done[q] = 1;
        }
    }

    int p1 = -1;
    char buff[10];
    for (int i = 0; i < 5; i++) {
        printf("%d\n", primes[i]);
        fflush(stdout);
        scanf("%s", buff);
        if (buff[0] == 'y') {
            if (p1 != -1) {
                printf("composite\n");
                return 0;
            }
            else p1 = primes[i];
        }
    }
    if (p1 == -1) {
        printf("prime\n");
        return 0;
    }
    for (int i = 5; primes[i] * p1 <= 100; i++) {
        printf("%d\n", primes[i]);
        fflush(stdout);
        scanf("%s", buff);
        if (buff[0] == 'y') {
            printf("composite\n");
            return 0;
        }
    }
    if (p1 < 10) {
        printf("%d\n", p1 * p1);
        fflush(stdout);
        scanf("%s", buff);
        if (buff[0] == 'y') {
            printf("composite\n");
            return 0;
        }
    }
    printf("prime\n");    
    return 0;
}
