// NEEDS TESTING
struct AhoCorasick {
    const static int MAXC = 300; // alphabet size
    const static int MAXND = (int)1e4 + 10;
    
    struct Node {
        vector<int> matches;
        int nxt[MAXC];
        int fail;

        Node() { memset(nxt, -1, sizeof(nxt)); }
    };
    
    vector<Node> nodes;
    vector<string> words;
    int cur_node;
    bool built;
    int fail_mem[MAXND][MAXC];

    void add(int node, int i, int idx) {
        int c = words[idx][i];
        if (i == (int)words[idx].size()) {
            nodes[node].matches.push_back(idx);
            return;
        }
        if (nodes[node].nxt[c] == -1) {
            nodes[node].nxt[c] = nodes.size();
            nodes.push_back(Node());
        }
        add(nodes[node].nxt[c], i + 1, idx);
    }

    void add_word(string word) {
        words.push_back(word);
        add(0, 0, words.size() - 1);
    }

    void build() {
        built = 1;
        queue<int> q;
        nodes[0].fail = 0;
        for (int c = 0; c < MAXC; c++) {
            int nxt = nodes[0].nxt[c];
            if (nxt != -1) {
                nodes[nxt].fail = 0;
                q.push(nxt);
            }
        }
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int c = 0; c < MAXC; c++) {
                int nxt = nodes[cur].nxt[c];
                if (nxt == -1) continue;
                int fail = nodes[cur].fail;
                while (fail && nodes[fail].nxt[c] == -1) fail = nodes[fail].fail;
                if (nodes[fail].nxt[c] == -1) nodes[nxt].fail = 0;
                else nodes[nxt].fail = nodes[fail].nxt[c];
                for (int match: nodes[nodes[nxt].fail].matches)
                    nodes[nxt].matches.push_back(match);
                q.push(nxt);
            }
        }
    }

    void walk(int c) {
        assert(built);
        int prv_node = cur_node;
        if (fail_m[cur_node][c] != -1) cur_node = fail_m[cur_node][c];
        else {
            if (nodes[cur_node].nxt[c] != -1)
                cur_node = nodes[cur_node].nxt[c];
            else {
                int fail = nodes[cur_node].fail;
                while (fail && nodes[fail].nxt[c] == -1) fail = nodes[fail].fail;
                if (nodes[fail].nxt[c] == -1) cur_node = 0;
                else cur_node = nodes[fail].nxt[c];
            }
            fail_m[prv_node][c] = cur_node;
        }
    }

    vector<int> get_matches() { return nodes[cur_node].matches; }

    void reset() { cur_node = 0; }        

    void clear() {
        built = 0;
        nodes.clear();
        words.clear();
        nodes.push_back(Node());
        memset(fail_m, -1, sizeof(fail_m));
        reset();
    }
    
    AhoCorasick() { clear(); }
};
