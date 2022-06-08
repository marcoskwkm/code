#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr, x)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

template<class FTYPE> struct FlowGraph {
    struct Edge {
        int v;
        FTYPE cap;
        Edge(int _v, FTYPE _cap) : v(_v), cap(_cap) {}
    };

    int V;
    vector<Edge> edges;
    vector<vector<int>> adj;

    FlowGraph(int _V) : V(_V) { adj.resize(V); }

    void add_edge(int u, int v, FTYPE cap) {
        adj[u].push_back(edges.size());
        edges.push_back(Edge(v, cap));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(u, 0));
    }
};

template<class FTYPE> struct Dinic {
    vector<int> ptr, dist;
    FlowGraph<FTYPE> &g;

    Dinic(FlowGraph<FTYPE> &_g) : g(_g) {
        ptr.resize(g.V);
        dist.resize(g.V);
    }

    bool bfs(int s, int t) {
        fill(dist.begin(), dist.end(), -1);
        dist[s] = 0;
        queue<int> q({s});
        while (!q.empty()) {
            int v = q.front();
            if (dist[v] == dist[t])
                break;
            q.pop();
            for (int i: g.adj[v]) {
                int nxt = g.edges[i].v;
                if (dist[nxt] == -1 && g.edges[i].cap) {
                    dist[nxt] = dist[v] + 1;
                    q.push(nxt);
                }
            }
        }
        return dist[t] != -1;
    }

    FTYPE dfs(int v, int t, FTYPE flow) {
        if (v == t)
            return flow;
        for (int &p = ptr[v]; p < (int)g.adj[v].size(); p++) {
            int i = g.adj[v][p];
            int nxt = g.edges[i].v;
            if (dist[nxt] == dist[v] + 1 && g.edges[i].cap) {
                FTYPE got = dfs(nxt, t, min(flow, g.edges[i].cap));
                if (got) {
                    g.edges[i].cap -= got;
                    g.edges[i ^ 1].cap += got;
                    return got;
                }
            }
        }
        return 0;
    }

    FTYPE max_flow(int s, int t) {
        FTYPE ret = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (FTYPE got = dfs(s, t, numeric_limits<FTYPE>::max()))
                ret += got;
        }
        return ret;
    }
};

vector<int> find_vertex_cover(FlowGraph<int> &g, int s, int t) {
    Dinic<int> dinic(g);
    vector<bool> seen(g.V);
    queue<int> q;
    dinic.max_flow(s, t);

    for (int idx: g.adj[s]) {
        if (g.edges[idx].cap > 0) {
            q.push(g.edges[idx].v);
            seen[g.edges[idx].v] = 1;
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int idx: g.adj[v]) {
            int nxt = g.edges[idx].v;
            if (g.edges[idx].cap == 0 || nxt == s || nxt == t || seen[nxt]) {
                continue;
            }
            seen[nxt] = 1;
            q.push(nxt);
        }
    }

    vector<int> cover;
    for (int idx: g.adj[s]) {
        if (!seen[g.edges[idx].v]) {
            cover.push_back(g.edges[idx].v);
        }
    }
    for (int idx: g.adj[t]) {
        if (seen[g.edges[idx].v]) {
            cover.push_back(g.edges[idx].v);
        }
    }

    return cover;
}

struct Potatoes {
    vector<string> plant(vector<string> field, int N);
};

vector<string> Potatoes::plant(vector<string> field, int N) {
    int n = field.size();
    int m = field[0].size();

    FlowGraph<int> g(n * m + 2);

    int s = n * m, t = n * m + 1;

    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};

    int n_vertices = 0;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (field[r][c] == '#') {
                continue;
            }
            n_vertices++;

            if ((r + c) & 1) {
                g.add_edge(s, r * m + c, 1);
            } else {
                g.add_edge(r * m + c, t, 1);
            }

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i], nc = c + dc[i];
                if (nr < 0 || nc < 0 || nr >= n || nc >= m || field[nr][nc] == '#') {
                    continue;
                }
                if ((r + c) & 1) {
                    g.add_edge(r * m + c, nr * m + nc, 1);
                }
            }
        }
    }

    auto cover = find_vertex_cover(g, s, t);
    if (n_vertices - (int)cover.size() < N) {
        return vector<string>();
    }

    vector<bool> in_cover(n * m);
    for (int v: cover) {
        in_cover[v] = 1;
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (field[r][c] == '#' || in_cover[r * m + c]) {
                continue;
            }
            if (N > 0) {
                N--;
                field[r][c] = 'P';
            }
        }
    }

    return field;
}

// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
using std::string;
using std::vector;
int run_test_case(int);
void run_test(int casenum = -1, bool quiet = false) {
    if (casenum != -1) {
        if (run_test_case(casenum) == -1 && !quiet) {
            std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
        }
        return;
    }

    int correct = 0, total = 0;
    for (int i = 0;; ++i) {
        int x = run_test_case(i);
        if (x == -1) {
            if (i >= 100)
                break;
            continue;
        }
        correct += x;
        ++total;
    }

    if (total == 0) {
        std::cerr << "No test cases run." << std::endl;
    } else if (correct < total) {
        std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")."
                  << std::endl;
    } else {
        std::cerr << "All " << total << " tests passed!" << std::endl;
    }
}

template<typename T> std::ostream &operator<<(std::ostream &os, const vector<T> &v) {
    os << "{";
    for (typename vector<T>::const_iterator vi = v.begin(); vi != v.end(); ++vi) {
        if (vi != v.begin())
            os << ",";
        os << " " << *vi;
    }
    os << " }";
    return os;
}
template<> std::ostream &operator<<(std::ostream &os, const vector<string> &v) {
    os << "{";
    for (vector<string>::const_iterator vi = v.begin(); vi != v.end(); ++vi) {
        if (vi != v.begin())
            os << ",";
        os << " \"" << *vi << "\"";
    }
    os << " }";
    return os;
}

int verify_case(int casenum, const vector<string> &expected, const vector<string> &received,
                std::clock_t elapsed) {
    std::cerr << "Example " << casenum << "... ";

    string verdict;
    vector<string> info;
    char buf[100];

    if (elapsed > CLOCKS_PER_SEC / 200) {
        std::sprintf(buf, "time %.2fs", elapsed * (1.0 / CLOCKS_PER_SEC));
        info.push_back(buf);
    }

    if (expected == received) {
        verdict = "PASSED";
    } else {
        verdict = "FAILED";
    }

    std::cerr << verdict;
    if (!info.empty()) {
        std::cerr << " (";
        for (size_t i = 0; i < info.size(); ++i) {
            if (i > 0)
                std::cerr << ", ";
            std::cerr << info[i];
        }
        std::cerr << ")";
    }
    std::cerr << std::endl;

    if (verdict == "FAILED") {
        std::cerr << "    Expected: " << expected << std::endl;
        std::cerr << "    Received: " << received << std::endl;
    }

    return verdict == "PASSED";
}

int run_test_case(int casenum__) {
    switch (casenum__) {
    case 0: {
        string field[] = {"........", "........", "........", "........"};
        int N = 3;
        string expected__[] = {"P.P.P...", "........", "........", "........"};

        std::clock_t start__ = std::clock();
        vector<string> received__ =
            Potatoes().plant(vector<string>(field, field + (sizeof field / sizeof field[0])), N);
        return verify_case(
            casenum__,
            vector<string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    case 1: {
        string field[] = {"####.###", "##.#####", "######.#", "###.####"};
        int N = 3;
        string expected__[] = {"####P###", "##P#####", "######P#", "###.####"};

        std::clock_t start__ = std::clock();
        vector<string> received__ =
            Potatoes().plant(vector<string>(field, field + (sizeof field / sizeof field[0])), N);
        return verify_case(
            casenum__,
            vector<string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    case 2: {
        string field[] = {"####.###", "##.#####", "######.#", "##..####"};
        int N = 5;
        string expected__[] = {};

        std::clock_t start__ = std::clock();
        vector<string> received__ =
            Potatoes().plant(vector<string>(field, field + (sizeof field / sizeof field[0])), N);
        return verify_case(
            casenum__,
            vector<string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    case 3: {
        string field[] = {".........", ".........", ".........", ".........", "........."};
        int N = 23;
        string expected__[] = {"P.P.P.P.P", ".P.P.P.P.", "P.P.P.P.P", ".P.P.P.P.", "P.P.P.P.P"};

        std::clock_t start__ = std::clock();
        vector<string> received__ =
            Potatoes().plant(vector<string>(field, field + (sizeof field / sizeof field[0])), N);
        return verify_case(
            casenum__,
            vector<string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    case 4: {
        string field[] = {".........", ".........", ".........", ".........", "........."};
        int N = 24;
        string expected__[] = {};

        std::clock_t start__ = std::clock();
        vector<string> received__ =
            Potatoes().plant(vector<string>(field, field + (sizeof field / sizeof field[0])), N);
        return verify_case(
            casenum__,
            vector<string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    case 5: {
        string field[] = {".........", "#########", ".#......#", ".########", ".#.....##"};
        int N = 13;
        string expected__[] = {"P.P.P.P.P", "#########", "P#P.P.P.#", ".########", "P#P.P.P##"};

        std::clock_t start__ = std::clock();
        vector<string> received__ =
            Potatoes().plant(vector<string>(field, field + (sizeof field / sizeof field[0])), N);
        return verify_case(
            casenum__,
            vector<string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }

        // custom cases

    case 6: {
        string field[] = {".#.", "#.#"};
        int N = 3;
        string expected__[] = {"P#P", "#P#"};

        std::clock_t start__ = std::clock();
        vector<string> received__ =
            Potatoes().plant(vector<string>(field, field + (sizeof field / sizeof field[0])), N);
        return verify_case(
            casenum__,
            vector<string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    case 7: {
        string field[] = {"###"};
        int N = 0;
        string expected__[] = {"###"};

        std::clock_t start__ = std::clock();
        vector<string> received__ =
            Potatoes().plant(vector<string>(field, field + (sizeof field / sizeof field[0])), N);
        return verify_case(
            casenum__,
            vector<string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    case 8: {
        string field[] = {"#.##.#", "......", "#.##.#"};
        int N = 7;
        string expected__[] = {"#P##P#", "P..P.P", "#P##P#"};

        std::clock_t start__ = std::clock();
        vector<string> received__ =
            Potatoes().plant(vector<string>(field, field + (sizeof field / sizeof field[0])), N);
        return verify_case(
            casenum__,
            vector<string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])),
            received__, clock() - start__);
    }
    default:
        return -1;
    }
}
} // namespace moj_harness

#include <cstdlib>
int main(int argc, char *argv[]) {
    if (argc == 1) {
        moj_harness::run_test();
    } else {
        for (int i = 1; i < argc; ++i)
            moj_harness::run_test(std::atoi(argv[i]));
    }
}
// END CUT HERE
