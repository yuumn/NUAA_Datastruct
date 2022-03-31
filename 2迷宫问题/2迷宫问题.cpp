#include <bits/stdc++.h>
#define MAXN 1024
using namespace std;
int a[MAXN][MAXN];
int b[MAXN][MAXN];
stack <pair<int,int> > q; 
int main(){
	fstream fp;
	fp.open("�Թ�·.txt",ios::in);
	string str;
	getline(fp,str);
	int len=str.length();
	int n=0,m=0,k;
	for(k=0;k<len;k++){
		if(str[k]==' ') break;
		n=(n<<1)+(n<<3)+str[k]-'0';
	}
	for(int i=k+1;i<len;i++){
		if(str[i]==' ') break;
		m=(m<<1)+(m<<3)+str[i]-'0';
	}
	//cout<<n<<" "<<m<<endl;
	int n1=1;
	while(!fp.eof()){
		getline(fp,str);
		len=str.length();
		int m1=1;
		for(int i=0;i<len;i++){
			if(str[i]=='0'||str[i]=='1'){
				a[n1][m1]=str[i]-'0';
				//0 ����
				//1 ������
				//-1 �߹��� 
				m1++;
			}
		}
		n1++;
	}
	fp.close();
	cout<<"������Ϊ�������ڵ�������:"<<endl;
	for(int i=1;i<=m;i++){
		if(!a[1][i]) cout<<"(1,"<<i<<") ";
	}
	cout<<endl;
	for(int i=1;i<=m;i++){
		if(!a[n][i]) cout<<"("<<n<<","<<i<<") ";
	}
	cout<<endl;
	for(int i=1;i<=n;i++){
		if(!a[i][1]) cout<<"("<<i<<",1) ";
	}
	cout<<endl;
	for(int i=1;i<=n;i++){
		if(!a[i][m]) cout<<"("<<i<<","<<m<<") ";
	}
	cout<<endl;
	for(int i=0;i<=n+1;i++){
		a[i][0]=1;
		a[i][m+1]=1;
	}
	for(int i=0;i<=m+1;i++){
		a[0][i]=1;
		a[n+1][i]=1;
	}
	int n2,m2,m1;
	while(1){
		cout<<"���������:";
		cin>>n1>>m1;
		cout<<endl;
		if(n1>n||m1>m){
			cout<<"���������ѳ��磬����������"<<endl;
			continue;
		}
		if(a[n1][m1]){
			cout<<"��ڲ�����,����������"<<endl;
			continue; 
		}
		break;
	}
	while(1){
		cout<<"���������:";
		cin>>n2>>m2;
		cout<<endl;
		if(n2>n||m2>m){
			cout<<"����ĳ����ѳ��磬����������"<<endl;
			continue;
		}
		if(a[n2][m2]){
			cout<<"���ڲ�����,����������"<<endl;
			continue;
		}
		break;
	}
	q.push(make_pair(n1,m1));
	a[n1][m1]=-1;
	while(!q.empty()){
		//cout<<"****"<<endl;
		int x=q.top().first;
		int y=q.top().second;
		if(x==n2&&y==m2){
			break;
		}
		if(b[x][y]==4){
			a[x][y]=0;
			q.pop();
			continue;
		}
		if(b[x][y]==0){
			if(a[x-1][y]==1||a[x-1][y]==-1){
				b[x][y]++;
				continue;
			}
			q.push(make_pair(x-1,y));
			a[x-1][y]=-1;
			b[x][y]++;
			continue;
		}
		if(b[x][y]==1){
			if(a[x][y-1]==1||a[x][y-1]==-1){
				b[x][y]++;
				continue;
			}
			q.push(make_pair(x,y-1));
			a[x][y-1]=-1;
			b[x][y]++;
			continue;
		}
		if(b[x][y]==2){
			if(a[x+1][y]==1||a[x+1][y]==-1){
				b[x][y]++;
				continue;
			}
			q.push(make_pair(x+1,y));
			a[x+1][y]=-1;
			b[x][y]++;
			continue;
		}
		if(b[x][y]==3){
			if(a[x][y+1]==1||a[x][y+1]==-1){
				b[x][y]++;
				continue;
			}
			q.push(make_pair(x,y+1));
			a[x][y+1]=-1;
			b[x][y]++;
			continue;
		}
	}
	if(q.empty()){
		cout<<"����·"<<endl;
		exit(0);
	}
	while(!q.empty()){
		int x=q.top().first;
		int y=q.top().second;
		a[x][y]=2;
		q.pop();
	}
	cout<<"�ո�����ߵ�·��"<<endl; 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==1){
				cout<<"��"; 
			} 
			else if(a[i][j]==0){
				cout<<"��"; 
			}
			else{
				cout<<"  ";
			}
//			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}

