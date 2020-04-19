#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <string>
#include <stack>
#include <map>
using namespace std;
typedef long long ll;



// Driver program to test above functions
int main()
{
    long jecketcost, sockcost, money;
    cin >> jecketcost >> sockcost >>money;
    long cnt =0;
    long moneyleft = money-jecketcost;
    while(moneyleft >= sockcost){
        cnt++;
        moneyleft -= sockcost;
    }
    if(cnt%2 == 0)
        cout << "Lucky Chef"<<endl;
    else
        cout << "Unlucky Chef" <<endl;
    return 0;
}
