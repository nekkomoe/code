#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <set>
 
using namespace std;
 
int x,y,n;
 
double f(double x,double y,int n,double ret=10000000){
    if(n==1)return x>y?x/y:y/x;
    double a=x/n,b=y/n;
    for(int i=1;i<n;i++)
        ret=min(ret,min(max(f(a*i,y,i),f(x-a*i,y,n-i)),max(f(x,b*i,i),f(x,y-b*i,n-i))));
    return ret;
}
 
int main(){
    scanf("%d%d%d",&x,&y,&n);
    printf("%.6f\n",f(x,y,n));
}
