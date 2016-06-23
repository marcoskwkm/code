#include <bits/stdc++.h>
using namespace std;

typedef vector< vector<int> > Letter;

const string alphabet = "abcdegijklmnopqrstuvwyz";

Letter letters[30];

int get(const Letter &l1, const Letter &l2) {
    int ret = 0x3f3f3f3f;
    for (int dr = -10; dr <= 10; dr++) {
        for (int dc = -10; dc <= 10; dc++) {
            int total = 0;
            for (int r = 0; r < 70; r++) {
                int r2 = r + dr;
                if (r2 < 0 || r2 >= 70) continue;
                for (int c = 0; c < 100; c++) {
                    int c2 = c + dc;
                    if (c2 < 0 || c2 >= 70) continue;
                    total += (l2[r2][c2] - l1[r][c])*(l2[r2][c2] - l1[r][c]);
                }
            }
            ret = min(ret, total);
        }
    }
    return ret;
}

int main() {
    FILE *f = fopen("alphabet/all.in", "r");
    for (int i = 0; i < 23; i++) {
        for (int l = 0; l < 70; l++) {
            vector<int> line;
            for (int c = 0; c < 100; c++) {
                int x;
                fscanf(f, "%d", &x);
                line.push_back(x);
            }
            letters[i].push_back(line);
        }
    }
    fclose(f);

    char buff[10];
    for (int t = 1; t <= 800; t++) {
        fprintf(stderr, "t = %03d...\n", t);
        sprintf(buff, "%03d", t);
        string file(buff);
        file = "l1/" + file + ".in";
        f = fopen(file.c_str(), "r");
        Letter test[10];
        for (int line = 0; line < 70; line++) {
            for (int letter = 0; letter < 6; letter++) {
                vector<int> l;
                for (int c = 0; c < 100; c++) {
                    int x;
                    fscanf(f, "%d", &x);
                    l.push_back(x);
                }
                test[letter].push_back(l);
            }
        }
        for (int letter = 0; letter < 6; letter++) {
            int best = 0x3f3f3f3f;
            char c = '?';
            // printf("letter %d...\n", letter);
            for (int k = 0; k < 23; k++) {
                int got = get(test[letter], letters[k]);
                // printf("%c: got = %d\n", alphabet[k], got);
                if (got < best) {
                    best = got;
                    c = alphabet[k];
                }
            }
            fprintf(stderr, "%c", c);
            printf("%c", c);
        }
        fprintf(stderr, "\n");
        printf("\n");
        fclose(f);
    }
    return 0;
}
