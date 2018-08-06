#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

const int N = 100010;

typedef long long ll;

namespace T {

int n, fa[110], x[110], y[110];

int get(int x) {
    return x == fa[x] ? x : fa[x] = get(fa[x]);
}

void main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d%d", &x[i], &y[i]);
    for(int i = 1 ; i <= n ; ++ i) fa[i] = i;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j < i ; ++ j) {
            if(x[i] == x[j] || y[i] == y[j]) {
                fa[get(i)] = get(j);
            }
        }
    }
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) ans += fa[i] == i;
    printf("%d\n", ans - 1);
}
}

int main() {
    T :: main();
}

