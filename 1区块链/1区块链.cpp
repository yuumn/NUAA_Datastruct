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
node* buildnode(string s,int code,node *head){//从文件中读取并建立 
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
int checknode(node *head){//检查 
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
node *insertnode(node *head,string s){//插入 
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
node *distortnode(node *head,int id,string s){//篡改 
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
void shownode(node *head){//显示 
	node *q=head->next;
	while(q){
		cout<<"节点编号:"<<q->id<<" 节点信息:"<<q->infor<<" 节点校验码:"<<q->checkcode<<endl;
		q=q->next;
	}
}
int main(){
	fstream fp,f;
	fp.open("demo_right1.txt",ios::in);
	//文本文件须不包含ASCII码为0、9、10、13、26的字符 
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
	cout<<"检查已给定是否有效"<<endl;
	//cout<<cnt<<endl;
	int x=checknode(head);
	if(x!=-1){
		cout<<"首个无效节点的节点编号为"<<x<<endl;
	}
	else{
		cout<<"链表有效"<<endl;
	}
	while(1){
		cout<<"1.向链表中添加信息"<<endl;
		cout<<"2.篡改一个节点的信息"<<endl;
		cout<<"3.显示链表内容"<<endl;
		cout<<"4.退出"<<endl;
		cout<<"请输入进行的操作编号：";
		cin>>x;
		string s;
		if(x==1){
			cout<<"请输入节点信息:";
			cin>>s;
			head=insertnode(head,s);
		}
		else if(x==2){
			while(1){
				cout<<"请输入要篡改的节点编号[0,"<<num-1<<"]:";
				int y;
				cin>>y;
				if(0<=y&&y<num){
					cout<<"请输入篡改的节点信息:"; 
					cin>>s;
					head=distortnode(head,y,s);
					cout<<"篡改成功，且链表有效"<<endl;
					break;
				}
				else{
					cout<<"节点编号错误，请重新输入"<<endl;
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
			cout<<"输入的编号错误，请重新输入"<<endl;
		}
	}
	 
	fp.close();
	//f.close();
	
	return 0;
} 
