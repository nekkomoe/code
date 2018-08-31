#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, sg[N], a[N];
void calc(int x) {
//    cout << "calc in " << x << endl;
    if(sg[x] != -1) return ;
    else if(x == 0) sg[x] = 0;
    else {
        vector<int> tmp;
        for(int i = 1 ; i * i <= x ; ++ i) {
            if(x % i) continue;
            calc(x - i), calc(x - x / i);
            tmp.push_back(sg[x - i]);
            tmp.push_back(sg[x - x / i]);
        }
        sort(tmp.begin(), tmp.end()), tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
        for(int i = 0 ; i < tmp.size() ; ++ i) {
            if(i != tmp[i]) {
                sg[x] = i;
                break;
            }
        }
        if(sg[x] == -1) sg[x] = tmp.size();
//        cout << "sg[" << x << "] = " << sg[x] << ": "; for(int i = 0 ; i < tmp.size() ; ++ i) cout << tmp[i] << ' '; cout << endl;
    }
}
int pre[N], sub[N];
int main() {
    for(int i = 0 ; i < N ; ++ i) sg[i] = -1;
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), calc(a[i]);
    for(int i = 1 ; i <= n ; ++ i) pre[i] = pre[i - 1] ^ sg[a[i]];
    for(int i = n ; i >= 1 ; -- i) sub[i] = sub[i + 1] ^ sg[a[i]];
    int ans = 0;
    if(pre[n]) {
        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = 1 ; j * j <= a[i] ; ++ j) {
                if(a[i] % j) continue;
                if((pre[i - 1] ^ sub[i + 1] ^ sg[a[i] - j]) == 0) ++ ans;
                if(j != a[i] / j) if((pre[i - 1] ^ sub[i + 1] ^ sg[a[i] - a[i] / j]) == 0) ++ ans;
            }
        }
    }
    printf("%d\n", ans);
}
