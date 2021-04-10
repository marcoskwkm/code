#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int count_match(int mask1, int mask2, int q) {
    int mask = (~(mask1 ^ mask2)) & ((1 << q) - 1);
    return __builtin_popcount(mask);
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> students;
    for (int i = 0; i < n; i++) {
        int mask = 0;
        for (int j = 0; j < q; j++) {
            char answer;
            scanf(" %c", &answer);
            if (answer == 'T') {
                mask |= (1 << j);
            }
        }
        int score;
        scanf("%d", &score);
        students.push_back(pii(mask, score));
    }

    vector<int> cands;
    for (int mask = 0; mask < (1 << q); mask++) {
        bool valid = 1;
        for (pii &p: students) {
            if (count_match(mask, p.first, q) != p.second) {
                valid = 0;
            }
        }
        if (valid) {
            cands.push_back(mask);
        }
    }

    int max_score_sum = 0;
    int best_answer = 0;
    for (int mask = 0; mask < (1 << q); mask++) {
        int score_sum = 0;
        for (int answer: cands) {
            score_sum += count_match(mask, answer, q);
        }
        if (score_sum > max_score_sum) {
            max_score_sum = score_sum;
            best_answer = mask;
        }
    }

    printf(" ");
    for (int i = 0; i < q; i++) {
        printf("%c", (best_answer & (1 << i)) ? 'T' : 'F');
    }
    int num = max_score_sum, den = cands.size();
    int gcd = __gcd(num, den);
    num /= gcd;
    den /= gcd;
    printf(" %d/%d\n", num, den);
}

int main() {
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d:", t);
        solve();
    }
    return 0;
}
