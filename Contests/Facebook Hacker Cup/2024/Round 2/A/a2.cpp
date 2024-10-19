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

vector<__int128> peaks;

struct TestCase {
    lint A, B, M;

    void read_input() { cin >> A >> B >> M; }

    void solve(stringstream &out, int case_id) {
        lint ans = 0;
        for (const auto &x: peaks) {
            if (x % M == 0 && A <= x && x <= B)
                ans++;
            else if (x > B)
                break;
        }
        out << "Case #" << case_id + 1 << ": " << ans << '\n';
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

const int MAXD = 8;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<vector<__int128>> prefs(10);
    auto gen = [&](this const auto &f, __int128 pref, int len) {
        prefs[len].push_back(pref);
        if (len == MAXD) return;
        for (int d = pref % 10; d <= 8; d++) {
            f(10 * pref + d, len + 1);
        }
    };

    for (int d = 1; d <= 9; d++) {
        peaks.push_back(d);
        gen(d, 1);
    }

    __int128 m = 10;
    for (int s = 1; s <= MAXD; s++) {
        for (auto b: prefs[s]) {
            int bf = b % 10;
            __int128 rev = 0;
            while (b) {
                rev = 10 * rev + b % 10;
                b /= 10;
            }
            for (auto a: prefs[s]) {
                int d = max<int>(a % 10, bf);
                for (int c = d + 1; c <= 9; c++) {
                    peaks.push_back(10 * m * a + m * c + rev);
                }
            }
        }
        m *= 10;
    }

    debug("size = %d\n", (int)peaks.size());
    sort(peaks.begin(), peaks.end());

    int T;
    cin >> T;
    MultiThreadSolver solver(T);
    solver.run();
    return 0;
}
