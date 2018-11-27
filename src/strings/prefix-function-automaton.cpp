// aut[oldPi][c] = newPi
vector<vector<int>> computeAutomaton(string s) {
    const char BASE = 'a';
    s += "#";
    int n = s.size();
    vector<int> pi = prefixFunction(s);
    vector<vector<int>> aut(n, vector<int>(26));
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && BASE + c != s[i])
                aut[i][c] = aut[pi[i-1]][c];
            else
                aut[i][c] = i + (BASE + c == s[i]);
        }
    }
    return aut;
}
vector<int> findOccurs(const string& s, const string& t) {
    auto aut = computeAutomaton(s);
    int curr = 0;
    vector<int> occurs;
    FOR(i, 0, (int)t.length()) {
        int c = t[i]-'a';
        curr = aut[curr][c];
        if(curr == (int)s.length()) {
            occurs.pb(i-s.length()+1);
        }
    }
    return occurs;
}