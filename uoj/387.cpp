#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;

int n, m;

int head[N], rest[N], to[N], tot, sz[N], fa[N];

void add(int u, int v) { to[++ tot] = v, rest[tot] = head[u], head[u] = tot; }

namespace m_1 {
    void dfs(int u) {
        printf("1 %d \n", u);
        for(int i = head[u] ; i ; i = rest[i]) dfs(to[i]);
    }
    void sol() {
        printf("%d\n", n);
        dfs(1);
    }
}

namespace pianfen1 {
    struct T { int u; };
    bool operator < (T a, T b) { return sz[a.u] < sz[b.u]; }
    priority_queue<T> pq;
    vector<int> ans[N];
    int cnt;
    int sol() {
        for(int i = 2 ; i <= n ; ++ i) ++ sz[fa[i]];
        pq.push((T) { 1 });
        cnt = 0;
        while(pq.size()) {
            ++ cnt;
            for(int i = 1 ; i <= m ; ++ i) {
                if(pq.empty()) break;
                ans[cnt].push_back(pq.top().u);
                pq.pop();
            }
            for(int i = 0 ; i < ans[cnt].size() ; ++ i) {
                int u = ans[cnt][i];
                for(int j = head[u] ; j ; j = rest[j]) pq.push((T) { to[j] });
            }
        }
        return cnt;
    }
    void output() {
        printf("%d\n", cnt);
        for(int i = 1 ; i <= cnt ; ++ i) {
            printf("%d ", int(ans[i].size()));
            for(int j = 0 ; j < ans[i].size() ; ++ j) printf("%d ", ans[i][j]);
            puts("");
        }
    }
}

namespace pianfen2 {

    void fafa(int u) {
        sz[u] = 1;
        for(int i = head[u] ; i ; i = rest[i]) fafa(to[i]), sz[u] += sz[to[i]];
    }

    struct T { int u; };
    bool operator < (T a, T b) { return sz[a.u] < sz[b.u]; }
    priority_queue<T> pq;
    vector<int> ans[N];
    int cnt;
    int sol() {
        fafa(1);
        cnt = 0;
        pq.push((T) { 1 });
        while(pq.size()) {
            ++ cnt;
            for(int i = 1 ; i <= m ; ++ i) {
                if(pq.empty()) break;
                ans[cnt].push_back(pq.top().u);
                pq.pop();
            }
            for(int i = 0 ; i < ans[cnt].size() ; ++ i) {
                int u = ans[cnt][i];
                for(int j = head[u] ; j ; j = rest[j]) pq.push((T) { to[j] });
            }
        }
        return cnt;
    }
    void output() {
        printf("%d\n", cnt);
        for(int i = 1 ; i <= cnt ; ++ i) {
            printf("%d ", int(ans[i].size()));
            for(int j = 0 ; j < ans[i].size() ; ++ j) printf("%d ", ans[i][j]);
            puts("");
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 2 ; i <= n ; ++ i) {
        scanf("%d", &fa[i]);
        add(fa[i], i);
    }
    if(m == 1) {
        m_1 :: sol();
    } else {
        int ans1 = pianfen1 :: sol();
        int ans2 = pianfen2 :: sol();
        // assert(ans1 == ans2);
        // printf("%d           %d     %d\n", ans1 - ans2, ans1, ans2);
        if(ans1 < ans2) pianfen1 :: output();
        else pianfen2 :: output();
    }
}
