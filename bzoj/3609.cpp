#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <queue>
#include <cstdio>
#include <set>
using namespace std;
 
int t,n,m,ans,c;
int main(){
    scanf("%d",&t);
    while(t--)scanf("%d%d",&n,&m),printf("%c\n",'0'+!((n/m*(m-1)+n-n/m*m-(n-n/m*m>0))&1));
}
