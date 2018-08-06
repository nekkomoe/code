#include <bits/stdc++.h>
using namespace std;
 
int D, G, p[20], c[20], vis[20];
 
struct T {
    int p, c;
};
 
int sol() {
    int res = 0, rem = G;
    for(int i = 1 ; i <= D ; ++ i) {
        if(vis[i]) {
            res += p[i];
            rem -= 100 * i * p[i] + c[i];
        }
    }
    for(int i = D ; i >= 1 ; -- i) {
        if(vis[i] == 0) {
            if(rem > 0) {
                if(rem - 100 * i * p[i] >= 0) {
                    // return 1000000000;
                    rem -= 100 * i * p[i] + c[i];
                    res += p[i];                 
                } else {
                    // rem - 100 * i * x >= 0
                    // x <= rem / (100 * i)
                    int x = rem / (100 * i);
                    rem -= 100 * i * x;
                    res += x;
                }
            }
        }
    }
    return rem <= 0 ? res : 1000000000;
}
 
int main() {
    scanf("%d%d", &D, &G);
    for(int i = 1 ; i <= D ; ++ i) {
        scanf("%d%d", &p[i], &c[i]);
    }
    int ans = 1000000000;
    for(int s = 0 ; s < (1 << D) ; ++ s) {
        for(int i = 1 ; i <= D ; ++ i) vis[i] = ((s >> (i - 1)) & 1);
        ans = min(ans, sol());
        // cout << s << ' ' << sol() << endl;
    }
    printf("%d\n", ans);
}
