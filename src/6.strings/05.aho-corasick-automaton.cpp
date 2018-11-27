// alphabet size
const int K = 70;

// the indices of each letter of the alphabet
int intVal[256];
void init() {
    int curr = 2;
    intVal[1] = 1;
    for(char c = '0'; c <= '9'; c++, curr++) intVal[(int)c] = curr;
    for(char c = 'A'; c <= 'Z'; c++, curr++) intVal[(int)c] = curr;
    for(char c = 'a'; c <= 'z'; c++, curr++) intVal[(int)c] = curr;
}

struct Vertex {
    int next[K];
    vector<int> marks;
    // ^ this can be changed to int mark = -1, if there will be no duplicates
    int p = -1;
    char pch;
    int link = -1;
    int exitLink = -1;
    // ^ exitLink points to the next node on the path of suffix links which is marked
    int go[K];

    // ch has to be some small char
    Vertex(int _p=-1, char ch=(char)1) : p(_p), pch(ch) {
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};

vector<Vertex> t(1);

void addString(string const& s, int id) {
    int v = 0;
    for (char ch : s) {
        int c = intVal[(int)ch];
        if (t[v].next[c] == -1) {
            t[v].next[c] = t.size();
            t.emplace_back(v, ch);
        }
        v = t[v].next[c];
    }
    t[v].marks.pb(id);
}

int go(int v, char ch);

int getLink(int v) {
    if (t[v].link == -1) {
        if (v == 0 || t[v].p == 0)
            t[v].link = 0;
        else
            t[v].link = go(getLink(t[v].p), t[v].pch);
    }
    return t[v].link;
}

int getExitLink(int v) {
    if(t[v].exitLink != -1) return t[v].exitLink;
    int l = getLink(v);
    if(l == 0) return t[v].exitLink = 0;
    if(!t[l].marks.empty()) return t[v].exitLink = l;
    return t[v].exitLink = getExitLink(l);
}

int go(int v, char ch) {
    int c = intVal[(int)ch];
    if (t[v].go[c] == -1) {
        if (t[v].next[c] != -1)
            t[v].go[c] = t[v].next[c];
        else
            t[v].go[c] = v == 0 ? 0 : go(getLink(v), ch);
    }
    return t[v].go[c];
}

void walkUp(int v, vector<int>& matches) {
    if(v == 0) return;
    if(!t[v].marks.empty()) {
        for(auto m : t[v].marks) matches.pb(m);
    }
    walkUp(getExitLink(v), matches);
}

// returns the IDs of matched strings.
// Will contain duplicates if multiple matches of the same string are found.
vector<int> walk(const string& s) {
    vector<int> matches;
    int curr = 0;
    for(char c : s) {
        curr = go(curr, c);
        if(!t[curr].marks.empty()) {
            for(auto m : t[curr].marks) matches.pb(m);
        }
        walkUp(getExitLink(curr), matches);
    }
    return matches;
}
/* Usage:
 * addString(strs[i], i);
 * auto matches = walk(text);
 * .. do what you need with the matches - count, check if some id exists, etc ..
 * Some applications:
 * - Find all matches: just use the walk function
 * - Find lexicographically smallest string of a given length that doesn't match any of the given strings:
 *   For each node, check if it produces any matches (it either contains some marks or walkUp(v) returns some marks).
 *   Remove all nodes which produce at least one match. Do DFS in the remaining graph, since none of the remaining nodes
 *   will ever produce a match and so they're safe.
 * - Find shortest string containing all given strings:
 *   For each vertex store a mask that denotes the strings which match at this state. Start at (v = root, mask = 0),
 *   we need to reach a state (v, mask=2^n-1), where n is the number of strings in the set. Use BFS to transition between states
 *   and update the mask.
 */