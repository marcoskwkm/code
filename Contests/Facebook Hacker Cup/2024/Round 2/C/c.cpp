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

template<class T = int>
inline T read() {
    T x;
    cin >> x;
    return x;
}

template<class T>
inline vector<T> read_vector(int n) {
    vector<T> v(n);
    read_array(v, n);
    return v;
}

template<class T>
vector<T> make_vector(size_t size, T initialValue) {
    return vector<T>(size, initialValue);
}

template<class T, class... Args>
auto make_vector(size_t head, Args &&...rem) {
    auto inner = make_vector<T>(rem...);
    return vector<decltype(inner)>(head, inner);
}

template<class T, class C = vector<T>>
inline void print_array(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? "" : " ");
    }
    cout << '\n';
}

struct TestCase {
    lint R, C, M;
    vector<tiii> nodes;

    void read_input() {
        cin >> R >> C >> M;
        for (int r = 1; r <= R; r++) {
            for (int c = 1; c <= C; c++) {
                int x;
                cin >> x;
                nodes.emplace_back(x, r, c);
            }
        }
    }

    void solve(stringstream &out, int case_id) {
        sort(nodes.begin(), nodes.end());

        auto count = [&](lint k) {
            lint ret = 0;
            auto bit = make_vector<lint>(R + 10, C + 10, 0ll);

            auto cnt = [&](int r, int c) {
                lint sum = 0;
                for (int i = r; i > 0; i -= i & -i) {
                    for (int j = c; j > 0; j -= j & -j) {
                        sum += bit[i][j];
                    }
                }
                return sum;
            };

            auto add = [&](int r, int c, int x) {
                for (int i = r; i <= R; i += i & -i) {
                    for (int j = c; j <= C; j += j & -j) {
                        bit[i][j] += x;
                    }
                }
            };

            for (int i = 0, j; i < (int)nodes.size();) {
                for (j = i; j < (int)nodes.size() && get<0>(nodes[j]) == get<0>(nodes[i]); j++) {
                    auto [x, r, c] = nodes[j];
                    lint hr = min<lint>(r + k, R), hc = min<lint>(c + k, C);
                    lint lr = max<lint>(r - k - 1, 0), lc = max<lint>(c - k - 1, 0);
                    lint got = (cnt(hr, hc) - cnt(hr, lc) - cnt(lr, hc) + cnt(lr, lc));

                    ret += 2 * got;
                }
                while (i < j) {
                    auto [xx, rr, cc] = nodes[i];
                    add(rr, cc, 1);
                    i++;
                }
            }

            return ret;
        };

        lint l = 0, r = R * R * C * C;
        while (l < r) {
            lint m = (l + r) / 2;
            if (count(m) >= M)
                r = m;
            else
                l = m + 1;
        }

        out << "Case #" << case_id + 1 << ": " << l << '\n';
    }
};

struct MultiThreadSolver {
    vector<thread> workers;
    mutex m;
    int n_cases, n_threads;
    vector<stringstream> outputs;
    int cur_idx = 0;

    MultiThreadSolver(int cases, int threads = 8) : n_cases(cases), n_threads(threads) {
        outputs.resize(cases);
    }

    void run() {
        for (int i = 0; i < n_threads; i++) {
            workers.emplace_back(&MultiThreadSolver::work, this);
        }
        for (auto &worker: workers) {
            worker.join();
        }
        for (int i = 0; i < n_cases; i++) {
            cout << outputs[i].str();
        }
    }

    void work() {
        while (1) {
            m.lock();
            if (cur_idx == n_cases) {
                m.unlock();
                break;
            }
            int idx = cur_idx++;
            TestCase tc;
            tc.read_input();
            m.unlock();
            debug("Case %d/%d...\r", idx + 1, n_cases);
            tc.solve(outputs[idx], idx);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    MultiThreadSolver solver(read());
    solver.run();

    return 0;
}
