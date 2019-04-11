/*
Let's say we have a relation:
dp[i] = min(dp[j] + h[j+1]*w[i]) for j<=i
Let's set k_j = h[j+1], x = w[i], b_j = dp[j]. We get:
dp[i] = min(b_j+k_j*x) for j<=i.
This is the same as finding a minimum point on a set of lines.
After calculating the value, we add a new line with
k_i = h[i+1] and b_i = dp[i].
*/
struct Line {
    int k;
    int b;

    int eval(int x) {
        return k*x+b;
    }

    int intX(Line& other) {
        int x = b-other.b;
        int y = other.k-k;
        int res = x/y;
        if(x%y != 0) res++;
        return res;
    }
};

struct BagOfLines {
    vector<pair<Line, int>> lines;

    void addLine(int k, int b) {
        Line current = {k, b};
        if(lines.empty()) {
            lines.pb({current, -OO});
            return;
        }
        int x = -OO;
        while(true) {
            auto line = lines.back().first;
            int from = lines.back().second;
            x = line.intX(current);
            if(x > from) break;
            lines.pop_back();
        }
        lines.pb({current, x});
    }

    int findMin(int x) {
        int lo = 0, hi = (int)lines.size()-1;
        while(lo < hi) {
            int mid = (lo+hi+1)/2;
            if(lines[mid].second <= x) {
                lo = mid;
            } else {
                hi = mid-1;
            }
        }
        return lines[lo].first.eval(x);
    }
};