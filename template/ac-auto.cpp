#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>

using namespace std;

const int N = 1e6 + 10;

int cnt, nxt[N][30], fail[N], tot[N], ans, n;

char s[N];

queue<int> q;

void insert() {
    scanf("%s", s);
    int x = 0;
    for(int i = 0 ; s[i] ; ++ i) {
        int c = s[i] - 'a';
        if(!nxt[x][c]) nxt[x][c] = ++ cnt;
        x = nxt[x][c];
    }
    ++ tot[x];
}

void bfs() {
    for(int i = 0 ; i < 26 ; ++ i) {
        if(nxt[0][i]) {
            fail[nxt[0][i]] = 0;
            q.push(nxt[0][i]);
        }
    }
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = 0 ; i < 26 ; ++ i) {
            int v = nxt[u][i];
            if(!v) nxt[u][i] = nxt[fail[u]][i];
            else {
                fail[v] = nxt[fail[u]][i];
                q.push(v);
            }
        }
    }
}

void sol() {
   scanf("%s", s);
   int u = 1;
   for(int i = 0 ; s[i] ; ++ i) {
        u = nxt[u][s[i] - 'a'];
        int v = u;
        while(v && ~tot[v]) {
            ans += tot[v];
            tot[v] = -1;
            v = fail[v];
        }
   }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        insert();
    }
    bfs();
    sol();
    printf("%d\n", ans);
    return 0;
}
