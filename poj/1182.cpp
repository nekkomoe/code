#include <iostream>
#include <cstdio>
using namespace std;
int n,k,fa[100020],w[100020],lie,d,x,y;
pair<int,int> getf(int x)
{
	if(fa[x]==x)return make_pair(x,0);
	pair<int,int> a=getf(fa[x]);
	a.second=(a.second+w[x])%3;
	fa[x]=a.first;
	w[x]=a.second;
	return a;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=k;i++)
	{
		scanf("%d%d%d",&d,&x,&y);
		//for(int i=1;i<=n;i++)getf(i);
		//cout<<i<<' '<<getf(1).second<<endl;
		//cout<<i<<' '<<getf(1).second<<endl;
		if((d==2 && x==y) || x>n || y>n){
			//cout<<i<<' '<<"lie 1!"<<endl;
			lie++;continue;}
		if(d==1)
		{
			if(getf(x).first==getf(y).first)
			{
				if(getf(x).second!=getf(y).second){
			//		cout<<i<<' '<<"lie 2!"<<endl;
					lie++;continue;}
			}else{
				pair<int,int> a=getf(x);
				fa[a.first]=y;
				w[a.first]=(3-a.second)%3;
				getf(x);
			}
		}else{
			if(getf(x).first==getf(y).first)
			{
			//	cout<<getf(fa[x]).second<<' '<<getf(fa[y]).second<<endl;
				if((getf(x).second+1)%3!=getf(y).second){
			//		cout<<i<<' '<<"lie 3!"<<endl;
					lie++;continue;}
			}else{
				pair<int,int> a=getf(x);
				fa[a.first]=y;
				w[a.first]=(2-a.second)%3;	
				getf(x);
			}
		}
	}
	printf("%d",lie);
	return 0;
}
