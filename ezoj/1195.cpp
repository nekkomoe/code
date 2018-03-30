%:pragma GCC optimize(2)
%:pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100010;

int ch[N][30], tot = 1, root = 1, n, m;

char s[N];

struct D { int rat, id; };

bool operator < (D a, D b) { return a.rat > b.rat; }

bool operator == (D a, D b) { return a.rat == b.rat; }

vector<D> vec[N];

struct T { int id, t; };

vector<T> tag[N];

int cnt[N];

vector<int> ans[N];

void ins(int rat, int id) {
    int p = root;
    for(int i = 1 ; s[i] ; ++ i) {
        int c = s[i] - 'a';
        if(!ch[p][c]) ch[p][c] = ++ tot;
        vec[p].push_back((D) { rat, id });
        p = ch[p][c];
    }
    vec[p].push_back((D) { rat, id });
}

void add(int id, int t) {
    int p = root;
    for(int i = 1 ; s[i] ; ++ i) {
        int c = s[i] - 'a';
        if(!ch[p][c]) return ;
        p = ch[p][c];
    }
    tag[p].push_back((T) { id, t });
}

void sol(int u = 1) {
    for(int i = 0 ; i < 26 ; ++ i) {
        int v = ch[u][i];
        if(v) {
            sol(v);
        }
    }
    sort(vec[u].begin(), vec[u].end());
    vec[u].erase(unique(vec[u].begin(), vec[u].end()), vec[u].end());
    for(vector<T> :: iterator it = tag[u].begin() ; it != tag[u].end() ; ++ it) {
        int t = it -> t, id = it -> id;
        t = min(t, (int) vec[u].size());
        :: cnt[id] = vec[u].size();
        for(int i = 0 ; i < t ; ++ i) {
            ans[id].push_back(vec[u][i].id);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, rat, k ; i <= n ; ++ i) {
        scanf("%d%d", &rat, &k);
        for(int j = 1 ; j <= k ; ++ j) {
            scanf("%s", s + 1);
            ins(rat, i);
        }
    }
    for(int i = 1, t ; i <= m ; ++ i) {
        scanf("%d%s", &t, s + 1);
        add(i, t);
    }
    sol();
    for(int i = 1 ; i <= m ; ++ i) {
        if(ans[i].empty()) puts("0");
        else {
            printf("%d", cnt[i]);
            for(vector<int> :: iterator it = ans[i].begin() ; it != ans[i].end() ; ++ it) {
                printf(" %d", *it - 1);
            }
            puts("");
        }
    }
}

