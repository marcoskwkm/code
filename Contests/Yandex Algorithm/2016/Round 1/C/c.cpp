#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int points[] = {100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
int v[12];

int main() {
    for (int i = 0; i < 10; i++) scanf("%d", &v[i]);
    for (int place = 30; place >= 0; place--) {
        set<int> avail;
        for (int i = 0; i < 30; i++) {
            if (i == place) continue;
            avail.insert(points[i]);
        }
        int cnt;
        for (cnt = 0; cnt < 10; cnt++) {
            int needs = points[place] - v[cnt];
            if (needs <= 0) continue;
            if (avail.lower_bound(needs) == avail.end()) break;
            avail.erase(avail.lower_bound(needs));
        }
        if (cnt < 10) {
            printf("%d\n", place == 30 ? 1000 : place + 1);
            return 0;
        }
    }
    printf("0\n");
    return 0;
}
