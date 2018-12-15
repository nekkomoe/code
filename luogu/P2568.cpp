#include <bits/stdc++.h>
 
using namespace std;
  
const int N = 10000010;
 
int v[N], prime[N], pTot, n, phi[N];
 
long long ans, f[N];
  
int main(){
    scanf("%d", &n);
    for(int i = (f[1] = phi[1] = 1) + 1 ; i <= n ; ++ i) {
        if(!v[i]) prime[++ pTot] = (phi[i] = i - 1) + 1;
        for(int j = 1 ; j <= pTot && i * prime[j] <= n ; ++ j) {
            v[i * prime[j]] = 1;
            if(i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
        f[i] = f[i - 1] + phi[i];
    }
    for(int i = 1 ; i <= pTot ; ++ i) ans += f[n / prime[i]];
    printf("%lld\n", ans * 2 - pTot);
}
