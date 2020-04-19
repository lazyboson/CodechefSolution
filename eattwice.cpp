#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <set>
#include <string>
#include <stack>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;



// Driver program to test above functions
int main()
{
    ios_base::sync_with_stdio(false);
    int tc;
    cin >> tc;
    while (tc--){
        ll n, m, d, v;
        cin >> n >>m;
        vector<pair<ll, ll>> price;

        for(int i=0;i<n; i++){
            cin >> d >>v;
            price.push_back({v,d});
        }
        //log(n) time
        sort(price.rbegin(),price.rend());
        long long ans = 0;
        int cnt = 0;
        set<ll> hasAccounted;
        for(int i = 0; i<n; i++){
            if(cnt <2){
                //log(n) time
                set<ll>::iterator itr = hasAccounted.end();
                if(hasAccounted.find(price[i].second) == itr){
                    ans += price[i].first;
                    cnt++;
                    hasAccounted.insert(price[i].second);
                }
            }
            else if(cnt == 2){
                break;
            }
        }
        cout << ans << endl;

    }
    return 0;
}
