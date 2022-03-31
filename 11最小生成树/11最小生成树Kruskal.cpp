#include <bits/stdc++.h>
using namespace std;
map <string,int> mint;
map <int,string> mstr;
int parent[1005];
int find(int x){
	while(x!=parent[x]){
		parent[x]=parent[parent[x]];
		x=parent[x];
	}
	return x;
}
priority_queue <pair<int,pair<int,int > > > q;
void Kruskal(){
	cout<<"Kruskal算法:"<<endl;
	cout<<"最小生成树的边为："<<endl; 
	int ans=0;
	while(!q.empty()){
		int u=q.top().second.first;
		int v=q.top().second.second;
		int w=-q.top().first;
		q.pop();
		if(find(u)==find(v)) continue;
		parent[find(u)]=find(v);
		ans+=w;
		cout<<"    "<<mstr[u]<<" "<<mstr[v]<<" "<<w<<endl;
	}
	cout<<"最小生成树的权值之和为："<<ans<<endl;
}

int main(){
	fstream fp;
	fp.open("11最小生成树.txt",ios::in);
	string str;
	getline(fp,str);
	int len=str.length();
	int n=0;
	for(int i=0;i<len;i++){
		if('0'<=str[i]&&str[i]<='9'){
			n=(n<<1)+(n<<3)+str[i]-'0';
		}
	}
	for(int i=1;i<=n;i++){
		parent[i]=i;
	}
	getline(fp,str);
	len=str.length();
	int num=0;
	for(int i=0;i<len;i++){
		string s;
		while(i<len&&str[i]!=' '){
			s+=str[i];
			i++;
		}
		mint[s]=++num;
		mstr[num]=s;
		cout<<s<<" "<<num<<endl;
	}
	while(!fp.eof()){
		getline(fp,str);
		len=str.length();
		if(len==0) break;
		int i=0;
		
		string s1,s2;
		while(i<len&&str[i]!=' '){
			s1+=str[i];
			i++;
		}
		i++;
		while(i<len&&str[i]!=' '){
			s2+=str[i];
			i++;
		}
		i++;
		int data=0;
		while(i<len&&str[i]!=' '){
			if('0'<=str[i]&&str[i]<='9'){
				data=(data<<1)+(data<<3)+str[i]-'0';
			}
			i++;
		}
		cout<<s1<<" "<<s2<<endl;
		cout<<mint[s1]<<" "<<mint[s2]<<" "<<data<<endl;
		//add(mint[s1],mint[s2],data);
	//	add(mint[s2],mint[s1],data);
		q.push(make_pair(-data,make_pair(mint[s1],mint[s2])));
	}
	Kruskal();
	
	fp.close();
	return 0;
} 
