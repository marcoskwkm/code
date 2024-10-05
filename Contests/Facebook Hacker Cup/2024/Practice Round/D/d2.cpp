#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define read_array(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int BSIZE = 550;

template<class Fun> class y_combinator_result {
    Fun fun_;

  public:
    template<class T> explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}

    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return fun_(ref(*this), forward<Args>(args)...);
    }
};

template<class Fun> decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
}

template<class T = int> inline T read() {
    T x;
    cin >> x;
    return x;
}

template<class T> inline vector<T> read_vector(int n) {
    vector<T> v(n);
    read_array(v, n);
    return v;
}

template<class T> vector<T> make_vector(size_t size, T initialValue) {
    return vector<T>(size, initialValue);
}

template<class T, class... Args> auto make_vector(size_t head, Args &&...rem) {
    auto inner = make_vector<T>(rem...);
    return vector<decltype(inner)>(head, inner);
}

template<class T, class C = vector<T>> inline void print_array(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? "" : " ");
    }
    cout << '\n';
}

struct Bucket {
    int diff;
    vector<int> v;
    Bucket() : diff(0) {}
};

void rebuild_buckets(vector<Bucket> &buckets) {
    vector<Bucket> new_buckets;
 
    Bucket cur_bucket;

    for (const auto &bucket : buckets) {
        for (int x: bucket.v) {
            cur_bucket.v.push_back(x + bucket.diff);
            if (cur_bucket.v.size() == BSIZE) {
                new_buckets.push_back(cur_bucket);
                cur_bucket = Bucket();
            }
        }
    }

    if (cur_bucket.v.size() > 0) {
        new_buckets.push_back(cur_bucket);
    }

    buckets = new_buckets;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int N, G;
        cin >> N >> G;
        vector<Bucket> buckets;
        buckets.emplace_back();
        buckets[0].v.push_back(INF);
        
        for (int i = 0; i < N; i++) {
            int E;
            cin >> E;

            int cur = 0, cnt = 0;
            while (E + cnt + buckets[cur].v.size() - 1 >= buckets[cur].v.back() + buckets[cur].diff) {
                buckets[cur].diff--;
                cnt += buckets[cur].v.size();
                cur++;
            }

            for (auto it = buckets[cur].v.begin(); it != buckets[cur].v.end(); it++) {
                if (E + cnt >= (*it) + buckets[cur].diff) {
                    (*it)--;
                    cnt++;
                } else {                    
                    buckets[cur].v.insert(it, E + cnt - buckets[cur].diff);
                    break;
                }
            }

            if (i % BSIZE == BSIZE - 1) {
                rebuild_buckets(buckets);
            }
        }

        int best = -1, min_dist = INF;
        int cnt = 0;
        for (const auto &bucket : buckets) {
            for (int x: bucket.v) {
                int real_x = x + bucket.diff;
                int dist = abs(G - real_x);
                if (dist <= min_dist) {
                    min_dist = dist;
                    best = N - cnt;
                }
                cnt++;
            }
        }

        printf("Case #%d: %d %d\n", t, best, min_dist);
    }
    return 0;
}
