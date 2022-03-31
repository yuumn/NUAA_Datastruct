#include <bits/stdc++.h>
using namespace std;
#define MAXN 100007
#define random(x) (rand()%x+1)
struct node{
	string id;//���֤�� 
	string name;//���� 
	string date;//���� 
	double rate;//Ƶ�� 
	double dis;//����� 
	struct node *next;
}edge[MAXN];
priority_queue <int> gg;
int prime[18]={90833,76481,77773,79777,84163,86017,87793,87797,91081,98419,98801,98899,98909,99347,99349,99367,99371,100003};
int num;
int conflictnum;
priority_queue <double> qdis;
priority_queue <double> qrate;
queue <int> qu;
bool bo;
int sumn; 
int getChainAddress(string id){
	int x=0;
	int len=id.length();
	for(int i=0;i<len;i++){
		x=((x<<1)+(x<<3)+id[i]-'0')%100007;
	}
	//cout<<x<<endl;
	//gg.push(-x);
	return x;
}
int getPrimeMult(string id){
	int x=0;
	int len=id.length();
	for(int i=0;i<len;i++){
		x+=(((id[i]-'0')*(prime[i]%100007))%100007);
		x%=100007;
	}
	//cout<<x<<endl;
	//gg.push(-x);
	return x;
}
void PrimeMult(string name,string id,string date,double dis,double rate){
	int x=getPrimeMult(id);
	int k=0;
	while(1){
		if(edge[x].id.length()==0){
			edge[x].name=name;
			edge[x].id=id;
			edge[x].date=date;
			edge[x].dis=dis;
			edge[x].rate=rate;
			edge[x].next=NULL;
			break;
		}
		else{
			k++;
			x++;
		}
	}
	if(k){
		conflictnum++;
		qu.push(k);
	}
}
int kkk;
void ChainAddress(string name,string id,string date,double dis,double rate){
	int x=getChainAddress(id);
	if(edge[x].id.length()==0){
		edge[x].name=name;
		edge[x].id=id;
		edge[x].date=date;
		edge[x].dis=dis;
		edge[x].rate=rate;
		edge[x].next=NULL;
		kkk++;
	}
	else{
		int k=1;
		conflictnum++;
		struct node *p=&edge[x];
		while(p->next!=NULL){
			p=p->next;
			k++;
		}
		qu.push(k);
		node *q= new node;
		q->name=name;
		q->id=id;
		q->date=date;
		q->dis=dis;
		q->rate=rate;
		q->next=NULL;
		p->next=q;
		//cout<<q->name<<" "<<p->name<<endl;
		kkk++;
	}
}
int main(){
	fstream fp;
	srand(time(0));
	fp.open("5.txt",ios::in);
	string str;
	string in;
	while(1){
		cout<<"1.������˷�"<<endl;
		cout<<"2.����ַ��"<<endl;
		cout<<"��ѡ������ͻ�ķ���:";
		cin>>in;
		if(in[0]=='1'){
			bo=1;
			break; 
		} 
		else if(in[0]=='2'){
			bo=0;
			break;
		}
		else{
			cout<<"�������������ѡ��"<<endl;
		}
	}
	while(!fp.eof()){
		getline(fp,str);
		if(str.length()==0) break;
		num++;
		int i=0,len=str.length();
		string name,id,date;
		double dis=0,rate=0;
		while(str[i]!=' '&&i<len){
			name+=str[i];
			i++;
		}
		i++;
		while(str[i]!=' '&&i<len){
			id+=str[i];
			i++;
		}
		i++;
		while(str[i]!=' '&&i<len){
			date+=str[i];
			i++;
		}
		i++;
		while(str[i]!=' '&&i<len){
			dis=dis*10+str[i]-'0';
			i++;
		}
		double t=0.1;
		while(str[i]!='.'){
			i++;
		}
		i++;
		while(i<len){
			rate+=(t*(str[i]-'0'));
			t=t/10.0;
			i++;
		}
		qdis.push(dis);
		qrate.push(rate);
		//cout<<name<<" "<<id<<" "<<date<<" "<<dis<<" "<<rate<<endl;
		if(bo){
			PrimeMult(name,id,date,dis,rate);
		}
		else{
			ChainAddress(name,id,date,dis,rate);	
		}
		//cout<<"--"<<endl;
	}
//	int uu=0;
//	while(!gg.empty()){
//		if(-gg.top()==uu){
//			gg.pop();
//			continue;
//		}
//		uu=-gg.top();
//		cout<<-gg.top()<<endl;
//		gg.pop();
//	}
	int leng=num/5;
	double dismin,ratemin;
	while(leng--){
		dismin=qdis.top();
		ratemin=qrate.top();
		qdis.pop();
		qrate.pop();
	}
	if(bo){
		cout<<"������˷�"; 
	}
	else{
		cout<<"����ַ��"; 
	}
	cout<<"��������ͻ"<<conflictnum<<"��"<<endl;
	if(conflictnum){
		cout<<"�ֱ�Ϊ:"<<endl;
		while(!qu.empty()){
			cout<<qu.front()<<"��"<<endl;
			sumn+=qu.front();
			qu.pop();
		}
		cout<<"��"<<sumn<<"��"<<endl; 
	}
	
	cout<<"VIP�ͻ�(�˳�Ƶ�ʻ��������ǰ20%):"<<endl;
	cout<<kkk<<" "<<dismin<<" "<<ratemin<<endl;
	cout.flags (ios::left);//������������
	int kk=0;
	if(bo){
		for(int i=0;i<MAXN;i++){
			if(edge[i].id.length()==0){
				continue;
			}
			kk++;
			if(edge[i].dis>=dismin||edge[i].rate>=ratemin){
				cout<<"����:"<<setw(6)<<edge[i].name<<" ���֤��:"<<edge[i].id<<" �˳�Ƶ��:"<<setw(6)<<edge[i].rate<<" �����:"<<edge[i].dis<<endl;
			}
		}
	}
	else{
		for(int i=0;i<MAXN;i++){
			if(edge[i].id.length()==0){
				continue;
			}
			if(edge[i].dis>=dismin||edge[i].rate>=ratemin){
				cout<<"����:"<<setw(6)<<edge[i].name<<" ���֤��:"<<edge[i].id<<" �˳�Ƶ��:"<<setw(6)<<edge[i].rate<<" �����:"<<edge[i].dis<<endl;
			}
			kk++;
			struct node *p=edge[i].next;
			while(p){
				kk++;
				//cout<<"++++++++++++++++++"<<endl;
				if(p->dis>=dismin||p->rate>=ratemin){
					cout<<"����:"<<setw(6)<<p->name<<" ���֤��:"<<p->id<<" �˳�Ƶ��:"<<setw(6)<<p->rate<<" �����:"<<p->dis<<endl;
				}
				p=p->next;
			}
		}
	}
	//cout<<"****"<<kk<<"****"<<endl;
	
	fp.close();
	
	return 0;
} 	
