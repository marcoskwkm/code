class UnionFind {
private:
    int pai[MAXS],rank[MAXS];
    int cnt;

public:
    UnionFind(int size) {
        for (int a = 0; a < size; ++a) {
            pai[a] = a;
            rank[a] = 0;
        }
        cnt = size;
    }
    int find(int v) { return pai[v] = (pai[v]==v) ? v:find(pai[v]); }
    void join(int i,int j) {
        int pi = find(i), pj = find(j);
        if (pi == pj) return;
        --cnt;
        if (rank[pi] > rank[pj]) pai[pj] = pi;
        else if (rank[pi] < rank[pj]) pai[pi] = pj;
        else {
            pai[pj] = pi;
            rank[pi]++;
        }
    }
    bool isConnected(int i,int j) { return find(i) == find(j); }
    int count() { return cnt; }        
};
