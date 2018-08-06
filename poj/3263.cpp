#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n, i, h, r, c[N];

set<pair<int, int> > vis;

int main() {
    scanf("%d%d%d%d", &n, &i, &h, &r);
    for(int i = 1 ; i <= r ; ++ i) {
        int a, b; scanf("%d%d", &a, &b);
        if(a > b) swap(a, b);
        if(vis.find(make_pair(a, b)) == vis.end()) {
            -- c[a + 1], ++ c[b];
            vis.insert(make_pair(a, b));
        }
    }
    for(int i = 1 ; i <= n ; ++ i) printf("%d\n", h + (c[i] += c[i - 1]));
}

