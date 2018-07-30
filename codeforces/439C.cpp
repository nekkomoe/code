#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int n, k, p, a[N];
vector<int> ans[N], odd, even;
void ns() { puts("NO"); exit(0); }
int main() {
    scanf("%d%d%d", &n, &k, &p), p = k - p;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        if(a[i] & 1) odd.push_back(a[i]);
        else even.push_back(a[i]);
    }
    for(int i = 1 ; i <= p ; ++ i) {
        if(odd.empty()) ns();
        ans[i].push_back(odd.back()), odd.pop_back();
    }
    if(odd.size() & 1) ns();
    for(int i = p + 1 ; i <= k ; ++ i) {
        if(even.size()) {
            ans[i].push_back(even.back());
            even.pop_back();
        } else if(odd.size()) {
            ans[i].push_back(odd.back());
            odd.pop_back();
            ans[i].push_back(odd.back());
            odd.pop_back();
        } else {
            ns();
        }
    }
    while(odd.size()) ans[1].push_back(odd.back()), odd.pop_back();
    while(even.size()) ans[1].push_back(even.back()), even.pop_back();
    puts("YES");
    for(int i = 1 ; i <= k ; ++ i) {
        printf("%d ", (int) ans[i].size());
        for(int j = 0 ; j < ans[i].size() ; ++ j) {
            printf("%d ", ans[i][j]);
        }
        puts("");
    }
}
