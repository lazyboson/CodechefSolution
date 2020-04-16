/*problem link - https://www.codechef.com/problems/CARSELL */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
typedef long long ll;



int main() {
    ios_base::sync_with_stdio(false);
    static const long long MODULE = 1e9+7;
    int t;
    cin >> t;
    while (t--) {
        ll ans =0;
        int n;
        vector<ll> price;
        cin >> n;
        for(int i=0; i<n; i++) {
            ll input;
            cin >>input;
            price.push_back(input);
        }

        sort(price.rbegin(),price.rend());
        for(int i= 0; i<n; i++) {
            ans+= std::max(0LL, price[i]-i);
            ans %= MODULE;
        }
        cout << ans <<endl;
    }
}
