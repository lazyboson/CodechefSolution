#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <queue>
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
        int n;
        cin >> n;
        vector<int> price(n);
        for(int i=0;i<n;i++){
            cin >> price[i];
        }
        //reverse sort
        sort(price.rbegin(), price.rend());

        ///using greedy algorithms
        bool isCnt = true;
        long ans = 0;
        if(n==1)
            cout << price[0] <<endl;
        else if(n== 2)
            cout << price[0] +price[1] <<endl;
        else{
            for(int j=0;j<n;j+=2){
                if(isCnt){
                    ans+= price[j];
                    if(j+1<n)
                        ans+= price[j+1];
                    isCnt=false;
                }
                else{
                    isCnt = true;
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}
