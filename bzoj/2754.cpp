#include <bits/stdc++.h>

using namespace std;

int inline read() {
    int ret = 0;
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) ret = ret * 10 + c - '0', c = getchar();
    return ret;
}

const int N = 2e5;

int n, m, ans1[N], ans2[N], vis1[N], vis2[N], cnt = 1, fail[N];

vector<int> a[N], st[N], tmp1, tmp2;

map<int, int> ch[N];

void ins(int id) {
    int x, p = 1;
    for(int i = read() ; i ; -- i) {
        x = read();
        if(!ch[p][x]) ch[p][x] = ++ cnt;
        p = ch[p][x];
    }
    st[p].push_back(id);
}

void build() {
    queue<int> q;
    q.push(1);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(map<int, int> :: iterator it = ch[u].begin() ; it != ch[u].end() ; ++ it) {
            int c = it -> first, v = it -> second, t = fail[u];
            while(!ch[t][c]) t = fail[t];
            fail[v] = ch[t][c];
            q.push(v);
        }
    }
}

void fetch(int id, int p) {
    for(int i = p ; i ; i = fail[i]) {
        if(!vis1[i]) {
            vis1[i] = 1;
            tmp1.push_back(i);
            for(int j = 0 ; j < st[i].size() ; ++ j) {
                int x = st[i][j];
                if(!vis2[x]) {
                    vis2[x] = 1;
                    tmp2.push_back(x);
                    ans1[x] ++, ans2[id] ++;
                }
            }
        }
    }
}

void sol(int id) {
    int p = 1;
    for(int i = 0 ; i < a[id].size() ; ++ i) {
        int c = a[id][i];
        while(!ch[p][c]) p = fail[p];
        fetch(id, p = ch[p][c]);
    }
    for(int i = 0 ; i < tmp1.size() ; ++ i) vis1[tmp1[i]] = 0;
    for(int i = 0 ; i < tmp2.size() ; ++ i) vis2[tmp2[i]] = 0;
    tmp1.clear(), tmp2.clear();
}

int main() {
    
    for(int i = -1 ; i <= 10000 ; ++ i) ch[0][i] = 1;
    
    n = read(), m = read();
    for(int i = 1, L ; i <= n ; ++ i) {
        L = read();
        while(L --) a[i].push_back(read());
        L = read();
        a[i].push_back(-1);
        while(L --) a[i].push_back(read());
    }
    for(int i = 1 ; i <= m ; ++ i) ins(i);
    build();
    for(int i = 1 ; i <= n ; ++ i) sol(i);
    for(int i = 1 ; i <= m ; ++ i) printf("%d\n", ans1[i]);
    for(int i = 1 ; i <= n ; ++ i) printf("%d", ans2[i]), (i < n && printf(" "));
}
