#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110, DAY = 24 * 60;
const int NSEG = 4 * 7 + 2;

const int DIGIT[][7] = {
    {1, 1, 1, 0, 1, 1, 1}, // 0
    {0, 0, 1, 0, 0, 1, 0}, // 1
    {1, 0, 1, 1, 1, 0, 1}, // 2
    {1, 0, 1, 1, 0, 1, 1}, // 3
    {0, 1, 1, 1, 0, 1, 0}, // 4
    {1, 1, 0, 1, 0, 1, 1}, // 5
    {1, 1, 0, 1, 1, 1, 1}, // 6
    {1, 0, 1, 0, 0, 1, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}, // 9
    {0, 0, 0, 0, 0, 0, 0}  // null
};

const int OFF[] = {0, 5, 12, 17};

struct Digit {
    int led[7];
    void parse(const vector<string> &v, int off) {
        led[0] = (v[0][1 + off] == 'X');
        led[1] = (v[1][0 + off] == 'X');
        led[2] = (v[1][3 + off] == 'X');
        led[3] = (v[3][1 + off] == 'X');
        led[4] = (v[4][0 + off] == 'X');
        led[5] = (v[4][3 + off] == 'X');
        led[6] = (v[6][1 + off] == 'X');
    }
    void clear() {
        for (int i = 0; i < 7; i++)
            led[i] = 0;
    }
    void set(int d) {
        for (int i = 0; i < 7; i++)
            led[i] = DIGIT[d][i];
    }
    Digit() {}
    Digit(int d) { set(d); }
};

struct Time {
    Digit digit[4];
    int colon[2];
    void parse(const vector<string> &v) {
        for (int i = 0; i < 4; i++)
            digit[i].parse(v, OFF[i]);
        colon[0] = (v[2][10] == 'X');
        colon[1] = (v[4][10] == 'X');
    }
    void clear() {
        colon[0] = colon[1] = 0;
        for (int i = 0; i < 4; i++)
            digit[i].clear();
    }
    vector<int> toVector() {
        vector<int> v;
        for (int d = 0; d < 4; d++)
            for (int j = 0; j < 7; j++)
                v.push_back(digit[d].led[j]);
        v.push_back(colon[0]);
        v.push_back(colon[1]);
        return v;
    }
};

Time clocks[MAXN];

pair<int, int> pos[7][2] = {
    { {0, 1}, {0, 2} }, // 0
    { {1, 0}, {2, 0} }, // 1
    { {1, 3}, {2, 3} }, // 2
    { {3, 1}, {3, 2} }, // 3
    { {4, 0}, {5, 0} }, // 4
    { {4, 3}, {5, 3} }, // 5
    { {6, 1}, {6, 2} }  // 6
};


char ans_grid[7][22];

vector< vector<int> > display;
vector< vector<int> > whole_day;

int n;

int check(int start_time, int seg) {
    int mask = 0;
    for (int t = 0; t < n; t++) {
        int cur_time = (t + start_time) % DAY;
        if (display[t][seg] == 1) {
            mask |= (1 << 3); // not always off
            if (whole_day[cur_time][seg] == 0)
                mask |= (1 << 0); // on when should be off
        }
        else {
            mask |= (1 << 2); // not always on
            if (whole_day[cur_time][seg] == 1)
                mask |= (1 << 1); // off when should be on
        }
    }
    if ((mask & 3) == 3) return -1;
    if ((mask & 5) == 5) return -1;
    if ((mask & 10) == 10) return -1;
    int ret = 0;
    if ((mask & 3) == 0) ret |= (1 << 0);    // ok
    if (!(mask & (1 << 2))) ret |= (1 << 1); // always on
    if (!(mask & (1 << 3))) ret |= (1 << 2); // always off
    return ret;
}

char getChar(int seg, int *status) {
    if (__builtin_popcount(status[seg]) > 1) return '?';
    else if (status[seg] & (1 << 0)) return 'W';
    else if (status[seg] & (1 << 1)) return '1';
    else return '0';
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        vector<string> v;
        for (int j = 0; j < 7; j++) {
            string s;
            cin >> s;
            v.push_back(s);
        }
        clocks[i].parse(v);
        display.push_back(clocks[i].toVector());
    }

    for (int start_time = 0; start_time < DAY; start_time++) {
        int hours = start_time / 60, mins = start_time % 60;
        Time cur;
        if (hours / 10 == 0) cur.digit[0].set(10);
        else cur.digit[0].set(hours / 10);
        cur.digit[1].set(hours % 10);
        cur.digit[2].set(mins / 10);
        cur.digit[3].set(mins % 10);
        cur.colon[0] = cur.colon[1] = 1;
        whole_day.push_back(cur.toVector());        
    }

    bool found = 0;
    int status[NSEG];
    memset(status, 0, sizeof(status));
    for (int start_time = 0; start_time < DAY; start_time++) {
        bool ok = 1;
        int cur_status[4 * 7 + 2];
        memset(cur_status, 0, sizeof(cur_status));
        for (int seg = 0; seg < NSEG; seg++) {
            cur_status[seg] = check(start_time, seg);
            if (cur_status[seg] == -1) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            found = 1;
            for (int seg = 0; seg < NSEG; seg++)
                status[seg] |= cur_status[seg];
        }
    }
    
    if (!found) printf("impossible\n");
    else {
        for (int r = 0; r < 7; r++)
            for (int c = 0; c < 21; c++)
                ans_grid[r][c] = '.';
        for (int d = 0; d < 4; d++) {
            for (int j = 0; j < 7; j++) {
                char c = getChar(7*d + j, status);
                ans_grid[pos[j][0].first][pos[j][0].second + OFF[d]] = c;
                ans_grid[pos[j][1].first][pos[j][1].second + OFF[d]] = c;
            }
        }
        ans_grid[2][10] = getChar(NSEG - 2, status);
        ans_grid[4][10] = getChar(NSEG - 1, status);
        
        for (int i = 0; i < 7; i++)
            printf("%s\n", ans_grid[i]);
    }        
    return 0;
}
