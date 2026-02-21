#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n, s; cin >> n >> s;
    vector<priority_queue<int, vector<int>, greater<int>>> pq(n);
    for(int i = 0; i < n; i++){
        for(int j = 0, h; j < s; j++){
            cin >> h;
            pq[i].push(h);
        }
    }
    set<pair<int,int>> st;
    for(int i = 0; i < n; i++){
        st.insert({pq[i].top(), i});
        pq[i].pop();
    }
    int ans = (*st.rbegin()).first - (*st.begin()).first;
    while(true){
        auto it = st.begin();
        int curr_height = it->first;
        int cls = it->second;
        if(pq[cls].empty()) break;
        st.erase(it);
        int next_height = pq[cls].top(); 
        pq[cls].pop();
        st.insert({next_height, cls});
        int lo = (*st.begin()).first;
        int hi = (*st.rbegin()).first;
        ans = min(ans, hi - lo);
    }
    cout << ans;
    return 0;
}
