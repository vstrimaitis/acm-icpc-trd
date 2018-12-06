// Add to segment, get maximum of segment
struct LazySegTree {
    int n;
    vector<ll> t, lazy;
    LazySegTree(int _n) {
        n = _n; t = vector<ll>(4*n, 0); lazy = vector<ll>(4*n, 0);
    }
    LazySegTree(vector<ll>& arr) {
        n = _n; t = vector<ll>(4*n, 0); lazy = vector<ll>(4*n, 0);
        build(arr, 1, 0, n-1); // same as in simple SegmentTree
    }
    void push(int v) {
        t[v*2] += lazy[v];
        lazy[v*2] += lazy[v];
        t[v*2+1] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v] = 0;
    }
    void update(int v, int tl, int tr, int l, int r, ll addend) {
        if (l > r) 
            return;
        if (l == tl && tr == r) {
            t[v] += addend;
            lazy[v] += addend;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), addend);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
            t[v] = max(t[v*2], t[v*2+1]);
        }
    }

    int query(int v, int tl, int tr, int l, int r) {
        if (l > r || r < tl || l > tr) return -OO;
        if (l <= tl && tr <= r) return t[v];
        push(v);
        int tm = (tl + tr) / 2;
        return max(query(v*2, tl, tm, l, r), 
                query(v*2+1, tm+1, tr, l, r));
    }
};