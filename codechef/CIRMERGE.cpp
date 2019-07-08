// 百度的……

#include <bits/stdc++.h>
using namespace std;
const int maxn=1010;
typedef long long ll;
ll dp[maxn][maxn];
ll sum[maxn];
int a[maxn];
int main()
{
    int n,x;
    int t; scanf("%d", &t);
    while(t --){
        scanf("%d",&n);
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            sum[i]=sum[i-1]+a[i];
            dp[i][i]=0;
        }
 
        int in=1;
        for(int i=n+1;i<=2*n;i++) {
            sum[i]=(sum[i-1]+a[in++]);
            dp[i][i]=0;
        }
 
        for(int len=2;len<=n;len++)
        {
            for(int i=1;i<=2*n;i++)
            {
                int j=i+len-1;
                if(j>n*2) break;
                for(int k=i;k<j;k++)
                {
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+(sum[j]-sum[i-1]));
                }
            }
        }
        ll MAX=0x3f3f3f3f3f3f3f3fll;
        for(int i=1;i<=n;i++) {
            MAX=min(dp[i][i+n-1],MAX);
        }
        printf("%lld\n",MAX);
    }
}
