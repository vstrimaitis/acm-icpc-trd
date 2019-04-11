ll pwr(ll a, ll b, ll m) {
    if(a == 1) return 1;
    if(b == 0) return 1;
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}