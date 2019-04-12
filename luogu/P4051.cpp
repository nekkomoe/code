#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <set>
#include <string>
 
using namespace std;
 
const int N=1000000;
char str[N];
int ranks[N],tmp[N],sa[N],k;
bool cmp(int i,int j){
    if(ranks[i]!=ranks[j])return ranks[i]<ranks[j];
    return ranks[i+k]<ranks[j+k];
}
 
int main(){
    memset(ranks,-1,sizeof(ranks));
    scanf("%s",str);
    int n=strlen(str);
    for(int i=0;i<n;i++)str[i+n]=str[i];
    n<<=1;
    for(int i=0;i<=n;i++)sa[i]=i,ranks[i]=i<n?str[i]:-1;
    for(k=1;k<=n;k<<=1){
        sort(sa,sa+n,cmp);
        tmp[sa[0]]=0;
        for(int i=1;i<=n;i++)tmp[sa[i]]=tmp[sa[i-1]]+cmp(sa[i-1],sa[i]);
        for(int i=0;i<=n;i++)ranks[i]=tmp[i];
    }
    for(int i=0;i<n;i++)
        if(sa[i]<=(n>>1)-1)
            putchar(str[sa[i]+(n>>1)-1]);
}
