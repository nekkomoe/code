#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

int n, d, m;
char str[N];
pair<pair<int, int>, pair<int, int> > rel[N];
vector<int> g[N];
void lk(int u, int v) {
    g[u].push_back(v);
}
int tra[N][3];

stack<int> sta;
int ins[N], bel[N], cnt;
int dfn[N], low[N], clk;

void dfs(int u) {
    dfn[u] = low[u] = ++ clk;
    sta.push(u), ins[u] = 1;
    for(int i = 0 ; i < g[u].size() ; ++ i) {
        int v = g[u][i];
        if(!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        int v; ++ cnt;
        do {
            v = sta.top(); sta.pop(); ins[v] = 0;
            bel[v] = cnt;
        } while(v != u);
    }
}
int rev[N];
void runprog() {
    cnt = clk = 0;

    for(int i = 1 ; i <= 2 * n ; ++ i) {
        g[i].clear();
        bel[i] = dfn[i] = low[i] = 0;
    }
    for(int i = 1, j = 1 ; i <= n ; ++ i, j += 2) {
        int t = j;
        rev[j] = j + 1;
        rev[j + 1] = j;
        for(int k = 'a' ; k <= 'c' ; ++ k) {
            if(k != str[i]) {
                tra[i][k - 'a'] = t;
                ++ t;
            }
        }
    }

    for(int t = 1 ; t <= m ; ++ t) {
        int i = rel[t].first.first, hi = rel[t].first.second;
        int j = rel[t].second.first, hj = rel[t].second.second;
        if(hi != str[i] && hj != str[j]) {
            int u = tra[i][hi - 'a'];
            int v = tra[j][hj - 'a'];
            lk(u, v);
            lk(rev[v], rev[u]);
        } else if(hi != str[i] && hj == str[j]) {
            int u = tra[i][hi - 'a'];
            lk(u, rev[u]);
        }
    }

    for(int i = 1 ; i <= 2 * n ; ++ i) {
        if(!dfn[i]) {
            dfs(i);
        }
    }

    for(int i = 1, j = 1 ; i <= n ; ++ i, j += 2) {
        if(bel[j] == bel[j + 1]) {
            return ;
        }
    }

    for(int i = 1, j = 1 ; i <= n ; ++ i, j += 2) {
        if(str[i] == 'a') {
            putchar(bel[j] < bel[j + 1] ? 'B' : 'C');
        } else if(str[i] == 'b') {
            putchar(bel[j] < bel[j + 1] ? 'A' : 'C');
        } else if(str[i] == 'c') {
            putchar(bel[j] < bel[j + 1] ? 'A' : 'B');
        }
    }
    exit(0);
}

int main() {
    scanf("%d%d%s", &n, &d, str + 1);
    scanf("%d", &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int a, c; char b[10], d[10];
        scanf("%d%s%d%s", &a, b, &c, d);
        b[0] = b[0] - 'A' + 'a';
        d[0] = d[0] - 'A' + 'a';
        rel[i] = make_pair(make_pair(a, (int) b[0]), make_pair(c, (int) d[0]));
    }
    vector<int> pos;
    for(int i = 1 ; i <= n ; ++ i) {
        if(str[i] == 'x') {
            pos.push_back(i);
        }
    }
    for(int i = 0 ; i < (1 << d) ; ++ i) {
        for(int j = 0 ; j < pos.size() ; ++ j) {
            if((i >> j) & 1) {
                str[pos[j]] = 'a';
            } else {
                str[pos[j]] = 'b';
            }
        }
        runprog();
    }
    puts("-1");
}

