/*https://www.codechef.com/FLPAST01/problems/RADGEE*/
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
using namespace std;
typedef long long ll;


void winner(list<ll> radhesh, list<ll> geeta, queue<ll> extra_pile){
    long long r_cnt=0, g_cnt=0;
    while(!radhesh.empty() && !geeta.empty()){
        list<ll>::iterator it;
        if(radhesh.front() > geeta.front()){
            r_cnt++;
            //erase first element will take constant time

            if(!extra_pile.empty()){
                radhesh.push_back(extra_pile.front());
                extra_pile.pop();
                geeta.push_back(extra_pile.front());
                extra_pile.pop();
            }
        }
        else{
            g_cnt++;

            if(!extra_pile.empty()){
                geeta.push_back(extra_pile.front());
                extra_pile.pop();
                radhesh.push_back(extra_pile.front());
                extra_pile.pop();
            }
        }
        //erase first element from both list and it shall take constant time
        it = radhesh.begin();
        radhesh.erase(it);
        it = geeta.begin();
        geeta.erase(it);
    }
    if(r_cnt > g_cnt)
        cout << "Radhesh wins" <<endl;
    else if(g_cnt > r_cnt)
        cout << "Geethakoomaree wins" <<endl;
    else
        cout << "Tie" << endl;
}

// Driver program to test above functions
int main()
{
    int testcases, n,q;
    long long num;
    cin>>testcases;
    while (testcases--){

        list<long long> st_first, st_second;
        queue<long long> extra;
        cin >> n >> q;
        //fill first stack
        for(int i=0; i<n;i++){
            cin>>num;
            st_first.push_back(num);
        }
        //fill second stack
        for(int i=0; i<n;i++){
            cin>>num;
            st_second.push_back(num);
        }
        //fill extra stack
        for(int i=0; i<q;i++){
            cin >> num;
            extra.push(num);
        }
        winner(st_first,st_second,extra);
    }
    return 0;
}
