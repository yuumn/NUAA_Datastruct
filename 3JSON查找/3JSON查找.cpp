#include <bits/stdc++.h>
using namespace std;
int n,m;
typedef struct node{
	string key;
	string value;
	struct node *firstchild,*nextbro;
}CSNode, *CSTree;
string Getkey(string str){
	string key;
	for(int i=1;i<str.length();i++){
		if(str[i]=='\\'&&(str[i+1]=='\\'||str[i+1]=='"')){
			key+=str[i+1];//   \"  \\ 
			i++;

		}
		else if(str[i]!='\\'&&str[i]!='"'){
			key+=str[i];

		}
		else if(str[i]=='"'){
			break;
		}
	}
	//cout<<"---"<<key<<endl;
	return key;
}
string Getvalue(string str){
	string value;
	int i=0;
	while(str[i]!=':') i++;
	i+=2;
	for(;i<str.length();i++){
		if(str[i]=='\\'&&(str[i+1]=='\\'||str[i+1]=='"')){
			value+=str[i+1];
			i++;

		}
		else if(str[i]!='\\'&&str[i]!='"'){
			value+=str[i];

		}
		else if(str[i]=='"'){
			break;
		}
	}
	return value;
}
int num;
int num1;
void PreOrderTraverse(CSTree T){
	//cout<<"***"<<++num1<<endl;
	if(T){
		//cout<<"123456"<<endl;
		string s=T->value;
		//cout<<s<<endl;
		if(T->value.length()!=0){
		//	cout<<"456"<<endl;
			//cout<<"//"<<++num1<<endl;
			cout<<T->key<<" "<<T->value<<endl;
		}
		else{
			//cout<<"0123"<<endl;
			cout<<T->key<<endl;
			//cout<<"++"<<++num1<<endl;
		}
		PreOrderTraverse(T->firstchild);
		PreOrderTraverse(T->nextbro);
	}
}
void CreateNodeTree(CSTree &T,fstream &datafile){
	//cout<<num++<<endl;
	//PreOrderTraverse(T);
	string str;
	getline(datafile,str);
	//cout<<str<<endl;
	int len=str.length();
	if(str[0]=='}'){
		//cout<<++num<<endl;
		//cout<<"***"<<endl;
		T=NULL;
	}
	else{
		T=new node;
		//T = (node*)malloc(sizeof(node));
		//cout<<++num<<" ";
		if(str[len-1]=='{'){//如果行末为'{'（值）是对象
			string key=Getkey(str);
			T->key=key;
			//cout<<"**"<<key<<endl;
			CreateNodeTree(T->firstchild,datafile);
			CreateNodeTree(T->nextbro,datafile);
		}
		else{
			string value,key;
			key=Getkey(str);
			value=Getvalue(str);
			T->key=key;
			T->value=value;
			//cout<<"--"<<T->key<<" "<<T->value<<endl;
			T->firstchild=NULL;
			CreateNodeTree(T->nextbro,datafile);
		}
	}
}
int Get_point(string str,int i,string &ss){
	
	int len=str.length();
	int j=0;
	while(i+j<len){
		if(str[i+j]=='.'){
			break;
		}
		else{
			ss+=str[i+j];
		}
		j++;
	}
	//ss+='\0';
	return i+j+1;
}
void SearchValue(string str,CSTree T){
	int i=0;
	int len=str.length();
	while(i<len){
		string s;
		i=Get_point(str,i,s);
		//int l=s.length();
		//cout<<"*"<<s<<"*"<<endl;
		while(T){
			//cout<<endl<<"T->key *"<<T->key<<"*"<<T->key.length()<<"*"<<s.length()<<endl;
			if(T->key==s){
				break;
			}
			else{
				T=T->nextbro;
			}
		}
		if(T==NULL) break;
		if(i<=len){
			T=T->firstchild;
		}
	}
	if(T==NULL){
		cout<<"NOTEXIST"<<endl;
	}
	else if(T->value.length()==0){
		cout<<"OBJECT"<<endl;
	}
	else{
		cout<<"STRING "<<T->value<<endl;
	}
	
}
int main(){
	fstream fp;
	fp.open("in.txt",ios::in);
	fp>>n>>m;
	string str;
	getline(fp,str);
	int len=str.length();
	int k;
	for(k=0;k<len;k++){
		if(str[k]==' ') break;
		n=(n<<1)+(n<<3)+str[k]-'0';
	}
	for(int i=k+1;i<len;i++){
		if(str[i]==' ') break;
		m=(m<<1)+(m<<3)+str[i]-'0';
	}
	CSTree T;
	getline(fp,str);
	CreateNodeTree(T,fp);
	cout<<"已读取的JSON数据为:"<<endl;
	PreOrderTraverse(T);
	while(!fp.eof()){
		cout<<"查询信息：";
		getline(fp,str);
		cout<<str<<" 查询结果为："; 
		SearchValue(str,T);
	}
	
	
	fp.close();
	return 0;
}
