#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)5e5 + 10;

struct Node {
    int pair;
    int l, r;
};

Node node[MAXN];

int main() {
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    stack<int> st;
    node[0].r = 1;
    node[n + 1].l = n;
    for (int i = 1; i <= n; i++) {
        node[i].l = i - 1;
        node[i].r = i + 1;
        char c;
        scanf(" %c", &c);
        if (c == '(') st.push(i);
        else {
            int p = st.top();
            st.pop();
            node[i].pair = p;
            node[p].pair = i;
        }
    }
    int cur = p;
    for (int i = 0; i < m; i++) {
        char op;
        scanf(" %c", &op);
        if (op == 'R') cur = node[cur].r;
        else if(op == 'L') cur = node[cur].l;
        else {
            int p = node[cur].pair;
            int l, r;
            if (p < cur) {
                l = node[p].l;
                r = node[cur].r;
            }
            else {
                l = node[cur].l;
                r = node[p].r;
            }
            node[l].r = r;
            node[r].l = l;
            if (r > n) cur = l;
            else cur = r;                
        }
    }
    cur = node[0].r;
    while(cur <= n) {
        printf("%c", node[cur].pair < cur ? ')' : '(');
        cur = node[cur].r;
    }            
    return 0;
}
