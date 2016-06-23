#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;
typedef pair<string, int> psi;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    priority_queue<int> pq;
    int n;
    vector<psi> ans;
    char buff[20];
    for (scanf("%d", &n); n--;) {
        int res;
        scanf(" %s", buff);
        if (buff[0] == 'i') {
            scanf("%d", &res);
            pq.push(-res);
            ans.push_back(psi("insert", res));
        }
        else if (buff[0] == 'r') {
            ans.push_back(psi("removeMin", -1));
            pq.pop();
        }
        else {
            scanf("%d", &res);
            while (!pq.empty() && -pq.top() < res) {
                ans.push_back(psi("removeMin", -1));
                pq.pop();
            }
            if (pq.empty() || -pq.top() != res) {
                ans.push_back(psi("insert", res));
            }
            ans.push_back(psi("getMin", res));
        }
    }
    printf("%d\n", (int)ans.size());
    for (const psi &p: ans) {
        printf("%s", p.first.c_str());
        if (p.first[0] != 'r') printf(" %d", p.second);
        printf("\n");
    }
    return 0;
}
