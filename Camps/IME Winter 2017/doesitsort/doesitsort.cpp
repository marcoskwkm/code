#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

bool check(const vector<int> &v, const vector<tiii> &ops) {
    vector<int> vv = v;
    for (tiii op: ops) {
        int k, l, r;
        tie(k, l, r) = op;
        if (k == 0) sort(vv.begin() + l, vv.begin() + r + 1);
        else if (vv[l] > vv[r]) swap(vv[l], vv[r]);
    }
    for (int i = 0; i < 19; i++)
        if (vv[i] > vv[i + 1])
            return 0;
    return 1;
}

int main() {
    clock_t tt = clock();
    int n;
    scanf("%d", &n);
    vector<tiii> ops;
    for (int i = 0; i < n; i++) {
        string f;
        int l, r;
        cin >> f >> l >> r;
        if (f == "sort")
            ops.push_back(tiii(0, l, r - 1));
        else
            ops.push_back(tiii(1, l, r));
    }
    vector<int> v;
    for (int i = 0; i < 20; i++)
        v.push_back(i);
    for (int i = 0; i < 20; i++) {
        for (int j = i + 1; j < 20; j++) {
            swap(v[i], v[j]);
            if (!check(v, ops)) {
                printf("incorrect\n");
                for (int x: v) printf("%d ", x);
                printf("\n");
                return 0;
            }
            swap(v[i], v[j]);
        }
    }
    for (int s = 0; s < 200000; s++) {
        random_shuffle(v.begin(), v.end());
        vector<int> vv = v;
        for (tiii op: ops) {
            int k, l, r;
            tie(k, l, r) = op;
            if (k == 0) sort(vv.begin() + l, vv.begin() + r + 1);
            else if (vv[l] > vv[r]) swap(vv[l], vv[r]);
        }
        bool ok = 1;
        for (int i = 0; i < 18; i++)
            if (vv[i] > vv[i + 1])
                ok = 0;
        if (!ok) {
            printf("incorrect\n");
            for (int x: v) printf("%d ", x);
            printf("\n");
            return 0;
        }
    }
    printf("correct\n");    
    return 0;
}
