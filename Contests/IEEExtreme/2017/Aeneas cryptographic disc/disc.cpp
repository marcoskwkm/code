#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0);

double get_length(double a1, double a2, double r) {
    a1 *= PI / 180;
    a2 *= PI / 180;
    return sqrt(2*r*r*(1 - cos(a2 - a1)));
}

int main() {
    double R;
    cin >> R;
    map<char, double> alpha;
    for (int i = 0; i < 26; i++) {
        char c;
        double a;
        scanf(" %c%lf", &c, &a);
        alpha[c] = a;
    }
    double ans = R;
    string line;
    getline(cin, line);
    getline(cin, line);
    char prv = 0;
    for (char c: line) {
        if (!isalpha(c)) continue;
        c = toupper(c);
        if (prv != 0) ans += get_length(alpha[prv], alpha[c], R);
        prv = c;
    }
    printf("%d\n", (int)ceil(ans));        
    return 0;
}
