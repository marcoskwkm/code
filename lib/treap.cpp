// Supports insertion, deletion, querying kth-element and finding element
// Keeps duplicate elements as different nodes

template <class T> class Treap {
    struct Node {
        T val;
        int h,cnt;
        Node *l, *r;
        Node(T val2) {
            val = val2;
            h = rand();
            cnt = 1;
            l = r = NULL;
        }
    };
    Node *root;
    
    inline Node* newNode(T val) { return new Node(val); }

    inline void refresh(Node *node) {
        if (node == NULL) return;
        node->cnt = (node->l == NULL ? 0 : node->l->cnt) +
            (node->r == NULL ? 0 : node->r->cnt) + 1;
    }

    void _insert(Node *&node, T val) {
        if (node == NULL) {
            node = newNode(val);
            return;
        }
        if (val <= node->val) {
            _insert(node->l, val);
            if (node->l->h > node->h) {
                Node *aux = node->l;
                node->l = aux->r;
                aux->r = node;
                node = aux;
                refresh(node->r);
                refresh(node);
            }
            else refresh(node);
        }
        else {
            _insert(node->r, val);
            if (node->r->h > node->h) {
                Node *aux = node->r;
                node->r = aux->l;
                aux->l = node;
                node = aux;
                refresh(node->l);
                refresh(node);
            }
            else refresh(node);
        }
    }

    Node* merge(Node *L,Node *R) {
        if (L == NULL) return R;
        if (R == NULL) return L;
        if (L->h < R->h) {
            L->r = merge(L->r,R);
            refresh(L);
            return L;
        }
        else {
            R->l = merge(L,R->l);
            refresh(R);
            return R;
        }
    }

    // not used. splits node into two trees a(<=val) and b(>val)
    void split(T val, Node *node, Node *&a, Node *&b) {
        if (node == NULL) {
            a = b = NULL;
            return;
        }
        Node *aux;
        if (val >= node->val) {
            split(val,node->r,aux,b);
            node->r = aux;
            a = node;
            refresh(a);
        }
        else {
            split(val,node->l,a,aux);
            node->l = aux;
            b = node;
            refresh(b);
        }
    }

    // erases a single appearence of val
    void _erase(Node *&node, T val) {
        if (node == NULL) return;
        if (node->val > val) _erase(node->l, val);
        else if (node->val < val) _erase(node->r, val);
        else node = merge(node->l,node->r);
        refresh(node);
    }
    
    // 0-indexed (not safe if element doesnt exist)
    T _kth(Node *node,int k) {
        int ql = (node->l == NULL ? 0 : node->l->cnt);
        if (k < ql) return _kth(node->l,k);
        if (k == ql) return node->val;
        k -= ql + 1;
        return _kth(node->r,k);
    }

    // returns position (0-indexed) of element 'val' in 'node'. -1 if it doesn't exist
    int _find(Node *node, T val) {
        if (node == NULL) return -1;
        if (node->val == val) return (node->l == NULL ? 0 : node->l->cnt);
        else if (node->val > val) return _find(node->l,val);
        else {
            int pos = _find(node->r,val);
            if (pos == -1) return -1;
            return 1 + (node->l == NULL ? 0 : node->l->cnt) + pos;
        }
    }        

    void _clear(Node *&node) {
        if (node == NULL) return;
        _clear(node->l); _clear(node->r);
        delete node;
        node = NULL;
    }
    
public:
    Treap() { root = NULL; }
    void insert(T val) { _insert(root,val); }
    T kth(int k) { return _kth(root,k); }
    int size() { return root == NULL ? 0 : root->cnt; }
    void clear() { _clear(root); }
    void erase(T val) { _erase(root,val); }
    int find(T val) { return _find(root,val); }
};
