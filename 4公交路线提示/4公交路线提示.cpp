#include <bits/stdc++.h>
#define MAXN 100010 
using namespace std;
map <string,int> strint;
map <int,string> intstr;
int num;
int cnt;
bool boo[MAXN];
bool boo2[MAXN];
bool boid[MAXN];
bool vis[MAXN];
int path[MAXN];
int d[MAXN];
vector <int> vestr[1000];//每条路线的所有站点 
vector <int> veint[12000];//站点所在的路线编号 
int parent[MAXN];//并查集 
int find(int p){
	while(p!=parent[p]){
		parent[p]=parent[parent[p]];
		p=parent[p];
	}
	return p;
}
struct node{
	int to,id,next;
}edge[MAXN];
int head[MAXN];
void add(int u,int v,int id){
	edge[++cnt].to=v;
	edge[cnt].id=id;
	edge[cnt].next=head[u];
	head[u]=cnt;
}
int ans;
vector <pair<int,int > > ansvect;
void dfs(int u,int v,int an,vector <pair<int,int > > vect){
	int len=veint[u].size();
	//bool bo=0;
	int id,ve;
	for(int i=0;i<len;i++){
		int leng=vestr[veint[u][i]].size();
		for(int j=0;j<leng;j++){
			if(vestr[veint[u][i]][j]==u){
				id=veint[u][i];
				ve=j;
				break;
			}
		}
		for(int j=0;j<leng;j++){
			if(vestr[veint[u][i]][j]==v){
				vect.push_back(make_pair(id,ve));
				vect.push_back(make_pair(veint[u][i],j));
				if(an<ans){
					ans=an;
					ansvect=vect;
				}
//				vect.pop_back();
//				vect.pop_back();
				return;
				//break;
			}
		}
	}
	boo[u]=1;
	for(int i=0;i<=20000;i++){
		boo2[i]=boo[i];
	}
	for(int i=0;i<len;i++){
//		if(boid[veint[u][i]]) continue;
//		boid[veint[u][i]]=1;
		int leng=vestr[veint[u][i]].size();
		for(int j=0;j<leng;j++){
			if(vestr[veint[u][i]][j]==u){
				id=veint[u][i];
				ve=j;
				break;
			}
		}
		for(int j=0;j<leng;j++){
			if(boo[vestr[veint[u][i]][j]]) continue;
			vect.push_back(make_pair(id,ve));
			vect.push_back(make_pair(veint[u][i],j));
			dfs(vestr[veint[u][i]][j],v,an+1,vect);
			for(int i=0;i<=20000;i++){
				boo[i]=boo2[i];
			}
			vect.pop_back();
			vect.pop_back();
		}
	}
}
void dijkstra(int u,int v){
	priority_queue <pair<int,int > > q;
	memset(vis,0,sizeof(vis));
	memset(d,0x3f,sizeof(d));
	memset(path,0,sizeof(path));
	//cout<<"**"<<d[0]<<"**"<<endl;
	q.push(make_pair(0,u));
	d[u]=0;
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=edge[i].next){
			int vv=edge[i].to;
			int id=edge[i].id;
			if(d[u]+1<d[vv]){
				d[vv]=d[u]+1;
				path[vv]=u;
				q.push(make_pair(-d[vv],vv));
			}
		}
	}
}
int main(){
	fstream fp;
	fp.open("南京公交线路.txt",ios::in);
	for(int i=0;i<MAXN;i++){
		parent[i]=i;
	}
	while(!fp.eof()){
		//cout<<"**";
		string str;
		getline(fp,str);
		int len=str.length();
		int i=0;
		int id=0;
		while('0'<=str[i]&&str[i]<='9'){
			id=(id<<1)+(id<<3)+str[i]-'0';
			i++;
		}
		//cout<<id<<endl;
		while(str[i]!=' '){
			i++;
		}
		while(str[i]==' '){
			i++;
		}
		int u=0,v=0;
		while(i<len){
			string s;
			while(str[i]!=','&&i<len){
				s+=str[i];
				i++;
			}
			if(strint.find(s)==strint.end()){
				strint[s]=++num;
				intstr[num]=s;
			}
			if(u==0){
				u=strint[s];
			}
			else{
				v=strint[s];
				add(u,v,id);
				add(v,u,id); 
				if(find(u)!=find(v)){
					parent[find(u)]=find(v);
				}
				u=v;
			}
			int x=strint[s];
			vestr[id].push_back(x);
			veint[x].push_back(id);
			i++;
		}
	}
	//cout<<n;//总计11976个站次 
	string start,end;
	int u,v;
	while(1){
		cout<<"请输入起点:";
		cin>>start;	
		if(strint.find(start)==strint.end()){
			cout<<"起点输入错误，请重新输入"<<endl;
		}
		else{
			u=strint[start];
			break;
		}
	}
	while(1){
		cout<<"请输入终点:";
		cin>>end;
		if(strint.find(end)==strint.end()){
			cout<<"终点输入错误，请重新输入"<<endl;
		}
		else{
			v=strint[end];
			break;
		}
	}
	if(u==v){
		cout<<"起点不可与终点相同"<<endl;
		exit(0);
	}
	if(find(u)!=find(v)){
		cout<<"无法从起点走到终点"<<endl;
		exit(0);
	}
	ans=0x3f3f3f3f;
	bool b=0;
	memset(boo,0,sizeof(boo));
	memset(boid,0,sizeof(boid));
	vector <pair<int,int > > t;
	dfs(u,v,0,t);
	if(ans>1000){
		cout<<"无法从起点走到终点"<<endl;
		exit(0);
	}
	while(1){
		cout<<"1.转车次数最少的乘车路线"<<endl;
		cout<<"2.经过站点最少的乘车路线"<<endl;
		cout<<"请选择需要的乘车路线"<<endl;
		string s;
		cin>>s;
		if(s[0]=='1'){
			/*
			ans=0x3f3f3f3f;
			bool b=0;
			memset(boo,0,sizeof(boo));
			memset(boid,0,sizeof(boid));
			vector <pair<int,int > > t;
			dfs(u,v,0,t);
			*/
			int len=ansvect.size();
			int pre=0;
			int flag=0;
			for(int i=0;i<len;i+=2){
				int u1=ansvect[i].first;
				int v1=ansvect[i].second;
				int u2=ansvect[i+1].first;
				int v2=ansvect[i+1].second;
				if(u1==pre) continue;
				pre=u1;
				flag++;
				cout<<u1<<"路  ";
				cout<<intstr[vestr[u1][v1]];
				if(v1<v2){
					v1++;
					while(v1<=v2){
						cout<<"->"<<intstr[vestr[u1][v1]];
						v1++;
					}
					
				}
				else{
					v1--;
					while(v1>=v2){
						cout<<"->"<<intstr[vestr[u1][v1]];
						v1--;
					}
				}
				cout<<endl;
				//cout<<ansvect[i].first<<" "<<ansvect[i].second<<endl;
			}
			cout<<"最少需转"<<flag<<"次车"<<endl;
			break;
		}
		else if(s[0]=='2'){
			dijkstra(u,v);
			cout<<"最少需经过"<<d[v]<<"个站点"<<endl;
			cout<<"经过的站点为:"<<endl;
			stack <string> st;
			while(v){
				st.push(intstr[v]);
				v=path[v];
			}
			while(!st.empty()){
				cout<<st.top()<<" ";
				st.pop();
			}
			cout<<endl;
			break;
		}
		else{
			cout<<"输入错误，请重新输入"<<endl;
		}
	}
	
	
	
	
	
	return 0;
}
