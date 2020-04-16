/*Problem Link - https://www.codechef.com/problems/COVIDLQ/ */
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    //reading input
    int testcase, n, input;
    vector<int> queue;
    vector<pair<int,int>> queue_with_distance;
    cin >> testcase;
    //reading input
    while(testcase--) {
        bool isPrinted = false;
        queue.clear();
        queue_with_distance.clear();
        cin >> n;
        for(int i = 0; i<n; i++) {
            cin >> input;
            queue.emplace_back(input);
        }
        //counting the respective distance;
        int cnt = 0;
        for(int i = 0; i<n; i++) {
            if(queue[i] == 1) {
                cnt++;
                queue_with_distance.emplace_back(make_pair(queue[i],cnt));
                cnt = 0;
            }
            else
                cnt++;
        }

        //printing answer, just we are not interested in first element as if one person who cares
        //if more than one just check and return
        for(int i = 1; i<(int) queue_with_distance.size(); i++) {
            if(queue_with_distance[i].second < 6) {
                cout<<"NO\n";
                isPrinted = true;
                break;
            }
        }
        if(!isPrinted)
            cout << "YES\n";
    }
    return 0;
}
