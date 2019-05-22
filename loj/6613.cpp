#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int ans[5];
priority_queue<ll> pq_big;
priority_queue<ll, vector<ll>, greater<ll> > pq_sma;
stack<ll> sta;
queue<ll> que;

int main() {
    for(int i = 1 ; i <= 4 ; ++ i) {
        ans[i] = 1;
    }
    int n; cin >> n;
    while(n --) {
        ll op, val; cin >> op >> val;
        if(op == 1) {
            que.push(val);
            sta.push(val);
            pq_big.push(val);
            pq_sma.push(val);
        } else {
            if(ans[1]) {
                if(que.size() && que.front() == val) que.pop();
                else ans[1] = 0;
            }
            if(ans[2]) {
                if(sta.size() && sta.top() == val) sta.pop();
                else ans[2] = 0;
            }
            if(ans[3]) {
                if(pq_big.size() && pq_big.top() == val) pq_big.pop();
                else ans[3] = 0;
            }
            if(ans[4]) {
                if(pq_sma.size() && pq_sma.top() == val) pq_sma.pop();
                else ans[4] = 0;
            }
        }
    }
    for(int i = 1 ; i <= 4 ; ++ i) {
        puts(ans[i] ? "Yes" : "No");
    }
}
