//并查集

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 1e5 + 10;

int T, n, m, a, b;

char op[10];

int fa[N], rk[N];

int find(int x) {
    if(x == fa[x]) return x;
    int root = find(fa[x]);
    rk[x] ^= rk[fa[x]];
    return fa[x] = root;
}

void merge(int a, int b) {
    int x = find(a), y = find(b);
    fa[x] = y;
    rk[x] = ~(rk[a] ^ rk[b]);
}

int main() {
    scanf("%d", &T);
    while(T --) {
        scanf("%d%d", &n, &m);
        for(int i = 1 ; i <= n ; i ++) fa[i] = i, rk[i] = 0;
        for(int i = 1 ; i <= m ; i ++) {
            scanf("%s%d%d", op, &a, &b);
            if(op[0] == 'D') {
                merge(a, b);
            } else {
                if(n == 2) {
                    puts("In different gangs.");
                } else if(find(a) == find(b)) {
                    if(rk[a] == rk[b]) {
                        puts("In the same gang.");
                    } else {
                        puts("In different gangs.");
                    }
                } else {
                    puts("Not sure yet.");
                }
            }
        }
    }
}
