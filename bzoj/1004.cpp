#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
 
int Sr,Sg,Sb,m,p,n,cnt,a[100],v[100],size[100],f[30][30][30],ans;
 
int solve(){
    memset(v,0,sizeof(v));
    memset(size,0,sizeof(size));
    memset(f,0,sizeof(f));
    cnt=0;
    for(int i=1;i<=n;i++){
        if(!v[i]){
            int j=i;
            cnt++;
            do{
                v[j]=1;
                size[cnt]++;
                j=a[j];
            }while(!v[j]);
        }
    }
    f[0][0][0]=1;
    for(int i=1;i<=cnt;i++){
        for(int a=Sr;a>=0;a--){
            for(int b=Sg;b>=0;b--){
                for(int c=Sb;c>=0;c--){
                    if(a>=size[i])(f[a][b][c]+=f[a-size[i]][b][c])%=p;
                    if(b>=size[i])(f[a][b][c]+=f[a][b-size[i]][c])%=p;
                    if(c>=size[i])(f[a][b][c]+=f[a][b][c-size[i]])%=p;
                }
            }
        }
    }
    return f[Sr][Sg][Sb];
}
 
int mul(int a,int b){
    int ret=1;
    while(b){
        if(b&1)(ret*=a)%=p;
        (a*=a)%=p;
        b>>=1;
    }
    return ret;
}
 
int main(){
    scanf("%d%d%d%d%d",&Sr,&Sg,&Sb,&m,&p);
    n=Sr+Sb+Sg;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++)
            scanf("%d",&a[j]);
        (ans+=solve())%=p;
    }
    for(int i=1;i<=n;i++)a[i]=i;
    (ans+=solve())%=p;
    printf("%d\n",(ans*mul(m+1,p-2))%p);
}
