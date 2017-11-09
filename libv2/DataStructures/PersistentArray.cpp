template<class T> struct PersistentArray {
    vector<vector<pair<int, T>>> v;
    int n;

    PersistentArray(const vector<T> &_v) : n(_v.size()) {
        for (int i = 0; i < n; i++)
            v.push_back({make_pair(0, _v[i])});
    }

    int update(int pos, const T &val) {
        static int cur_ver = 1;
        v[pos].push_back(make_pair(cur_ver, val));
        return cur_ver++;
    }

    T query(int pos, int ver) const {
        int l = 0, r = v[pos].size() - 1;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (v[pos][mid].first <= ver) l = mid;
            else r = mid - 1;
        }
        return v[pos][l].second;
    }
};
