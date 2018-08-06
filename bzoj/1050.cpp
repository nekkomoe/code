#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
 
struct EDGE{
    int u,v,c;
    bool operator < (EDGE b) const{
        return c<b.c;
    }
}e[6000];
int fa[600],n,m,ansmax=1,ansmin,st,en;
int f(int x){return x==fa[x]?x:fa[x]=f(fa[x]);}
void init(){for(int i=1;i<=n;i++)fa[i]=i;}
int gcd(int a,int b){return b?gcd(b,a%b):a;}
 
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].c);
    scanf("%d%d",&st,&en);
    sort(e,e+m);
    for(int i=0,Min,Max,x;i<m;i=x+1){
        Min=Max=-1;
        init();
        for(x=i;x<m;x++){
            fa[f(e[x].u)]=f(e[x].v);
            if(f(st)==f(en)){
                Max=e[x].c;
                break;}}
        if(Max==-1){if(!ansmin)return 0&puts("IMPOSSIBLE");else break;}
        init();
        for(;x>=0;x--){
            fa[f(e[x].u)]=f(e[x].v);
            if(f(st)==f(en)){
                Min=e[x].c;
                break;}}
        if(Min==-1){if(!ansmin)return 0&puts("IMPOSSIBLE");else break;}
        int g=gcd(Max,Min);Max/=g,Min/=g;
        if(ansmax*Min>ansmin*Max)ansmax=Max,ansmin=Min;
    }
    ansmin==1?printf("%d\n",ansmax):printf("%d/%d\n",ansmax,ansmin);
}
