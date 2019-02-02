#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

// struct KMP {
//     string pattern;
//     int len;
//     vector<int> f;

//     KMP(string p) {
//         pattern = p;
//         len = p.size();
//         f.resize(len + 2);
//         f[0] = f[1] = 0;
//         for (int i = 2; i <= len; i++) {
//             int now = f[i - 1];
//             while (1) {
//                 if (p[now] == p[i - 1]) {
//                     f[i] = now + 1;
//                     break;
//                 }
//                 if (now == 0) {
//                     f[i] = 0;
//                     break;
//                 }
//                 now = f[now];
//             }
//         }
//     }

//     bool match(const string &text) {
//         vector<int> ret;
//         int size = text.size();
//         int i = 0, j = 0;
//         while (j < size) {
//             if (text[j] == pattern[i]) {
//                 i++; j++;
//                 if (i == len) {
//                     return 1;
//                 }
//             }
//             else if (i > 0) i = f[i];
//             else j++;
//         }
//         return 0;
//     }
// };

bool contains(const string &text, const string &s) {
    if (text.size() < s.size()) return 0;
    for (int i = 0; i <= text.size() - s.size(); i++)
        if (text.substr(i, s.size()) == s)
            return 1;
    return 0;
}

vector<string> v;
string go(int len) {
    for (lint m = 0; m < (1LL << len); m++) {
        string cand = "";
        for (int i = 0; i < len; i++) {
            if (m & (1LL << i)) cand += '1';
            else cand += '0';
        }
        bool ok = 1;
        for (auto &s: v) {
            if (!contains(cand, s)) {
                ok = 0;
                break;
            }
        }
        if (ok) return cand;
    }
    return "";
}

int main() {
    int n;
    cin >> n;
    for (int m = 0; m < (1 << n); m++) {
        string s = "";
        for (int j = 0; j < n; j++) {
            if (m & (1 << j))
                s += '1';
            else
                s += '0';
        }
        v.push_back(s);
    }

    for (int len = 1;; len++) {
        string sol = go(len);
        if (sol != "") {
            printf("Optimal length: %d\n", (int)sol.size());
            printf("%s\n", sol.c_str());
            break;
        }
    }
    return 0;
}
