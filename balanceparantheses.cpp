#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

map<string, bool> visited;

bool isBalaced(string inQuestion) {
    int cnt = 0;
    for(auto c:inQuestion) {
        if( c == '(') cnt++;
        else if( c== ')') cnt--;
        if(cnt < 0) return 0;
    }
    return 1;
}

vector<string> bfs(string exp) {
    vector<string> ans;
    queue<string> graph;
    graph.push(exp);
    bool found = 0;
    while(!graph.empty()) {
        string u = graph.front();
        graph.pop();
        if(visited[u]) continue;
        visited[u] = true;
        if(isBalaced(u)) found = 1, ans.push_back(u);
        if(found)
            continue;
        for(int i=0; i< u.size(); i++) {
            if(u[i] == '(' || u[i] == ')') {
                string v = u.substr(0, i) + u.substr(i+1, u.size());
                graph.push(v);
            }
        }
    }
    return ans;
}

int main() {
    string expression;
    cin >> expression;
    vector<string> ans = bfs(expression);
    for(auto x : ans)
        cout << x << endl;

    return 0;
}

