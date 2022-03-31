#include <bits/stdc++.h>
using namespace std;
const int mod=113;
int num;
int cnt;
struct node{
	int id;
	string infor;
	int checkcode;
	node *next;
};
node* buildnode(string s,int code,node *head){//���ļ��ж�ȡ������ 
	node *p=new node;
	node *q=head;
	p->id=num;
	//cout<<num<<endl;
	num++;
	p->infor=s;
	p->checkcode=code;
	p->next=NULL;
	while(q->next){
		q=q->next;
	}
	q->next=p;
	//cout<<q->id<<endl;
	return head;
}
int checknode(node *head){//��� 
	node *q=head->next;
	string s=q->infor;
	int len=s.length();
	int check=0;
	for(int i=0;i<len;i++){
		check+=s[i];
	}
	check+=q->id;
	check%=mod;
	//cout<<check<<" "<<q->id<<" "<<q->checkcode<<endl;
	if(check!=q->checkcode){
		return q->id;
	}
	int pre=q->checkcode;
	while(q->next){
		q=q->next;
		s=q->infor;
		len=s.length();
		check=0;
		for(int i=0;i<len;i++){
			check+=s[i];
		}
		check+=q->id;
		//cout<<q->id<<endl;
		check+=pre;
		check%=mod;
		if(check!=q->checkcode){
			return q->id;
			//cout<< q->id<<" "<<check<<" "<<q->checkcode<<" "<<q->infor[0]<<" "<<q->infor[len-1]<<endl;
		}
		pre=q->checkcode;
	}
	return -1;
}
node *insertnode(node *head,string s){//���� 
	node *q=head->next;
	int pre=q->checkcode;
	while(q->next){
		pre=q->checkcode;
		q=q->next;
	}
	node *p=new node;
	p->id=num;
	num++;
	p->infor=s;
	p->next=NULL;
	int len=s.length();
	int check=0;
	check+=pre;
	check+=p->id;
	for(int i=0;i<len;i++){
		check+=s[i];
	}
	check%=mod;
	p->checkcode=check;
	q->next=p;
	return head;
}
node *distortnode(node *head,int id,string s){//�۸� 
	node *q=head,*p=head;
	int x=q->id,pre=0;
	while(x!=id){
		pre=q->checkcode;
		q=q->next;
		x=q->id;
	}
	q->infor=s;
	int check=0;
	int len;
	while(q){
		check=0;
		len=q->infor.length();
		for(int i=0;i<len;i++){
			check+=q->infor[i];
		}
		check+=pre;
		check+=q->id;
		check%=mod;
		q->checkcode=check;
		pre+=q->checkcode;
		q=q->next;
	}
	return head;
}
void shownode(node *head){//��ʾ 
	node *q=head->next;
	while(q){
		cout<<"�ڵ���:"<<q->id<<" �ڵ���Ϣ:"<<q->infor<<" �ڵ�У����:"<<q->checkcode<<endl;
		q=q->next;
	}
}
int main(){
	fstream fp,f;
	fp.open("demo_right1.txt",ios::in);
	//�ı��ļ��벻����ASCII��Ϊ0��9��10��13��26���ַ� 
	//f.open("out.txt",ios::out);
	if(!fp){
		cout<<"open error"<<endl;
		exit(0);
	}
	string str;
	node *head=new node;
	//head=NULL;
	head->next=NULL;
	while(!fp.eof()){
		cnt++;
		getline(fp,str);
		int len=str.length();
		if(len==0) break;
		int k=0;
		int data=0;
		while(str[k]!=' '){
			//cout<<str[k]<<endl;
			data=(data<<1)+(data<<3)+str[k]-'0';
			k++;
		}
		//cout<<data<<" "<<len<<endl;
		string s;
		for(int i=k+1;i<len;i++){
			s+=str[i];
		}
		//cout<<s<<endl;
		head=buildnode(s,data,head);
	}
	cnt--;
	cout<<"����Ѹ����Ƿ���Ч"<<endl;
	//cout<<cnt<<endl;
	int x=checknode(head);
	if(x!=-1){
		cout<<"�׸���Ч�ڵ�Ľڵ���Ϊ"<<x<<endl;
	}
	else{
		cout<<"������Ч"<<endl;
	}
	while(1){
		cout<<"1.�������������Ϣ"<<endl;
		cout<<"2.�۸�һ���ڵ����Ϣ"<<endl;
		cout<<"3.��ʾ��������"<<endl;
		cout<<"4.�˳�"<<endl;
		cout<<"��������еĲ�����ţ�";
		cin>>x;
		string s;
		if(x==1){
			cout<<"������ڵ���Ϣ:";
			cin>>s;
			head=insertnode(head,s);
		}
		else if(x==2){
			while(1){
				cout<<"������Ҫ�۸ĵĽڵ���[0,"<<num-1<<"]:";
				int y;
				cin>>y;
				if(0<=y&&y<num){
					cout<<"������۸ĵĽڵ���Ϣ:"; 
					cin>>s;
					head=distortnode(head,y,s);
					cout<<"�۸ĳɹ�����������Ч"<<endl;
					break;
				}
				else{
					cout<<"�ڵ��Ŵ�������������"<<endl;
				}
			}
		}
		else if(x==3){
			shownode(head);
		}
		else if(x==4){
			break;
		}
		else{
			cout<<"����ı�Ŵ�������������"<<endl;
		}
	}
	 
	fp.close();
	//f.close();
	
	return 0;
} 
