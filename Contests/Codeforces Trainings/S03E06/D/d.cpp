#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int knight_dc[] = {-1, 1, 2, 2, 1, -1, -2, -2};
int knight_dr[] = {2, 2, 1, -1, -2, -2, -1, 1};
vector<int> bishop_dc, bishop_dr;
vector<pii> bishop_d = {pii(1, 1), pii(1, -1), pii(-1, 1), pii(-1, -1)};

int attacked[10][10];

pii parse(string s) {
    int r = s[0] - 'a';
    int c = s[1] - '1';
    return pii(r, c);
}

bool valid(int r, int c) {
    return r >= 0 && c >= 0 && r < 8 && c < 8;
}

void mark_attacked(pii king, pii knight, pii bishop) {
    memset(attacked, 0, sizeof(attacked));
    int rk, ck;
    tie(rk, ck) = king;
    for (int dr = -1; dr <= 1; dr++)
        for (int dc = -1; dc <= 1; dc++)
            if (valid(rk + dr, ck + dc))
                attacked[rk + dr][ck + dc] = 1;

    int rn, cn;
    tie(rn, cn) = knight;
    for (int i = 0; i < 8; i++) {
        int nr = rn + knight_dr[i], nc = cn + knight_dc[i];
        if (valid(nr, nc)) attacked[nr][nc] = 1;
    }

    int rb, cb;
    tie(rb, cb) = bishop;
    // for (int i = 0; i < (int)bishop_dc.size(); i++) {
    //     int nr = rb + bishop_dr[i], nc = cb + bishop_dc[i];
    //     if (valid(nr, nc)) {
    //         attacked[nr][nc] = 1;
    //     }
    // }
    for (pii p: bishop_d) {
        int dr, dc;
        tie(dr, dc) = p;
        for (int i = 1; i < 10; i++) {
            int nr = rb + dr * i, nc = cb + dc * i;
            if (!valid(nr, nc)) break;
            attacked[nr][nc] = 1;
            if (pii(nr, nc) == king || pii(nr, nc) == knight) break;
        }
    }
}

bool is_checkmated(pii king) {
    int r, c;
    tie(r, c) = king;
    if (!attacked[r][c]) return 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (!valid(r + dr, c + dc)) continue;
            if (!attacked[r + dr][c + dc]) return 0;
        }
    }
    return 1;
}            

int main() {
    for (int i = 1; i <= 8; i++) {
        bishop_dc.push_back(i);
        bishop_dr.push_back(i);
        
        bishop_dc.push_back(i);
        bishop_dr.push_back(-i);

        bishop_dc.push_back(-i);
        bishop_dr.push_back(i);

        bishop_dc.push_back(-i);
        bishop_dr.push_back(-i);
    }

    string wking, wbishop, wknight;
    cin >> wking >> wbishop >> wknight;
    
    string bking;
    cin >> bking;

    pii wK = parse(wking), wN = parse(wknight);
    pii wB = parse(wbishop), bK = parse(bking);

    // moving knight
    for (int i = 0; i < 8; i++) {
        int nr = wN.first + knight_dr[i], nc = wN.second + knight_dc[i];
        if (!valid(nr, nc)) continue;
        if (pii(nr, nc) == wK || pii(nr, nc) == wB || pii(nr, nc) == bK)
            continue;
        mark_attacked(wK, pii(nr, nc), wB);
        // printf("Knight at (%d, %d):\n", nr, nc);
        // for (int r = 0; r < 8; r++) {
        //     for (int c = 0; c < 8; c++) {
        //         printf("%d ", attacked[r][c]);
        //     }
        //     printf("\n");
        // }
        if (is_checkmated(bK)) {
            printf("N%c%d\n", 'a' + nr, nc + 1);
            return 0;
        }
    }

    // moving bishop
    for (pii p: bishop_d) {
        int dr, dc;
        tie(dr, dc) = p;
        for (int i = 1; i < 10; i++) {
            int nr = wB.first + dr * i, nc = wB.second + dc * i;
            if (!valid(nr, nc)) break;
            if (pii(nr, nc) == wK || pii(nr, nc) == wN || pii(nr, nc) == bK) break;
            mark_attacked(wK, wN, pii(nr, nc));
            if (is_checkmated(bK)) {
                printf("B%c%d\n", 'a' + nr, nc + 1);
                return 0;
            }            
        }
    }

    // moving king
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            int nr = wK.first + dr, nc = wK.second + dc;
            if (!valid(nr, nc)) continue;
            if (pii(nr, nc) == wB || pii(nr, nc) == wN) continue;
            if (abs(nr - bK.first) <= 1 && abs(nc - bK.second) <= 1) continue;
            mark_attacked(pii(nr, nc), wN, wB);
            if (is_checkmated(bK)) {
                printf("K%c%d\n", 'a' + nr, nc + 1);
                return 0;
            }
        }
    }
    
    printf("impossible\n");
    return 0;
}
