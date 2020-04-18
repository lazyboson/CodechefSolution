/*https://www.codechef.com/FLPAST01/problems/MAY19F1*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll ;
typedef vector<long long> vll;
typedef vector<int> vi;

// the segment tree is stored like a heap array
class SegmentTree {
private:
    vi st, A;
    int n;

    // same as binary heap operations
    int left (int p) {
        return p << 1;
    }
    int right(int p) {
        return (p << 1) + 1;
    }
    void build(int p, int L, int R) {                           // O(n log n)
        if (L == R)                            // as L == R, either one is fine
            st[p] = L;                                         // store the index
        else {                                // recursively compute the values
            build(left(p), L,(L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R);
            int p1 = st[left(p)], p2 = st[right(p)];
            //modified to get the Maximum Range Query
            st[p] = (A[p1] <= A[p2]) ? p2 : p1;
        }
    }

    // O(log n)- very fast
    int rmq(int p, int L, int R, int i, int j) {
        if (i >  R || j <  L) return -1; // current segment outside query range
        if (L >= i && R <= j) return st[p];               // inside query range

        // compute the min position in the left and right part of the interval
        int p1 = rmq(left(p), L, (L+R) / 2, i, j);
        int p2 = rmq(right(p), (L+R) / 2 + 1, R, i, j);

        if (p1 == -1) return p2;   // if we try to access segment outside query
        if (p2 == -1) return p1;
        // same as above
        return (A[p1] <= A[p2]) ? p2 : p1;
    }          // as as in build routine

    int update_point(int p, int L, int R, int idx, int new_value) {
        // this update code is still preliminary, i == j
        // must be able to update range in the future!
        int i = idx, j = idx;

        // if the current interval does not intersect
        // the update interval, return this st node value!
        if (i > R || j < L)
            return st[p];

        // if the current interval is included in the update range,
        // update that st[node]
        if (L == i && R == j) {
            A[i] = new_value; // update the underlying array
            return st[p] = L; // this index
        }

        // compute the minimum position in the
        // left and right part of the interval
        int p1, p2;
        p1 = update_point(left(p), L,(L + R) / 2, idx, new_value);
        p2 = update_point(right(p), (L + R) / 2 + 1, R, idx, new_value);

        // return the position where the overall minimum is
        return st[p] = (A[p1] <= A[p2]) ? p2 : p1;
    }

public:
    SegmentTree(const vi &_A) {
        A = _A;
        n = (int)A.size();              // copy content for local usage
        st.assign(4 * n, 0);            // create large enough vector of zeroes
        build(1, 0, n - 1);                                  // recursive build
    }

    int rmq(int i, int j) {
        return rmq(1, 0, n - 1, i, j);    // overloading
    }

    int update_point(int idx, int new_value) {
        return update_point(1, 0, n - 1, idx, new_value);
    }
};



int main() {
    ios_base::sync_with_stdio(false);
    int testcase, games, query;
    cin >> testcase;
    while (testcase--) {
        cin >> games >> query;
        vector<int> scores(games);
        vector<int> raise_query(query);

        for(int i =0; i<games; i++) {
            cin >> scores[i];
        }
        for(int i =0; i<query; i++) {
            cin >> raise_query[i];
        }
        //build segment tree for these set of the scores
        SegmentTree _st(scores);

        for(int i=0; i<query; i++) {
            //the tree return max element in the range
            int index = _st.rmq(0, raise_query[i]-1);
            cout << scores[index] << endl;
            //this will take linear time so if i shall get TLE then will go for segemnt tree
//            ll ans = *max_element(scores.begin(), scores.begin()+raise_query[i]);
//            cout << ans << endl;
        }
    }
    return 0;
}

