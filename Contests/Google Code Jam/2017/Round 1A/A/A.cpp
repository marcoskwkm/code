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

    static const int MAXD = 26;
    char grid[MAXD][MAXD];
    int R, C;
    
    void readInput() {
        scanf("%d%d", &R, &C);
        for (int r = 0; r < R; r++)
            for (int c = 0; c < C; c++)
                scanf(" %c", &grid[r][c]);
    }
    
    string solve(int test_case) {
        out += sprintf(out, "Case #%d:\n", test_case);
        for (int r = 0; r < R; r++) {            
            char last = '?';
            for (int c = 0; c < C; c++) {
                if (grid[r][c] == '?')
                    grid[r][c] = last;
                else
                    last = grid[r][c];
            }
            last = '?';
            for (int c = C - 1; c >= 0; c--) {
                if (grid[r][c] == '?')
                    grid[r][c] = last;
                else
                    last = grid[r][c];
            }
        }
        for (int c = 0; c < C; c++) {
            char last = '?';
            for (int r = 0; r < R; r++) {
                if (grid[r][c] == '?')
                    grid[r][c] = last;
                else
                    last = grid[r][c];
            }
            last = '?';
            for (int r = R - 1; r >= 0; r--) {
                if (grid[r][c] == '?')
                    grid[r][c] = last;
                else
                    last = grid[r][c];
            }
        }        
        
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++)
                out += sprintf(out, "%c", grid[r][c]);
            out += sprintf(out, "\n");
        }
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
