#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n, g = 0, b = 0;
    scanf("%d", &n);
    vector<string> names;
    for (int i = 0; i < n; i++) {
        char op;
        string name;
        scanf (" %c", &op);
        cin >> name;
        names.push_back(name);
        if (op == '+') g++;
        else b++;
    }
    sort(names.begin(), names.end());
    for (string s: names) cout << s << endl;
    printf("Se comportaram: %d | Nao se comportaram: %d\n", g, b);        
    return 0;
}
