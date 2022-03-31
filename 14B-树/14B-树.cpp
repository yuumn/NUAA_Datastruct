#include <bits/stdc++.h>
using namespace std;
int m;
typedef struct node{
	vector <int> data;
	vector <node *> children;
	struct node *parent;
}CSBTree,*BTree;
void ins(BTree &T,int x){
	if(T==NULL){
		T=new node;
		T->data.push_back(x);
		T->parent=NULL;
		return;
	}

	BTree p=T;
	int i;
	while(!p->children.empty()){
		for(i=0;i<p->data.size();i++){
			if(p->data[i]==x){
				return;
			}
			if(p->data[i]>x){
				break;
			}
		}
		p=p->children[i];
	}
	if(x<p->data[0]){
		p->data.insert(p->data.begin(),x);
	}
	else if(x>p->data.back()){
		p->data.push_back(x);
	}
	else{
		for(int i=0;i<p->data.size();i++){
			if(p->data[i]==x){
				return;
			}
			if(p->data[i]<x&&x<p->data[i+1]){
				p->data.insert(p->data.begin()+i+1,x);
				break;
			}
		}
	}

	while(p->data.size()>=m){
		
		if(p->parent==NULL){
			int mid;
			if(p->data.size()%2==1){
				mid=p->data.size()/2;
			}
			else{
				mid=(p->data.size())/2-1;
			} 
			BTree q1 = new node;
			BTree q2 = new node;
			BTree q = new node;
			for(i=0;i<mid;i++){
				q1->data.push_back(p->data[i]);
			}
			if(!p->children.empty()){
				
				for(i=0;i<=mid;i++){
					q1->children.push_back(p->children[i]);
					p->children[i]->parent=q1;
				}
			}
			q1->parent=q;
			q->data.push_back(p->data[mid]);
			q->children.push_back(q1);
			q->children.push_back(q2);
			q->parent=NULL; 
			for(i=mid+1;i<p->data.size();i++){
				q2->data.push_back(p->data[i]);
			}
			for(i=mid+1;i<p->children.size();i++){
				q2->children.push_back(p->children[i]);
				p->children[i]->parent=q2;
			}
			q2->parent=q;
			T=q;
	
			break;
		}
		
		int mid;
		if(p->data.size()%2==1){
			mid=p->data.size()/2;
		} 
		else{
			mid=(p->data.size())/2-1;
		} 
		BTree q1 = new node;
		BTree q2 = new node;
		for(i=0;i<mid;i++){
			q1->data.push_back(p->data[i]);
		}
		if(!p->children.empty()){
			for(i=0;i<=mid;i++){
				q1->children.push_back(p->children[i]);
				p->children[i]->parent=q1;
			}
		}
		q1->parent=p->parent;
		for(i=mid+1;i<p->data.size();i++){
			q2->data.push_back(p->data[i]);
		}
		if(!p->children.empty()){
			
			for(i=mid+1;i<p->children.size();i++){
				q2->children.push_back(p->children[i]);
				p->children[i]->parent=q2;
			}
		}
		q2->parent=p->parent;
		BTree q=new node;
		q=p->parent;
		if(p->data[mid]<q->data[0]){
			q->data.insert(q->data.begin(),p->data[mid]);
		}
		else if(p->data[mid]>q->data.back()){
			q->data.push_back(p->data[mid]);
		}
		else{
			for(i=0;i<q->data.size();i++){
				if(q->data[i]==p->data[mid]){
					break;
				}
				if(q->data[i]<p->data[mid]&&p->data[mid]<q->data[i+1]){
					q->data.insert(q->data.begin()+i+1,p->data[mid]);
					break;
				}
			}
		}
		for(i=0;i<q->children.size();i++){
			if(q->children[i]==p){
				q->children.erase(q->children.begin()+i);
				q->children.insert(q->children.begin()+i,q1);
				q->children.insert(q->children.begin()+i+1,q2);
				break;
			}
		}
		
		p=p->parent;
		
	}
	
}

void del(BTree &T,int x){
	
	bool flag=0;
	if(T->children.size()==0){
		if(!T->data.empty()){
			for(int i=0;i<T->data.size();i++){
				if(T->data[i]==x){
					flag=1;
					T->data.erase(T->data.begin()+i);
					break;
				}
			}
		}
		if(flag==1){
			cout<<"删除成功"<<endl;
		}
		else{
			cout<<"未找到"<<endl;
		}
		return;
	}
	BTree p=T; 
	int t,i;
	while(!flag&&!p->children.empty()){
		for(i=0;i<p->data.size();i++){
			if(p->data[i]==x){
				flag=1;
				break;
			}
			if(p->data[i]>x){
				break;
			}
		}
		if(!flag){
			p=p->children[i];
		}
	}
	if(flag){

		BTree q=p->children[i+1];
		while(!q->children.empty()){
			q=q->children[0];
		}
		t=q->data[0];
		q->data[0]=p->data[i];
		p->data[i]=t;
		p=q;
		i=0;
	}
	else{
		for(i=0;i<p->data.size();i++){
			if(p->data[i]==x){
				
				break;
				
			}
		}
		if(i==p->data.size()){
			cout<<"未找到"<<endl;
			return;
		}
	}
	p->data.erase(p->data.begin()+i);
	if(p->data.size()>=(m+1)/2-1){
		return;
	}
	int pos;
	for(i=0;i<p->parent->children.size();i++){
		if(p->parent->children[i]==p){
			pos=i;
		}
	}
	if(pos!=0&&p->parent->children[pos-1]->data.size()>(m+1)/2-1){
		t=p->parent->children[pos-1]->data.back();
		p->parent->children[pos-1]->data.pop_back();
		int t1=p->parent->data[pos-1];
		p->parent->data[pos-1]=t;
		p->data.insert(p->data.begin(),t1);
		
	}
	if(pos!=p->parent->children.size()-1&&p->parent->children[pos+1]->data.size()>(m+1)/2-1){
		t=p->parent->children[pos+1]->data[0];
		p->parent->children[pos+1]->data.erase(p->parent->children[pos+1]->data.begin());
		int t1=p->parent->data[pos];
		p->parent->data[pos]=t;
		p->data.push_back(t1);
		
	}
	while(p->data.size()<(m+1)/2-1){
		if(p->parent==NULL){
			T=p->children[0];
			T->parent=NULL;

			p=T;
			return;
		}
		for(i=0;i<p->parent->children.size();i++){
			if(p->parent->children[i]==p){
				pos=i;
			}
		}
		
		if(pos==0){
			
			p->data.push_back(p->parent->data[pos]);
			p->parent->data.erase(p->parent->data.begin()+pos);
			
			for(int i=0;i<p->parent->children[pos+1]->data.size();i++){
				p->data.push_back(p->parent->children[pos+1]->data[i]);
			}
			if(p->parent->children[pos+1]->children.size()!=0){
				
				for(int i=0;i<p->parent->children[pos+1]->children.size();i++){
					p->children.push_back(p->parent->children[pos+1]->children[i]);
					p->parent->children[pos+1]->children[i]->parent=p;
				}
			}
			delete p->parent->children[pos+1];
			p->parent->children.erase(p->parent->children.begin()+pos+1);
			
		}
		else{
			
			p->data.insert(p->data.begin(),p->parent->data[pos-1]);
			p->parent->data.erase(p->parent->data.begin()+pos-1);
			
			for(int i=p->parent->children[pos-1]->data.size()-1;i>=0;i--){
				//cout<<p->parent->children[pos-1]->data[i]<<"** ";
				p->data.insert(p->data.begin(),p->parent->children[pos-1]->data[i]);
			}
			if(p->parent->children[pos-1]->children.size()!=0){
				
				for(int i=p->parent->children[pos-1]->children.size()-1;i>=0;i--){
					p->children.insert(p->children.begin(),p->parent->children[pos-1]->children[i]);
					p->parent->children[pos-1]->children[i]->parent=p;
				}
				
			}
			delete p->parent->children[pos-1];
			p->parent->children.erase(p->parent->children.begin()+pos-1);
			
		}
		
		if(p->data.size()>m-1){
			int mid;
			if(p->data.size()%2==1){
				mid=p->data.size()/2;
			} 
			else{
				mid=(p->data.size())/2-1;
			} 
			BTree q1 = new node;
			BTree q2 = new node;
			for(i=0;i<mid;i++){
				q1->data.push_back(p->data[i]);
			}
			if(!p->children.empty()){
				for(i=0;i<=mid;i++){
					q1->children.push_back(p->children[i]);
					p->children[i]->parent=q1;
				}
			}
			q1->parent=p->parent;
			for(i=mid+1;i<p->data.size();i++){
				q2->data.push_back(p->data[i]);
			}
			if(!p->children.empty()){
				
				for(i=mid+1;i<p->children.size();i++){
					q2->children.push_back(p->children[i]);
					p->children[i]->parent=q2;
				}
			}
			q2->parent=p->parent;
			BTree q=new node;
			q=p->parent;
			if(p->data[mid]<q->data[0]){
				q->data.insert(q->data.begin(),p->data[mid]);
			}
			else if(p->data[mid]>q->data.back()){
				q->data.push_back(p->data[mid]);
			}
			else{
				for(i=0;i<q->data.size();i++){
					if(q->data[i]==p->data[mid]){
						break;
					}
					if(q->data[i]<p->data[mid]&&p->data[mid]<q->data[i+1]){
						q->data.insert(q->data.begin()+i+1,p->data[mid]);
						break;
					}
				}
			}
			for(i=0;i<q->children.size();i++){
				if(q->children[i]==p){
					q->children.erase(q->children.begin()+i);
					q->children.insert(q->children.begin()+i,q1);
					q->children.insert(q->children.begin()+i+1,q2);
					break;
				}
			}
		}
		
		p=p->parent;
		
		
	}
	
	
}

bool SearchBTree(BTree &T,int x){
	BTree p=T;
	if(T->data.empty()){
		return 0; 
	}
	int i;
	while(p){
		for(i=0;i<p->data.size();i++){
			if(p->data[i]==x){
				return 1;
			}
			if(p->data[i]>x){
				break;
			}
		}
		
		if(p->children.empty()){
			return 0;
		}
		else{
			p=p->children[i];	
		}
		
	}
	return 0;
	
}

void DelBTree(BTree &T){
	queue <BTree> q;
	q.push(T);
	while(!q.empty()){
		BTree p=q.front();
		q.pop();
		if(!p->children.empty()){
			for(int i=0;i<p->children.size();i++){
				q.push(p->children[i]);
			}
		}
		p->data.clear();
		p->children.clear();
		p->parent=NULL;
		if(p!=T) delete p; 
	}
	
}

void ShowBTree(BTree &T){
	cout<<"[";
	for(int i=0;i<T->data.size();i++){
		cout<<T->data[i];
		if(i==T->data.size()-1) continue;
		cout<<" ";
	}
	cout<<"]";
	if(!T->children.empty()){
		cout<<"(";
		for(int i=0;i<T->children.size();i++){
			ShowBTree(T->children[i]);
			if(i==T->children.size()-1) continue;
			cout<<",";
		}
		cout<<")";
	}

}

void ShowMenu(){                 //菜单 
    cout<<"1.创建B-树"<<endl;
    cout<<"2.显示B-树"<<endl;
    cout<<"3.插入数据"<<endl;
    cout<<"4.删除数据"<<endl;
    cout<<"5.查找数据"<<endl;
    cout<<"6.删除B-树"<<endl;
    cout<<"7.退出系统"<<endl;
    cout<<"  请输入选择的类型(1-7):";
    
}
void creat(BTree &T){
	fstream fp;
	fp.open("B-树.txt",ios::in);
	if(!fp){
		cout<<"文件打开失败!"<<endl;
		exit(0); 
	}
	int x;
	while(!fp.eof()){
		fp>>x;
		ins(T,x);         //调用插入算法 
	}

	fp.close();
}
int main(){
	BTree T= new node;
	T=NULL;
	while(1){
		ShowMenu();
		string s;
		cin>>s;
		if(s[0]=='1'){
			//创建
			//T= new node;
			cout<<"请输入你需要创建的B-树的阶数:";
			cin>>m;
			creat(T);
		}
		else if(s[0]=='2'){
			//显示
			ShowBTree(T);
			cout<<endl;
		}
		else if(s[0]=='3'){
			//插入
			string s;
			cout<<"请输入要插入的数值："; 
			cin>>s;
			int x=0;
			for(int i=0;i<s.length();i++){
				x=(x<<1)+(x<<3)+s[i]-'0';
			}
			ins(T,x);
			
		} 
		else if(s[0]=='4'){
			//删除 
			string s;
			cout<<"请输入要删除的数值："; 
			cin>>s;
			int x=0;
			for(int i=0;i<s.length();i++){
				x=(x<<1)+(x<<3)+s[i]-'0';
			}
			del(T,x);
			
		} 
		else if(s[0]=='5'){
			//查找
			string s;
			cout<<"请输入要查找的数值："; 
			cin>>s;
			int x=0;
			for(int i=0;i<s.length();i++){
				x=(x<<1)+(x<<3)+s[i]-'0';
			}
			if(SearchBTree(T,x)){
				cout<<"B-树中存在"<<x<<endl; 
			}
			else{
				cout<<"B-树中不存在"<<x<<endl; 
			}
		}
		else if(s[0]=='6'){
			//毁树
			DelBTree(T);
		} 
		else if(s[0]=='7'){
			//退出
			DelBTree(T);
			exit(0);
		} 
		else{
			cout<<"输入错误，请重新输入"<<endl;
			continue;
		}
		
	} 
	

	return 0;
}
