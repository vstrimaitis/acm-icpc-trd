struct Edge
{
    int a, b, cost;
};

int n, m, v; // v - starting vertex
vector<Edge> e;

/* Finds SSSP with negative edge weights.
 * Possible optimization: check if anything changed in a relaxation step. If not - you can break early.
 * To find a negative cycle: perform one more relaxation step. If anything changes - a negative cycle exists.
 */
void solve() {
    vector<int> d (n, oo);
    d[v] = 0;
    for (int i=0; i<n-1; ++i)
        for (int j=0; j<m; ++j)
            if (d[e[j].a] < oo)
                d[e[j].b] = min (d[e[j].b], d[e[j].a] + e[j].cost);
    // display d, for example, on the screen
}