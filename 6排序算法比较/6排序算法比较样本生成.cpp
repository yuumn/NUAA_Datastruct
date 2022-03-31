#include <bits/stdc++.h>
#define random(x) (rand()%x+1)
using namespace std;

int main(){
	srand(time(0));
	fstream fp;
	for(int i=1;i<=10;i++){
		string s;
		if(i<10){
			s+=('0'+i);
		}
		else{
			s+="10";
		}
		s+=".txt";
		fp.open(s.c_str(),ios::out);
		int m=50000;
		if(i>2){
			while(m--){
				fp<<random(1000000)<<" ";
			}
		}
		else if(i==1){
			while(m--){
				fp<<50000-m<<" ";
			}
		}
		else if(i==2){
			while(m--){
				fp<<m+1<<" ";
			}
		}
	}
	
	fp.close();
	
	return 0;
} 
