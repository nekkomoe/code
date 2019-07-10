#include <bits/stdc++.h>
using namespace std;

void runprog() {
    int n; scanf("%d", &n);
//    assert(1 <= n && n <= 100); // 20%
    
    unordered_map<int, int> coef;
    for(int i = 1 ; i <= n ; ++ i) {
        int j, f; scanf("%d%d", &j, &f);
        assert(0 <= j && j <= int(1e9));
        assert(-20000 <= f && f <= 20000);
        
//        assert(0 <= j && j <= 100); // 20%
//        assert(0 <= j && j <= int(1e5)); // 50%

        coef[j] += f;
    }

//    assert(coef.size() == n); // 另外 20%，i互不相同

    int ans = 0;
    for(auto t: coef) {
        if(t.second) {
            ++ ans;
        }
    }
    printf("%d\n", ans);
}

int main() {
    int t; scanf("%d", &t);
    assert(1 <= t && t <= 5);
    while(t --) {
        runprog();
    }
}
