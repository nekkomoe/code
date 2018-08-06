//dp

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int f[500][50], v, p, pos[500];

int w(int l, int r) {
    int vi = (l + r) / 2, ret = 0;
    for(int i = l ; i <= r ; i ++) {
        ret += abs(pos[vi] - pos[i]);
    }
    return ret;
}

int main() {
    scanf("%d%d", &v, &p);
    for(int i = 1 ; i <= v ; i ++) {
        scanf("%d", &pos[i]);
    }
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    sort(pos + 1, pos + 1 + v);
    for(int i = 1 ; i <= v ; i ++) {
        for(int j = 1 ; j <= min(i, p) ; j ++) {
            for(int k = 0 ; k < i ; k ++) {
                f[i][j] = min(f[i][j], f[k][j - 1] + w(k + 1, i));
            }
        }
    }
    printf("%d\n", f[v][p]);
}
