#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	string a[100],b[100],s;
	for(int i=0;i<n;i++){
		cin>>a[i]>>b[i];
	}
	while(m--){
		cin>>s;
		bool flag=0;
		int len2=s.length();
		for(int i=0;i<n;i++){
			int len1=a[i].length();
			int x=0,y=0;
			while(x<len1&&y<len2){
				if(s[y]==a[i][x]){
					x++;
					y++;
					continue;
				}
				if(a[i][x]!='<'){
					break;
				}
				x++;
				if(a[i][x]=='i'){

					while(y<len2&&'0'<=s[y]&&s[y]<='9'){

						y++;
					}

					x+=4;
					continue;
				}
				if(a[i][x]=='s'){
					bool flag2=0;
					while(y<len2&&s[y]!='/'){
						flag2=1;
						y++;
					}
					if(!flag2){
						break;
					}
					x+=4;
					continue;
				}
				if(a[i][x]=='p'){
					flag=1;
					break;
				}
			}
			if(x==len1&&y==len2){
				flag=1;
			}
			if(flag){
				x=0,y=0;
				cout<<b[i];
				while(x<len1&&y<len2){
					if(a[i][x]==s[y]){
						x++;
						y++;
						continue;
					}
					x++;
					cout<<" ";
					if(a[i][x]=='i'){
						bool bo=0;
						while(y<len2&&'0'<=s[y]&&s[y]<='9'){
							if(s[y]>'0'){
								bo=1;
							}
							if(bo){
								cout<<s[y];
							}
							y++;
						}
						x+=4;
						continue;
					}
					if(a[i][x]=='s'){
						bool bo=0;
						while(y<len2&&s[y]!='/'){
							bo=1;
							cout<<s[y];
							y++;
						}
						x+=4;
						continue;
					}
					if(a[i][x]=='p'){
						while(y<len2){
							cout<<s[y];
							y++;
						}
					}
				}
			}
			if(flag) break;
		}
		if(!flag){
			cout<<"404";
		}
		cout<<endl;
		
	}
	
	
	return 0;
}
