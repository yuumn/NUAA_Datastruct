#include <bits/stdc++.h>
using namespace std;
map <string,int> mint;
map <int,string> mstr;
struct node{
	int to,w,next;
}a[200005];
int head[1005];
bool bo[1005];
int top;
void add(int u,int v,int w){
	a[++top].to=v;
	a[top].w=w;
	a[top].next=head[u];
	head[u]=top;
}
priority_queue <pair<int,pair<int,int > > > q;
void Prim(){
	for(int i=head[1];i;i=a[i].next){
		q.push(make_pair(-a[i].w,make_pair(1,a[i].to)));
	}
	//bo[1]=1;
	int ans=0;
	cout<<"Prim�㷨:"<<endl;
	cout<<"��С�������ı�Ϊ��"<<endl; 
	while(!q.empty()){
		int u=q.top().second.first;
		int v=q.top().second.second;
		int w=-q.top().first;
		q.pop();
		if(bo[u]) continue;
		cout<<"    "<<mstr[u]<<" "<<mstr[v]<<" "<<w<<endl;
		bo[u]=1;
		ans+=w;
		for(int i=head[v];i;i=a[i].next){
			if(bo[a[i].to]) continue;
			q.push(make_pair(-a[i].w,make_pair(v,a[i].to)));
		}
	}
	cout<<"��С��������Ȩֵ֮��Ϊ��"<<ans<<endl;
}

int main(){
	fstream fp;
	fp.open("11��С������.txt",ios::in);
	string str;
	getline(fp,str);
	int len=str.length();
	int n=0;
	for(int i=0;i<len;i++){
		if('0'<=str[i]&&str[i]<='9'){
			n=(n<<1)+(n<<3)+str[i]-'0';
		}
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
		add(mint[s1],mint[s2],data);
		add(mint[s2],mint[s1],data);
	}
	Prim();
	
	fp.close();
	return 0;
} 
