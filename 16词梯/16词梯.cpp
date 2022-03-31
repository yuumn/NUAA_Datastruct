#include <bits/stdc++.h>
using namespace std;
struct node{
	int to,next;
}a[25][200000];
int top[25];
int head[25][500000];
bool bo[500000];
int dis[500000];
int path[500000];
void add(int u,int v,int len){
	a[len][++top[len]].to=v;
	a[len][top[len]].next=head[len][u];
	head[len][u]=top[len];
}
bool StrCmp(string s1,string s2){
	int len=s1.length();
	int flag=0;
	for(int i=0;i<len;i++){
		if(s1[i]!=s2[i]){
			flag++;
		}
	}
	if(flag==1){
		return 1;
	}
	else{
		return 0;
	}
	
}
void dij(int u,int v,int len){
	memset(bo,0,sizeof(bo));
	memset(dis,0x3f,sizeof(dis));
	memset(path,0,sizeof(path));
	dis[u]=0;
	priority_queue <pair<int,int > > q;
	q.push(make_pair(0,u));
	while(!q.empty()){

		int x=q.top().second;
		q.pop();
		if(bo[x]) continue;
		bo[x]=1;
		for(int i=head[len][x];i;i=a[len][i].next){
			int to=a[len][i].to;
			if(dis[x]+1<dis[to]){
				dis[to]=dis[x]+1;
				path[to]=x;
				q.push(make_pair(-dis[to],to));
			}
		}
		
	}
	
}
map <string,int> strint;
map <int,string> intstr; 
int num;
unordered_set <string> s[50];
int main(){

	clock_t start = clock();
	
	ifstream fin("words.txt", std::ios::binary);     
	vector<char> buf(fin.seekg(0, std::ios::end).tellg());
	fin.seekg(0, std::ios::beg).read(&buf[0], static_cast<std::streamsize>(buf.size()));
	fin.close();
	
	clock_t end = clock();
    cout << "time : " << ((double)end - start) / CLOCKS_PER_SEC << "s\n";
    
    start = clock();
	
	int i=0;
	int lenn=buf.size();
	
	while(i<lenn&&buf[i]!='\x0a'){
		string ss;
		while(i<lenn&&buf[i]!='\x0a'){
			if('A'<=buf[i]&&buf[i]<='Z'){
				ss+=buf[i]-'A'+'a';
			}
			else if('a'<=buf[i]&&buf[i]<='z'){
				ss+=buf[i];
			}
			i++;
		}
		i++;
		strint[ss]=++num;
		intstr[num]=ss;
		int len=ss.length();
		for(int j=0;j<len;j++){
			string s1=ss;
			for(int k=0;k<26;k++){
				s1[j]='a'+k;
				if(s1[j]==ss[j]){
					continue;
				}
				if(s[len].count(s1)){
					add(strint[s1],strint[ss],len);
					add(strint[ss],strint[s1],len);
				}
			}
		}
		s[len].insert(ss);

	}
	
	end = clock();
    cout << "time : " << ((double)end - start) / CLOCKS_PER_SEC << "s\n";

	string s1,s2;
	int len1,len2;
	while(1){
		
		while(1){
			cout<<"请输入第一个单词(输入0退出程序):"<<endl;
			cin>>s1;
			if(s1=="0"){
				exit(0);
			} 
			len1=s1.length();
			//cout<<strint[s1]<<endl;
			if(s[len1].count(s1)==0){
				cout<<"找不到第一个单词,请重新输入"<<endl;
				continue;
			}
			else{
				break;
			}
		 
		}
		while(1){
			cout<<"请输入第二个单词:"<<endl;
			cin>>s2;
			len2=s2.length();
			//cout<<strint[s2]<<endl;
			if(s[len2].find(s2)==s[len2].end()){
				cout<<"找不到第一个单词,请重新输入"<<endl;
				continue;
			}
			else if(len1!=len2){
				cout<<"与第一个单词长度不同，请重新输入"<<endl;
				continue;
			}
			else{
				break;
			}
		}
		dij(strint[s1],strint[s2],len1);
		if(dis[strint[s2]]>100000){
			cout<<"无解"<<endl;
		}
		else{
			cout<<"词梯长度为:"<<dis[strint[s2]]<<endl;
			int p=strint[s2];
			stack <int> st;
			while(p){
				st.push(p);
				p=path[p];
			}
			while(!st.empty()){
				cout<<intstr[st.top()];
				st.pop();
				if(!st.empty()) cout<<"->";
			}
			cout<<endl;
		}
	
	}
	
	
	
	return 0;
}


