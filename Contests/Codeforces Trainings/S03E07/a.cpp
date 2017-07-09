#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct Hash {
    static const int P1 = 31, P2 = 37, MOD = (int)1e9 + 7;    
    lint h1, h2;
    Hash(lint a = 0, lint b = 0) { h1 = a; h2 = b; }
    Hash(const string &s) {
        h1 = 0, h2 = 0;
        for (char c: s) {
            h1 = (P1 * h1 + c) % MOD;
            h2 = (P2 * h2 + c) % MOD;
        }
    }
    void append(char c) {
        h1 = (P1 * h1 + c) % MOD;
        h2 = (P2 * h2 + c) % MOD;
    }
    bool operator==(const Hash &that) const { return h1 == that.h1 && h2 == that.h2; }
    bool operator!=(const Hash &that) const { return h1 != that.h1 || h2 != that.h2; }
    Hash operator*(const Hash &that) const {
        return Hash((h1 * that.h1) % MOD, (h2 * that.h2) % MOD);
    }
    Hash operator-(const Hash &that) const {
        return Hash((h1 - that.h1 + MOD) % MOD, (h2 - that.h2 + MOD) % MOD);
    }
    bool operator<(const Hash &that) const {
        if (h1 == that.h1) return h2 < that.h2;
        return h1 < that.h1;
    }
};

struct HashArray {
    vector<Hash> pot;
    vector<Hash> array;

    HashArray(string &s) {
        pot.resize(s.size());
        pot[0] = Hash(1,1);
        Hash acc;
        for (size_t i = 0; i < s.size(); i++) {
            acc.append(s[i]);
            array.push_back(acc);
            if (i > 0) pot[i] = pot[i - 1] * Hash(Hash::P1, Hash::P2);
        }
    }

    inline Hash get_hash(int l, int r) {
        if (l == 0) return array[r];
        return array[r] - array[l - 1] * pot[r - l + 1];
    }
};

const int MAXND = (int)4e5 + 10;

struct Node {
    int val, end;
    Node *nxt[26];
} data[MAXND];

int data_cnt;
Node* newnode() {
    if (data_cnt == MAXND) abort();
    data[data_cnt].val = data[data_cnt].end = 0;
    memset(data[data_cnt].nxt, 0, sizeof(data[data_cnt].nxt));
    return &data[data_cnt++];
}

void refresh(Node *node) {
    for (int i = 0; i < 26; i++) {
        if (!node->nxt[i]) continue;
        node->nxt[i]->val = node->val + node->nxt[i]->end;
    }
}

const int MAXN = (int)2e5 + 10;
map<Hash, Node*> mp;
Hash cur_hash[MAXN];

void dfs(Node *node) {
    for (int i = 0; i < 26; i++) {
        if (!node->nxt[i]) continue;
        int before = !!node->nxt[i]->val;
        node->nxt[i]->val = node->val + node->nxt[i]->end;
        if (before != !!node->nxt[i]->val)
            dfs(node->nxt[i]);
    }
}

void add_char(int i, char c) {
    Node *node = mp[cur_hash[i]];
    cur_hash[i].append(c);
    if (node->nxt[c - 'a'] == NULL) {
        node->nxt[c - 'a'] = newnode();
        mp[cur_hash[i]] = node->nxt[c - 'a'];
    }
    node->val--, node->end--;
    node->nxt[c - 'a']->val++, node->nxt[c - 'a']->end++;
    dfs(node);
}

string vs[MAXN];

int main() {
    int n, q;
    cin >> n >> q;
    Node *trie = newnode();
    mp[Hash()] = trie;
    trie->val = trie->end = n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (char c: s) add_char(i, c);
        // printf("s: %s\n", s.c_str());
    }
    int last_yes = 0;
    for (int qi = 0; qi < q; qi++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            string s;
            cin >> s;
            for (char &c: s) c = (c - 'a' + last_yes) % 26 + 'a';
            HashArray ha(s);
            bool found = 0;
            for (int i = 0; i < (int)s.size(); i++) {
                int l = i - 1, r = s.size() - 1;
                while (l < r) {
                    int mid = (l + r + 1) / 2;
                    Hash hash = ha.get_hash(i, mid);
                    if (mp.find(hash) == mp.end()) r = mid - 1;
                    else l = mid;
                }
                if (l == i - 1) continue;
                Hash hash = ha.get_hash(i, l);
                if (mp[hash]->val > 0) {
                    found = 1;
                    break;
                }
            }
            printf("%s\n", found ? "YES" : "NO");
            if (found) last_yes = qi;
        }
        else {
            int i, c;
            scanf("%d%d", &i, &c);
            i = (i + last_yes) % n;
            char add = 'a' + (c + last_yes) % 26;
            add_char(i, add);
        }            
    }
        
    return 0;
}
