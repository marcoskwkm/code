class KMP {
private:
    string pattern;
    int len;
    
public:
    vector<int> f;
    KMP(string p) {
        pattern = p;
        len = p.size();
        f.resize(len + 2);
        f[0] = f[1] = 0;
        for (int a = 2; a <= len; ++a) {
            int now = f[a - 1];
            while (1) {
                if (p[now] == p[a - 1]) {
                    f[a] = now + 1;
                    break;
                }
                if (now == 0) {
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
        int i = 0, j = 0;
        while (j < size) {
            if (text[j] == pattern[i]) {
                ++i; ++j;
                if (i == len) {
                    ret.push_back(j - len);
                    i = f[i];                    
                }
            }
            else if (i > 0) i = f[i];
            else j++;
        }
        return ret;
    }
};
