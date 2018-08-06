#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=55;
  
int in[maxn][maxn],vis[maxn];
int p[maxn],n,ans;
  
inline int getans() {
    int ret = 1;
    memset(vis,0,sizeof(vis)) , vis[p[1]] = 1;
    for(int i=2,fail;i<=n;i++) {
        fail = 0;
        for(int j=1;j<i;j++)
            if( vis[p[j]] && !in[p[j]][p[i]] ) {
                fail = 1;
                break;
            }
        if( !fail ) vis[p[i]] = 1 , ++ret;
    }
    return ret;
}
  
int main() {
srand((unsigned long long) new char);
 
    static int x,y;
    scanf("%d",&n);
    while( scanf("%d%d",&x,&y) == 2 ) in[x][y] = in[y][x] = 1;
    for(int i=1;i<=n;i++) p[i] = i;
    for(int i=1;i<=100000;i++) {
        std::random_shuffle(p+1,p+1+n);
        ans = std::max( ans , getans() );
    }
    printf("%d\n",ans);
    return 0;
}

