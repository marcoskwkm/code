#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXC = 20;

vector<string> names[MAXC];
int avail[MAXC][30];

int main() {
    int c;
    scanf("%d", &c);
    map<string, int> id;
    memset(avail, -1, sizeof(avail));
    for (int i = 0; i < c; i++) {
        string name;
        int n;
        cin >> name >> n;
        id[name] = i;
        for (int j = 0; j < n; j++) {
            string schedule;
            string room_name;
            cin >> schedule >> room_name;
            names[i].push_back(room_name);
            for (int h = 0; h < 24; h++)
                if (schedule[h] == '.')
                    avail[i][h] = j;
        }
    }
    int q;
    for (scanf("%d", &q); q--;) {
        int n;
        scanf("%d", &n);
        vector<int> ids;
        for (int i = 0; i < n; i++) {
            string name;
            cin >> name;
            ids.push_back(id[name]);
        }
        bool ok = 0;
        for (int h = 0; h < 24; h++) {
            bool found = 1;
            for (int i = 0; i < n; i++) {
                if (avail[ids[i]][h] == -1) {
                    found = 0;
                    break;
                }
            }
            if (found) {
                ok = 1;
                printf("Yes");
                for (int i = 0; i < n; i++)
                    printf(" %s", names[ids[i]][avail[ids[i]][h]].c_str());
                printf("\n");
                break;
            }
        }
        if (!ok) printf("No\n");
    }        
    return 0;
}
