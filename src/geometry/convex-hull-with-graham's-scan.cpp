// Takes in >= 3 points
// Returns convex hull in clockwise order
vector<Vec<int>> buildConvexHull(vector<Vec<int>> pts) {
    sort(pts.begin(), pts.end());
    stack<Vec<int>> hull;
    hull.push(pts[0]);
    auto p = pts[0];
    sort(pts.begin()+1, pts.end(), [&](Vec<int> a, Vec<int> b) -> bool {
        // p->a->b is a ccw turn
        return sgn((a-p)^(b-a)) == 1;
    });
    hull.push(pts[1]);
    FOR(i, 2, (int)pts.size()) {
        auto c = pts[i];
        if(c == hull.top()) continue;
        while(true) {
            auto a = hull.top(); hull.pop();
            auto b = hull.top();
            auto ba = a-b;
            auto ac = c-a;
            if((ba^ac) >= 0) { // allows points on hull. Use > to disallow
                hull.push(a);
                break;
            }
        }
        hull.push(c);
    }
    vector<Vec<int>> hullPts;
    while(!hull.empty()) {
        hullPts.pb(hull.top());
        hull.pop();
    }
    return hullPts;
}