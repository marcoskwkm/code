int rmq[LOG][MAXN];
int v[MAXN];
int n;

// Builds RMQ structure for array v of size n in O(n*log(n))
void build_rmq() {
    for(int i = 0; i < n; i++)
        rmq[0][i] = v[i];
    for(int log = 1; log < LOG; ++log) {
        for(int i = 0; i < n; i++) {
            rmq[log][i] = min(rmq[log-1][i], rmq[log-1][min(n-1, i + (1<<(log-1)))]);
        }
    }
}
// l e r inclusives
int get_rmq(int l,int r) {
    int len = r - l + 1;
    int bit = 31 - __builtin_clz(len);
    return min(rmq[bit][l], rmq[bit][r - (1<<bit) + 1]);
}
