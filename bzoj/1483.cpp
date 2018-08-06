#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
 
using namespace std;
 
const int N = 1000010;
 
vector<int> pos[N];
 
int n, m, c[N], f[N], ans;
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &c[i]);
        pos[c[i]].push_back(i);
        f[c[i]] = c[i];
        if(c[i] != c[i - 1]) ++ ans;
    }
    for(int i = 1, op, x, y ; i <= m ; ++ i) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &x, &y);
            if(x != y) {
                if(pos[f[x]].size() > pos[f[y]].size()) swap(f[x], f[y]);
                x = f[x];
                y = f[y];
                for(int i = 0 ; i < pos[x].size() ; ++ i) {
                    int z = pos[x][i];
                    if(c[z - 1] == y) -- ans;
                    if(c[z + 1] == y) -- ans;
                    pos[y].push_back(z);
                }
                for(int i = 0 ; i < pos[x].size() ; ++ i) {
                    int z = pos[x][i];
                    c[z] = y;
                }
                pos[x].clear();
            }
        } else {
            printf("%d\n", ans);
        }
    }
}
