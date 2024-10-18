struct TestCase {
    void read_input() {}

    void solve(stringstream &out, int case_id) { out << "Case #" << case_id + 1 << ":"; }
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