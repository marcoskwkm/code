#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int BUFF_SIZE = (int)1e5 + 10;
const int N_THREADS = 4;
const int MAXT = 1010;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

mutex input_mutex;
queue<int> test_cases;
string solutions[MAXT];

struct Problem {
    char output[BUFF_SIZE];
    char *out = output;

    static const int MAXN = 52;

    vector<lint> pack[MAXN];
    lint grams[MAXN];
    int N, P;
    
    void readInput() {
        scanf("%d%d", &N, &P);
        for (int i = 0; i < N; i++)
            scanf("%lld", &grams[i]);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {
                lint w;
                scanf("%lld", &w);
                pack[i].push_back(w);
            }
            sort(pack[i].begin(), pack[i].end(), greater<lint>());
        }
    }    
    
    string solve(int test_case) {
        out += sprintf(out, "Case #%d: ", test_case);
        int ans = 0;
        for (lint q = 1; q <= 1000000; q++) {
            bool take = 1;
            for (int i = 0; i < N; i++) {
                while (!pack[i].empty() && 10 * pack[i].back() < 9 * q * grams[i])
                    pack[i].pop_back();
                if (pack[i].empty()) {
                    take = 0;
                    break;
                }
                if (10 * pack[i].back() > 11 * q * grams[i])
                    take = 0;
            }
            if (take) {
                ans++;
                for (int i = 0; i < N; i++) {
                    pack[i].pop_back();
                }
                q--;
            }
        }                    
        
        out += sprintf(out, "%d\n", ans);
        return string(output);
    }    
};

void solver() {
    while (1) {
        input_mutex.lock();
        if (test_cases.empty()) {
            input_mutex.unlock();
            return;
        }
        int test_case = test_cases.front();
        test_cases.pop();
        Problem problem;
        problem.readInput();
        input_mutex.unlock();
        clock_t time = clock();
        solutions[test_case] = problem.solve(test_case);
        debug("Finished case #%d (%.3fs)\n", test_case, double(clock() - time) / CLOCKS_PER_SEC);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++)
        test_cases.push(t);
    vector<thread> threads;
    for (int i = 0; i < N_THREADS; i++)
        threads.push_back(thread(solver));
    for (int i = 0; i < N_THREADS; i++)
        threads[i].join();
    for (int t = 1; t <= T; t++)
        printf("%s", solutions[t].c_str());
    return 0;
}
