#include <bits/stdc++.h>
#define MAXN 400005
using namespace std;
int n,m;
struct node{
	int to,w,next;
}a[MAXN];
int head[MAXN];
int top;
void add(int u,int v,int w){
	a[++top].to=v;
	a[top].w=w;
	a[top].next=head[u];
	head[u]=top;
}
priority_queue <pair<int,int > > q;
bool bo[MAXN];
int dis[MAXN];
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	q.push(make_pair(0,1));
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	while(!q.empty()){
		int u=q.top().second;
		int w=-q.top().first;
		q.pop();
		if(bo[u]) continue;
		bo[u]=1;
		for(int i=head[u];i;i=a[i].next){
			int v=a[i].to;
			int w1=a[i].w;
			if(bo[v]) continue;
			if(dis[v]>max(w,w1)) dis[v]=max(w,w1);
			q.push(make_pair(-dis[v],v));
		}

	}
	cout<<dis[n];
	
	return 0;
} 
