inline void read(int &n) {
    char c = getchar_unlocked();
    while(c==9||c==10||c==32) c=getchar_unlocked();
    bool neg = (c=='-');
    n= (neg ? 0 : c-'0');
    c=getchar_unlocked();
    while('0'<=c  && c<='9') {
        n = (n<<1) + (n<<3) + c-'0';
        c = getchar_unlocked();
    }
    if(neg) n = -n;
}
