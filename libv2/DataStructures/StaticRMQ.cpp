namespace RMQ {
    template<class T> struct min {
        T operator() (T a, T b) { return std::min(a, b); }
    };

    template<class T> struct max {
        T operator() (T a, T b) { return std::max(a, b); }
    };

    // Static RMQ structure.
    // Builds in O(NlogN) and computes queries in O(1).
    template<class T, class Agg = min<T>> struct StaticRMQ {
        Agg agg = Agg();
        vector<vector<T>> rmq;
        int N, K;

        StaticRMQ(const vector<T> &v) {
            N = v.size();
            K = 32 - __builtin_clz(N);
            rmq = vector<vector<T>>(K);

            for (int i = 0; i < K; i++)
                rmq[i].resize(N);
            for (int i = 0; i < N; i++)
                rmq[0][i] = v[i];
            for (int k = 1; k < K; k++)
                for (int i = 0; i < N; i++)
                    rmq[k][i] = agg(rmq[k - 1][i], rmq[k - 1][std::min(N - 1, i + (1 << (k - 1)))]);
        }

        T get(int l, int r) {
            int k = 31 - __builtin_clz(r - l + 1);
            return agg(rmq[k][l], rmq[k][r - (1 << k) + 1]);
        }
    };
}
