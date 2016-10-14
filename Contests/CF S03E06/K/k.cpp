#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXL = 300;

bool is_upd(string s) {
    for (char c: s)
        if (c == ' ')
            return 1;
    return 0;
}

double get_time(const char *str) {
    double h, m, s;
    sscanf(str, "%lf:%lf:%lf", &h, &m, &s);
    return h + m/60 + s/60/60;
}

int main() {
    string line;
    double total = 0;
    double last_t = 0, last_v = 0;
    while (getline(cin, line)) {
        if (is_upd(line)) {
            char t[MAXL];
            double val;
            sscanf(line.c_str(), " %s %lf", t, &val);
            double cur_t = get_time(t);
            total += (cur_t - last_t) * last_v;
            last_t = cur_t;
            last_v = val;
        }
        else {
            double cur_t = get_time(line.c_str());
            printf("%s %.2f km\n", line.c_str(), total + (cur_t - last_t) * last_v);
        }
    }            
    return 0;
}
