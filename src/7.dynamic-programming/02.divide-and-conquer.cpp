/*
Let A[i][j] be the optimal answer for using i objects to satisfy j first
requirements.
The recurrence is:
A[i][j] = min(A[i-1][k] + f(i, j, k)) where f is some function that denotes the
cost of satisfying requirements from k+1 to j using the i-th object.
Consider the recursive function calc(i, jmin, jmax, kmin, kmax), that calculates
all A[i][j] for all j in [jmin, jmax] and a given i using known A[i-1][*].
*/

void calc(int i, int jmin, int jmax, int kmin, int kmax) {
    if(jmin > jmax) return;
    int jmid = (jmin+jmax)/2;
    // calculate A[i][jmid] naively (for k in kmin...min(jmid, kmax){...})
    // let kmid be the optimal k in [kmin, kmax]
    calc(i, jmin, jmid-1, kmin, kmid);
    calc(i, jmid+1, jmax, kmid, kmax);
}

int main() {
    // set initial dp values
    FOR(i, start, k+1){
        calc(i, 0, n-1, 0, n-1);
    }
    cout << dp[k][n-1];
}