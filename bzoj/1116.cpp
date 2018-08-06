#include <cstdio>

const int N = 200010 * 2;

int n, m;

int fa[N], tag[N];

int getf(int x) { return x == fa[x] ? x : fa[x] = getf(fa[x]); }

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) fa[i] = i;
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        int p = getf(u), q = getf(v);
        if(p != q) fa[p] = q, tag[q] = (tag[p] || tag[q]);
        else tag[p] = 1;
    }
    for(int i = 1 ; i <= n ; ++ i) if(!tag[getf(i)]) return puts("NIE"), 0;
    puts("TAK");
}

