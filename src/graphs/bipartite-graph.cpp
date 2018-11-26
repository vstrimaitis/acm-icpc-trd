class BipartiteGraph {
private:
    vector<int> _left, _right;
    vector<vector<int>> _adjList;
    vector<int> _matchR, _matchL;
    vector<bool> _used;

    bool _kuhn(int v) {
        if (_used[v]) return false;
        _used[v] = true;
        FOR(i, 0, (int)_adjList[v].size()) {
            int to = _adjList[v][i] - _left.size();
            if (_matchR[to] == -1 || _kuhn(_matchR[to])) {
                _matchR[to] = v;
                _matchL[v] = to;
                return true;
            }
        }
        return false;
    }
    void _addReverseEdges() {
        FOR(i, 0, (int)_right.size()) {
            if (_matchR[i] != -1) {
                _adjList[_left.size() + i].pb(_matchR[i]);
            }
        }
    }
    void _dfs(int p) {
        if (_used[p]) return;
        _used[p] = true;
        for (auto x : _adjList[p]) {
            _dfs(x);
        }
    }
    vector<pii> _buildMM() {
        vector<pair<int, int> > res;
        FOR(i, 0, (int)_right.size()) {
            if (_matchR[i] != -1) {
                res.push_back(make_pair(_matchR[i], i));
            }
        }

        return res;
    }
public:
    void addLeft(int x) {
        _left.pb(x);
        _adjList.pb({});
        _matchL.pb(-1);
        _used.pb(false);
    }
    void addRight(int x) {
        _right.pb(x);
        _adjList.pb({});
        _matchR.pb(-1);
        _used.pb(false);
    }
    void addForwardEdge(int l, int r) {
        _adjList[l].pb(r + _left.size());
    }
    void addMatchEdge(int l, int r) {
        if(l != -1) _matchL[l] = r;
        if(r != -1) _matchR[r] = l;
    }
    // Maximum Matching
    vector<pii> mm() {
        _matchR = vector<int>(_right.size(), -1);
        _matchL = vector<int>(_left.size(), -1);
        // ^ these two can be deleted if performing MM on already partially matched graph
        _used = vector<bool>(_left.size() + _right.size(), false);


        bool path_found;
        do {
            fill(_used.begin(), _used.end(), false);
            path_found = false;
            FOR(i, 0, (int)_left.size()) {
                if (_matchL[i] < 0 && !_used[i]) {
                    path_found |= _kuhn(i);
                }
            }
        } while (path_found);

        return _buildMM();
    }

    // Minimum Edge Cover
    // Algo: Find MM, add unmatched vertices greedily.
    vector<pii> mec() {
        auto ans = mm();
        FOR(i, 0, (int)_left.size()) {
            if (_matchL[i] != -1) {
                for (auto x : _adjList[i]) {
                    int ridx = x - _left.size();
                    if (_matchR[ridx] == -1) {
                        ans.pb({ i, ridx });
                        _matchR[ridx] = i;
                    }
                }
            }
        }
        FOR(i, 0, (int)_left.size()) {
            if (_matchL[i] == -1 && (int)_adjList[i].size() > 0) {
                int ridx = _adjList[i][0] - _left.size();
                _matchL[i] = ridx;
                ans.pb({ i, ridx });
            }
        }
        return ans;
    }

    // Minimum Vertex Cover
    // Algo: Find MM. Run DFS from unmatched vertices from the left part.
    // MVC is composed of unvisited LEFT and visited RIGHT vertices.
    pair<vector<int>, vector<int>> mvc(bool runMM = true) {
        if (runMM) mm();
        _addReverseEdges();
        fill(_used.begin(), _used.end(), false);
        FOR(i, 0, (int)_left.size()) {
            if (_matchL[i] == -1) {
                _dfs(i);
            }
        }
        vector<int> left, right;
        FOR(i, 0, (int)_left.size()) {
            if (!_used[i]) left.pb(i);
        }
        FOR(i, 0, (int)_right.size()) {
            if (_used[i + (int)_left.size()]) right.pb(i);
        }
        return { left,right };
    }

    // Maximal Independant Vertex Set
    // Algo: Find complement of MVC.
    pair<vector<int>, vector<int>> mivs(bool runMM = true) {
        auto m = mvc(runMM);
        vector<bool> containsL(_left.size(), false), containsR(_right.size(), false);
        for (auto x : m.first) containsL[x] = true;
        for (auto x : m.second) containsR[x] = true;
        vector<int> left, right;
        FOR(i, 0, (int)_left.size()) {
            if (!containsL[i]) left.pb(i);
        }
        FOR(i, 0, (int)_right.size()) {
            if (!containsR[i]) right.pb(i);
        }
        return { left, right };
    }

};