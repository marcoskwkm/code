#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class KMP {
private:
    string pattern;
    int len;
public:
    vector<int> f;
    KMP(string p) {
        pattern = p;
        len = p.size();
        f.resize(len+2);
        f[0] = f[1] = 0;
        for(int a=2;a<=len;++a) {
            int now = f[a-1];
            while(1) {
                if(p[now] == p[a-1]) {
                    f[a] = now+1;
                    break;
                }
                if(now==0) {
                    f[a] = 0;
                    break;
                }
                now = f[now];
            }
        }
    }
    //returns a vector of indices with the beginning of each match
    vector<int> match(string text) {
        vector<int> ret;
        int size = text.size();
        int i=0,j=0;
        while(j<size) {
            if(text[j] == pattern[i]) {
                ++i; ++j;
                if(i==len) {
                    ret.push_back(j-len);
                    i = f[i];                    
                }
            }
            else if(i>0) i = f[i];
            else j++;
        }
        return ret;
    }
};

pair<string, string> read_song() {
    string p;
    getline(cin, p);
    if (p == "EOF") return make_pair(p, "");
    string song = "";
    while (1) {
        string line;
        getline(cin, line);
        if (line == "") break;
        song += line;
    }
    return make_pair(p, song);
}

int get_count(string &p, string &song) {
    KMP kmp(p);
    return kmp.match(song).size();
}

int main() {
    while (1) {
        string p, song;
        tie(p, song) = read_song();
        if (p == "EOF") break;
        
        int best = get_count(p, song), ans = -1;
        int n;
        scanf("%d", &n);
        getline(cin, p);
        for (int i = 1; i <= n; i++) {
            string pp, ssong;
            tie(pp, ssong) = read_song();
            // printf("pp = %s, song = %s\n", pp.c_str(), ssong.c_str());
            int cnt = get_count(pp, ssong);
            // printf("got %d\n", cnt);
            if (cnt > best) {
                best = cnt;
                ans = i;
            }
        }
        printf("%d\n", ans);
    }            
    return 0;
}
