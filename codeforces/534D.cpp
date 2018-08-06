#include "bits/stdc++.h"
using namespace std;
const int N = 2e5 + 10;
vector<int> ans, bak[N];
int n;
void ns() { puts("Impossible"); exit(0); }
int main() {
    scanf("%d", &n);
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x);
        bak[x].push_back(i);
    }
    int now = 0;
    while(ans.size() != n) {
        if(bak[now].size()) {
            ans.push_back(bak[now].back());
            bak[now].pop_back();
            ++ now;
        } else {
            while(now - 3 >= 0 && bak[now].empty()) now -= 3;
            if(bak[now].empty()) ns();
            ans.push_back(bak[now].back());
            bak[now].pop_back();
            ++ now;
        }
    }
    if(ans.size() == n) {
        puts("Possible");
        for(int i = 0 ; i < ans.size() ; ++ i) printf("%d ", ans[i]);
        puts("");
    } else {
        ns();
    }
}
