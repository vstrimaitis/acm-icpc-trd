vector<Vec<int>> buildConvexHull(vector<Vec<int>>& pts) {
    int n = pts.size();
    sort(pts.begin(), pts.end());
    auto currP = pts[0]; // choose some extreme point to be on the hull
    
    vector<Vec<int>> hull;
    set<Vec<int>> used;
    hull.pb(pts[0]);
    used.insert(pts[0]);
    while(true) {
        auto candidate = pts[0]; // choose some point to be a candidate
        
        auto currDir = candidate-currP;
        vector<Vec<int>> toUpdate;
        FOR(i, 0, n) {
            if(currP == pts[i]) continue;
            // currently we have currP->candidate
            // we need to find point to the left of this
            auto possibleNext = pts[i];
            auto nextDir = possibleNext - currP;
            auto cross = currDir ^ nextDir;
            if(candidate == currP || cross > 0) {
                candidate = possibleNext;
                currDir = nextDir;
            } else if(cross == 0 && nextDir.norm() > currDir.norm()) {
                candidate = possibleNext;
                currDir = nextDir;
            }
        }
        if(used.find(candidate) != used.end()) break;
        hull.pb(candidate);
        used.insert(candidate);
        currP = candidate;
    }
    return hull;
}