struct KMP {
    string pattern;
    int len;
    // f[i] = the size of longest preffix that is a suffix of p[0..i-1]    
    vector<int> f;
    
    KMP(string p) {
        pattern = p;
        len = p.size();
        f.resize(len + 2);
        f[0] = f[1] = 0;
        for (int i = 2; i <= len; i++) {
            int now = f[i - 1];
            while (1) {
                if (p[now] == p[i - 1]) {
                    f[i] = now + 1;
                    break;
                }
                if (now == 0) {
                    f[i] = 0;
                    break;
                }
                now = f[now];
            }
        }
    }
    
    // returns a vector of indices with the beginning of each match
    vector<int> match(string text) {
        vector<int> ret;
        int size = text.size();
        int i = 0, j = 0;
        while (j < size) {
            if (text[j] == pattern[i]) {
                i++; j++;
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
