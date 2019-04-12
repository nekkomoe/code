#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

int n, a[N];
deque<int> q;

int main() {
    int T; scanf("%d", &T);
    while(T --) {
        q.clear();
        scanf("%d", &n);
        set<int> s;
        for(int i = 1 ; i <= n ; ++ i) {
            scanf("%d", &a[i]);
            s.insert(a[i]);
        }
        vector<int> ans;
        
        for(int i = 1 ; i <= n ; ++ i) {
            int mn = 0;
            while(q.size() && s.size() && (mn = min(min(q.front(), q.back()), a[i])) <= *s.begin()) {
                if(s.count(mn)) s.erase(mn);
                ans.push_back(mn);
                if(mn == q.front()) {
                    q.pop_front();
                } else if(mn == q.back()) {
                    q.pop_back();
                } else {
                    s.erase(a[i]);
                    a[i] = 1e9 + 10;
                }
            }
            if(a[i] == *s.begin()) {
                ans.push_back(a[i]);
                s.erase(a[i]);
            } else if(s.count(a[i])) {
                s.erase(a[i]);
                q.push_back(a[i]);
            }
        }
        
        while(q.size()) {
            if(q.front() < q.back()) {
                ans.push_back(q.front());
                q.pop_front();
            } else {
                ans.push_back(q.back());
                q.pop_back();
            }
        }
        
        for(int x: ans) {
            printf("%d ", x);
        }
        puts("");
    }
}
