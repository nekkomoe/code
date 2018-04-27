#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;
 
double x[50],y,f[50][50],s[50];
int n;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lf",&x[i]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%lf",&y);
            f[i][j]=2*(y-x[j]);
            f[i][n+1]+=y*y-x[j]*x[j];
        }
    }   
    for(int i=1;i<=n;i++){
        int r=i;
        for(int j=i+1;j<=n;j++)
            if(fabs(f[j][i])>fabs(f[r][i]))
                r=j;
        for(int j=1;j<=n+1;j++)swap(f[r][j],f[i][j]);
        for(int k=i+1;k<=n;k++){
            double t=f[k][i]/f[i][i];
            for(int j=i;j<=n+1;j++)f[k][j]-=t*f[i][j];
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=i+1;j<=n;j++)
            f[i][n+1]-=f[j][n+1]*f[i][j];
        f[i][n+1]/=f[i][i];
    }
    for(int i=1;i<=n-1;i++)printf("%.3f ",f[i][n+1]);
    printf("%.3lf\n",f[n][n+1]);
}
