#include <bits/stdc++.h>
using namespace std;
const int N = 25;

queue<pair<int, int> > q;
int n, a[N], cnt;
vector<int> G[N];
int mx[N], ans[N];

namespace xuanxuepianfen {
    void dfs(int u) {
    //    cout << u << "{";
        ans[u] = mx[u] = 0;
        for(int i = 0 ; i < G[u].size() ; ++ i) {
            int v = G[u][i];
            dfs(v);
            ans[u] = max(ans[u], max(ans[v], mx[u] + mx[v] + 1));
            mx[u] = max(mx[u], mx[v] + 1);
            
        }
        ans[u] = max(ans[u], mx[u]);
    //    cout << "}";
    }
    void sol() {
        sort(a + 1, a + 1 + n, greater<int>());
        for(int i = 1 ; i <= n ; ++ i) {
            ++ cnt;
            if(q.empty()) {
                q.push(make_pair(cnt, a[i]));
            } else {
                while(q.front().second == 0) q.pop();
                q.front().second --;
                G[q.front().first].push_back(cnt);
                q.push(make_pair(cnt, a[i] - 1));
            }
        }
        dfs(1);
        printf("%d\n", ans[1]);
    }
}
int main() {
    scanf("%d", &n);
    int sum = 0;
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), sum += a[i];
    if(sum != 2 * (n - 1)) return puts("-1"), 0;
    int ans = n - 1;
    for(int i = 1 ; i <= n ; ++ i) ans -= max(2, a[i]) - 2;
    printf("%d\n", ans);
}
