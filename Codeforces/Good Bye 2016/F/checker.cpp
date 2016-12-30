#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200;

vector<int> adj[MAXN];

int main() {
    FILE *f = fopen("f.in", "r");
    int n;
    fscanf(f, "%d", &n);
    int h = n;
    n = (1 << n) - 1;
    for (int i = 1; i < n; i++) {
        int u, v;
        fscanf(f, "%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    fclose(f);
    printf("1\n");
    printf("%d\n", h);
    fflush(stdout);
    int cnt = 0;
    while (1) {
        int x;
        char op;
        scanf(" %c%d", &op, &x);
        if (op == '!') {
            fprintf(stderr, "Answer: %d (%d)\n", x, cnt);
            if (x == -1) system("cp f.in fuck.in");
            break;
        }
        else {
            cnt++;
            printf("%d\n", adj[x].size());
            for (int nxt: adj[x]) printf("%d ", nxt);
            printf("\n");
            fflush(stdout);
        }
    }
    return 0;
}
