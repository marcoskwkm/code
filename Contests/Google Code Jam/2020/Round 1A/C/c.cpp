#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

struct Node {
    int s;
    bool out;
    Node *up, *down, *left, *right;
};

Node border;
Node nodes[MAXN];

int node_cnt;
Node* newNode(int s) {
    nodes[node_cnt].s = s;
    nodes[node_cnt].out = 0;
    return &nodes[node_cnt++];
}

Node* q[2][MAXN];
int len[2];

bool isOut(Node *competitor) {
    if (competitor->out) return 0;

    int multiplier = 0, sum = 0;
    if (competitor->up != &border) {
        multiplier++;
        sum += competitor->up->s;
    }
    if (competitor->down != &border) {
        multiplier++;
        sum += competitor->down->s;
    }
    if (competitor->left != &border) {
        multiplier++;
        sum += competitor->left->s;
    }
    if (competitor->right != &border) {
        multiplier++;
        sum += competitor->right->s;
    }

    return multiplier * competitor->s < sum;
}

int main() {
    int t = 1, T;
    border.s = 0;
    border.out = 1;
    for (cin >> T; t <= T; t++) {
        node_cnt = 0;

        int R, C;
        cin >> R >> C;

        vector<vector<Node*>> competitors(R);
        lint sumActive = 0;
        for (int r = 0; r < R; r++) {
            competitors[r].resize(C);
            for (int c = 0; c < C; c++) {
                int s;
                scanf("%d", &s);
                competitors[r][c] = newNode(s);
                sumActive += s;
            }
        }

        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                competitors[r][c]->up = (r == 0 ? &border : competitors[r - 1][c]);
                competitors[r][c]->down = (r + 1 == R ? &border : competitors[r + 1][c]);
                competitors[r][c]->left = (c == 0 ? &border : competitors[r][c - 1]);
                competitors[r][c]->right = (c + 1 == C ? &border : competitors[r][c + 1]);
            }
        }

        int cur = 0, nxt = 1;
        len[cur] = len[nxt] = 0;

        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (isOut(competitors[r][c])) {
                    q[cur][len[cur]++] = competitors[r][c];
                    competitors[r][c]->out = 1;
                }
            }
        }

        lint ans = 0;
        while (1) {
            ans += sumActive;
            if (len[cur] == 0) break;

            // printf("new round\n");
            for (int i = 0; i < len[cur]; i++) {
                // printf("%d is out\n", q[cur][i]->s);
                sumActive -= q[cur][i]->s;

                q[cur][i]->up->down = q[cur][i]->down;
                q[cur][i]->down->up = q[cur][i]->up;
                q[cur][i]->left->right = q[cur][i]->right;
                q[cur][i]->right->left = q[cur][i]->left;
            }

            for (int i = 0; i < len[cur]; i++) {
                if (isOut(q[cur][i]->up)) {
                    q[cur][i]->up->out = 1;
                    q[nxt][len[nxt]++] = q[cur][i]->up;
                }
                if (isOut(q[cur][i]->down)) {
                    q[cur][i]->down->out = 1;
                    q[nxt][len[nxt]++] = q[cur][i]->down;
                }
                if (isOut(q[cur][i]->left)) {
                    q[cur][i]->left->out = 1;
                    q[nxt][len[nxt]++] = q[cur][i]->left;
                }
                if (isOut(q[cur][i]->right)) {
                    q[cur][i]->right->out = 1;
                    q[nxt][len[nxt]++] = q[cur][i]->right;
                }
            }

            cur ^= 1;
            nxt ^= 1;
            len[nxt] = 0;
        }

        printf("Case #%d: %lld\n", t, ans);
    }

    return 0;
}
