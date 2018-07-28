#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <string>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
 
int ans,n,m,k,nxt[50];
struct M{
    int T[30][30];
    M(){memset(T,0,sizeof(T));}
    M MUL (M b,int l1,int l2,int l3){
        M ret;
        for(int i=0;i<l1;i++)
            for(int j=0;j<l3;j++)
                for(int k_=0;k_<l2;k_++)
                    ret.T[i][j]=(ret.T[i][j]+T[i][k_]*b.T[k_][j])%k;
        return ret;
    }
}f,ff;
M mul(M a,int len,int b){
    M ret;
    for(int i=0;i<len;i++)ret.T[i][i]=1;
    while(b){
        if(b&1)ret=ret.MUL(a,len,len,len);
        a=a.MUL(a,len,len,len);
        b>>=1;
    }
    return ret;
}
char str[50];
int main(){
    scanf("%d%d%d%s",&n,&m,&k,str+1);
    for(int i=2,j=0;i<=m;i++){
        while(j&&str[j+1]!=str[i])j=nxt[j];
        nxt[i]=(j+=str[j+1]==str[i]);
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<=9;j++){
            int t=i;
            while(t&&str[t+1]!=j+'0')t=nxt[t];
            if(str[t+1]==j+'0')f.T[i][t+1]++;
            else f.T[i][0]++;
        }
    }
    ff.T[0][0]=1;
    f=mul(f,m,n);
    ff=ff.MUL(f,1,m,m);
    for(int i=0;i<m;i++)(ans+=ff.T[0][i])%=k;
    printf("%d\n",ans);
}
