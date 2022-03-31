#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
struct node{
	char ch;
	int num;
	struct node *lson,*rson;
	node(char x,int y){
		ch=x;
		num=y;
		lson=NULL;
		rson=NULL;
	}
	
};
struct cmp{
	bool operator()(node*a,node*b){
		return a->num>b->num;
	}
};
void HuffmanErgodic(node *T,unordered_map <char,string> &s,string str){
	if(T==NULL){
		return;
	}
	if(T->ch!=26){
		s[T->ch]=str;
	}
	HuffmanErgodic(T->lson,s,str+"0");
	HuffmanErgodic(T->rson,s,str+"1");
}
void HuffmanEncode(string filename){
	fstream fp;
	fp.open(filename.c_str(),ios::in);
	if(!fp){
		cout<<"error"<<endl;
		exit(0);
	}
	ostringstream st;
	st<<fp.rdbuf();
	string s=st.str();
	unordered_map <char,int> charint;

	int len=s.length();
	for(int i=0;i<len;i++){
		charint[s[i]]++;
	}
	priority_queue <node*,vector<node*>,cmp> q;
	for(auto it:charint){
		node *x=new node(it.first,it.second);
		q.push(x);
	}
	while(q.size()!=1){
		node *x=q.top();
		q.pop();
		node *y=q.top();
		q.pop();
		node *z=new node(26,x->num+y->num);
		z->lson=x;
		z->rson=y;
		q.push(z);
	}
	node *head=q.top();
	unordered_map <char,string> charstr;
	string ss;
	HuffmanErgodic(head,charstr,ss);
	string result;
	for(int i=0;i<len;i++){
		result+=charstr[s[i]];
	}
	len=result.size();
	int char_size=sizeof(char)*8;
	while(result.length()%char_size){
		result+="0";
	} 
	fstream fst;
	filename=filename.substr(0,filename.length()-4);
	fst.open((filename+"解码表.txt").c_str(),ios::out);
	fst<<len<<endl;
	for(auto it:charstr){
		fst<<it.first<<" "<<it.second<<endl;
	}
	fst.close();
	
	char ch=0;
	len=result.length();
	//cout<<result;
	string answer;
	for(int i=0;i<len;i+=char_size){
		ch=0;
		for(int j=0;j<char_size;++j){
			ch=ch*2+result[i+j]-'0';
		}
		answer+=ch;
	}
	len=answer.length();
	FILE *file=fopen((filename+".dat").c_str(),"wb");
	system("pause");
	for(int i=0;i<len;i++){
		//cout<<answer[i];
		fputc(answer[i],file);
	}
	fclose(file);
	fp.close();
	
}
void HuffmanDecode(string filename){
	filename=filename.substr(0,filename.length()-4);
	fstream fst;
	fst.open((filename+"解码表.txt"),ios::in);
	if(!fst){
		cout<<"找不到解码表"<<endl;
		exit(0);
		return;
	}
	int len,num;
	fst>>num;
	
	string str;
	unordered_map <string,char> strchar;

	char ch,_;
	string s;
	while (fst >> noskipws >> _ >> ch >> _ >> s) {
    	if (ch == 7)
      		strchar[s] = '\n';
    	else
      		strchar[s] = ch;
      	
  	}
	fst.close();
	
	FILE *fp=fopen((filename+".dat").c_str(),"rb");
	string answer;
	for(int i=0;i<num/8+1;i++){
		answer+=fgetc(fp);
	}
	fclose(fp);
	len=answer.length();
	
	string encode;
	for(int i=0;i<len;i++){

		bitset<sizeof(char)*8> b(answer[i]);
		string st=b.to_string();
		encode+=st;
	}
	
	encode=encode.substr(0,num);
	
	len=encode.length();
	int j=0;
	string song;
	for(int i=0;i<len;i++){
		string sub=encode.substr(j,i-j+1);
		if(strchar.find(sub)==strchar.end()){
			continue;
		}
		else{
			song+=strchar[sub];
			j=i+1;
		}
	}
	fstream f;
	f.open((filename+"解码后.txt").c_str(),ios::out);
	
	f<<song;
	f.close();
	
}

int main(int argc, char const *argv[]){
	if(argc!=2){
		cout<<"error"<<endl;
		exit(0);
		return 0; 
	} 
	string filename = argv[1];
	string filenameExtension=filename.substr(filename.length()-3,3);
	if(filenameExtension=="dat"){
		HuffmanDecode(filename);
		
	}
	else if(filenameExtension=="txt"){
		HuffmanEncode(filename);
		
	}
	else{
		cout<<"error 文件错误"<<endl;
		exit(0);
		return 0;
	}
		
	
	
} 
