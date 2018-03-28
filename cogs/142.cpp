#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define FN "icow"

const int N = 1010;

int n, T, r[N], vis[N];

int main() {
    freopen(FN ".in", "r", stdin);
    freopen(FN ".out", "w", stdout);
    scanf("%d%d", &n, &T);
    for(int i = 1 ; i <= n ; i ++) {
        scanf("%d", &r[i]);
    }
    if(n == 1) {
        for(int i = 1 ; i <= T ; i ++) {
            puts("1");
        }
        return 0;
    }
    for(int i = 1 ; i <= T ; i ++) {
        int id = 0;
        for(int j = 1 ; j <= n ; j ++) {
            if(r[id] < r[j]) {
                id = j;
            }
        }
        vis[id] = 1;
        printf("%d\n", id);
        int w = r[id] / (n - 1);
        int md = r[id] % (n - 1);
        r[id] = 0;
        for(int j = 1 ; j <= n ; j ++) {
            if(j != id) {
                r[j] += w;
                if(md) {
                    md --;
                    r[j] ++;
                }
            }
        }
    }
}
