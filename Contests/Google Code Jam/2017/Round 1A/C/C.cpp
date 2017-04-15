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

    lint Hd, Ad, Hk, Ak, B, D;
    
    void readInput() {
        cin >> Hd >> Ad >> Hk >> Ak >> B >> D;
    }

    int calc(int n_buff, int n_debuff) {
        lint hd = Hd, ad = Ad, hk = Hk, ak = Ak;
        int n_turns = 0;
        int last_heal = -1;
        bool dead = 0;
        for (int i = 0; i < n_debuff; i++) {
            n_turns++;
            int nxt_ak = max(0ll, ak - D);
            if (hd - nxt_ak <= 0) {
                if (last_heal == i || Hd - ak <= 0) {
                    dead = 1;
                    break;
                }
                last_heal = i;
                hd = Hd - ak;
                i--;
            }
            else {
                ak = nxt_ak;
                hd -= ak;
            }
        }
        if (dead) return INF;
        last_heal = -1;
        for (int i = 0; i < n_buff; i++) {
            n_turns++;
            int nxt_ad = min(100ll, ad + B);
            if (hd - ak <= 0) {
                if (last_heal == i || Hd - ak <= 0) {
                    dead = 1;
                    break;
                }
                last_heal = i;
                hd = Hd - ak;
                i--;
            }
            else {
                ad = nxt_ad;
                hd -= ak;
            }
        }
        if (dead || ad == 0) return INF;
        last_heal = -1;
        for (int i = 0;; i++) {
            n_turns++;
            if (hk - ad <= 0) break;
            if (hd - ak <= 0) {
                if (last_heal == i || Hd - ak <= 0) {
                    dead = 1;
                    break;
                }
                last_heal = i;
                hd = Hd - ak;
                i--;
            }
            else {
                hk -= ad;
                hd -= ak;
            }
        }
        if (dead) return INF;
        return n_turns;        
    }

    string solve(int test_case) {
        out += sprintf(out, "Case #%d: ", test_case);                
        int ans = INF;
        for (int n_buff = 0; n_buff <= 100; n_buff++) {
            for (int n_debuff = 0; n_debuff <= 100; n_debuff++) {
                ans = min(ans, calc(n_buff, n_debuff));
            }
        }
        if (ans == INF) out += sprintf(out, "IMPOSSIBLE\n");
        else out += sprintf(out, "%d\n", ans);
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
