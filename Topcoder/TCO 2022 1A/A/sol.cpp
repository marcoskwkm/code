#include <bits/stdc++.h>
using namespace std;

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct SkyscraperReconstruction {
    vector<int> reconstruct(string visibility) {
        int n_tall = count(visibility.begin(), visibility.end(), 'O');
        int cur_height = visibility.size() - n_tall + 1;
        int cur_low = 1;
        vector<int> ans;
        for (size_t i = 0; i < visibility.size(); i++) {
            if (visibility[i] == 'O') {
                ans.push_back(cur_height++);
            } else {
                ans.push_back(cur_low++);
            }
        }
        return ans;
    }
};

#ifdef HOME
int main() { return 0; }
#endif
