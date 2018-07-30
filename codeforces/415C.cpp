#include "bits/stdc++.h"
using namespace std;
int n, k, flag;
set<int> vis;
int main() {
    scanf("%d%d", &n, &k);
    if(n & 1) flag = 1, -- n;
    if(n == 0) {
        puts(k == 0 ? "1000000000" : "-1");
    } else {
        int d = k - (n - 2) / 2;
        if(d <= 0) {
            puts("-1");
        } else {
            int tot = 1000000000 - 1;
            if(d != 1) printf("%d %d ", d, d * 2), vis.insert(d), vis.insert(d * 2);
            else printf("%d %d ", tot, tot - 1), vis.insert(tot), vis.insert(tot - 1), tot -= 2;
            for(int i = 1 ; i <= n - 2 ; i += 2) {
                while(vis.find(tot) != vis.end() || vis.find(tot - 1) != vis.end()) tot -= 2;
                printf("%d %d ", tot, tot - 1);
                vis.insert(tot), vis.insert(tot - 1);
                tot -= 2;
            }
            if(flag) printf("1000000000");
            puts("");
        }
    }
}
