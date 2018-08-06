#include <bits/stdc++.h>

using namespace std;

const int N = 30010;

int n, cnt = 1, ch[N][2], fail[N], ep[N], vis[N], ins[N];

char s[N];

vector<int> G[N];

int dfs(int u) {
    ins[u] = 1;
    for(int i = 0 ; i < 2 ; ++ i) {
        int v = ch[u][i];
        if(ins[v] || (!vis[v] && !ep[v] && (vis[v] = 1) && dfs(v))) return 1;
    }
    return ins[u] = 0;
}

int main() {
    ch[0][0] = ch[0][1] = 1;
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", s + 1);
        for(int j = 1, p = 1 ; s[j] ; ++ j) {
            int c = s[j] - '0';
            if(!ch[p][c]) ch[p][c] = ++ cnt;
            p = ch[p][c];
            if(!s[j + 1]) ep[p] = 1;
        }
    }
    queue<int> q;
    q.push(1);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = 0 ; i < 2 ; ++ i) {
            int v = ch[u][i];
            if(v) {
                int k = fail[u];
                while(!ch[k][i]) k = fail[k];
                fail[v] = ch[k][i];
                ep[v] |= ep[fail[v]];
                q.push(v);
            } else ch[u][i] = ch[fail[u]][i];
        }
    }
    if(dfs(1)) puts("TAK"); else puts("NIE");
}
