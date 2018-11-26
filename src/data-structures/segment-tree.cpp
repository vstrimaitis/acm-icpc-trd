struct SegmentTree {
    int n;
    vector<ll> t;
    const ll IDENTITY = 0; // OO for min, -OO for max, ...
    ll f(ll a, ll b) {
        return a+b;
    }
    SegmentTree(int _n) {
        n = _n; t = vector<ll>(4*n, IDENTITY);
    }
    SegmentTree(vector<ll>& arr) {
        n = arr.size(); t = vector<ll>(4*n, IDENTITY);
        build(arr, 1, 0, n-1);
    }
    void build(vector<ll>& arr, int v, int tl, int tr) {
        if(tl == tr) { t[v] = arr[tl]; }
        else {
            int tm = (tl+tr)/2;
            build(arr, 2*v, tl, tm);
            build(arr, 2*v+1, tm+1, tr);
            t[v] = f(t[2*v], t[2*v+1]);
        }
    }
    // sum(1, 0, n-1, l, r)
    ll sum(int v, int tl, int tr, int l, int r) {
        if(l > r) return IDENTITY;
        if (l == tl && r == tr) return t[v];
        int tm = (tl+tr)/2;
        return f(sum(2*v, tl, tm, l, min(r, tm)), sum(2*v+1, tm+1, tr, max(l, tm+1), r));
    }
    // update(1, 0, n-1, i, v)
    void update(int v, int tl, int tr, int pos, ll newVal) {
        if(tl == tr) { t[v] = newVal; }
        else {
            int tm = (tl+tr)/2;
            if(pos <= tm) update(2*v, tl, tm, pos, newVal);
            else update(2*v+1, tm+1, tr, pos, newVal);
            t[v] = f(t[2*v],t[2*v+1]);
        }
    }
};