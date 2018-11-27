template <typename T>
struct Node {
    Node* l, *r;
    ll prio, size, sum;
    T val;
    bool rev;
    Node() {}
    Node(T _val) : l(nullptr), r(nullptr), val(_val), size(1), sum(_val), rev(false) {
        prio = rand() ^ (rand() << 15);
    }
};
template <typename T>
struct ImplicitTreap {
    typedef Node<T>* NodePtr;
    int sz(NodePtr n) {
        return n ? n->size : 0;
    }
    ll getSum(NodePtr n) {
        return n ? n->sum : 0;
    }

    void push(NodePtr n) {
        if (n && n->rev) {
            n->rev = false;
            swap(n->l, n->r);
            if (n->l) n->l->rev ^= 1;
            if (n->r) n->r->rev ^= 1;
        }
    }

    void recalc(NodePtr n) {
        if (!n) return;
        n->size = sz(n->l) + 1 + sz(n->r);
        n->sum = getSum(n->l) + n->val + getSum(n->r);
    }

    void split(NodePtr tree, ll key, NodePtr& l, NodePtr& r) {
        push(tree);
        if (!tree) {
            l = r = nullptr;
        }
        else if (key <= sz(tree->l)) {
            split(tree->l, key, l, tree->l);
            r = tree;
        }
        else {
            split(tree->r, key-sz(tree->l)-1, tree->r, r);
            l = tree;
        }
        recalc(tree);
    }

    void merge(NodePtr& tree, NodePtr l, NodePtr r) {
        push(l); push(r);
        if (!l || !r) {
            tree = l ? l : r;
        }
        else if (l->prio > r->prio) {
            merge(l->r, l->r, r);
            tree = l;
        }
        else {
            merge(r->l, l, r->l);
            tree = r;
        }
        recalc(tree);
    }

    void insert(NodePtr& tree, T val, int pos) {
        if (!tree) {
            tree = new Node<T>(val);
            return;
        }
        NodePtr L, R;
        split(tree, pos, L, R);
        merge(L, L, new Node<T>(val));
        merge(tree, L, R);
        recalc(tree);
    }

    void reverse(NodePtr tree, int l, int r) {
        NodePtr t1, t2, t3;
        split(tree, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        if(t2) t2->rev = true;
        merge(t2, t1, t2);
        merge(tree, t2, t3);
    }

    void print(NodePtr t, bool newline = true) {
        push(t);
        if (!t) return;
        print(t->l, false);
        cout << t->val << " ";
        print(t->r, false);
        if (newline) cout << endl;
    }

    NodePtr fromArray(vector<T> v) {
        NodePtr t = nullptr;
        FOR(i, 0, (int)v.size()) {
            insert(t, v[i], i);
        }
        return t;
    }

    ll calcSum(NodePtr t, int l, int r) {
        NodePtr L, R;
        split(t, l, L, R);
        NodePtr good;
        split(R, r - l + 1, good, L);
        return getSum(good);
    }
};
/* Usage: ImplicitTreap<int> t;
Node<int> tree = t.fromArray(someVector); t.reverse(tree, l, r); ...
*/