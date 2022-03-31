//#pragma comment(linker,"/STACK:1024000000,1024000000") 
//#pragma comment(linker, "/STACK:1048576")
#include <bits/stdc++.h>
using namespace std;
const int n=50000;
int a[50005];
int b[50005];
void Insert_sort(int a[]){//直接插入排序
	int i,j,k;
	for(i=1;i<n;i++){
		for(j=i-1;j>=0;j--){
			if(a[j]<a[i]){
				break;
			}
		}
		if(j!=i-1){
			int t=a[i];
			for(k=i-1;k>j;k--){
				a[k+1]=a[k];
			}
			a[k+1]=t;
		}
	}
}
void Shell_sort(int a[]){//希尔排序
	int d=n/2;
	while(d>0){
		for(int i=d+1;i<n;i++){
			int j;
			for(j=i-d;j>=0;j-=d){
				if(a[j]<a[i]){
					break;
				}
			}
			if(j!=i-d){
				int t=a[i];
				int k;
				for(k=i-d;k>j;k-=d){
					a[k+d]=a[k];
				}
				a[k+d]=t;
			}
		}
		d/=2;
	}
}
void Bubble_sort(int a[]){//冒泡排序
	for(int i=0;i<n;i++){
		for(int j=0;j<n-i;j++){
			if(a[j-1]>a[j]){
				int t=a[j-1];
				a[j-1]=a[j];
				a[j]=t;
			}
		}
	}
}
void Quick_sort(int a[],int l,int r){//快速排序
	if(l>=r) return;
	int t=a[l];
	int i=l,j=r;
	//cout<<"***"<<endl;
	while(i<j){
		while(a[j]>t&&i<j){
			j--;
		}
		while(a[i]<t&&i<j){
			i++;
		}
		if(i<j){
			int tt=a[i];
			a[i]=a[j];
			a[j]=tt;
		}
	}
	a[l]=a[i];
	a[i]=t;
	Quick_sort(a,l,i-1);
	Quick_sort(a,i+1,r);
}
void Select_sort(int a[]){//选择排序
	for(int i=0;i<n;i++){
		int MAIN=0x3f3f3f3f; 
		int u=i;
		for(int j=i+1;j<n;j++){
			if(a[j]<MAIN){
				MAIN=a[j];
				u=j;
			}
		}
		int t=a[i];
		a[i]=a[u];
		a[u]=t;
	}
}
void treeSelectSort(int a[]){//树形选择排序 
	int len=2*n-1;
	int t[len];
	int low=0;
	for(int i=len-1,j=0;j<n;i--,j++){
		t[i]=a[j];
	}
	for(int i=len-1;i>0;i-=2){
		t[(i-1)/2]=(t[i-1]>t[i]?t[i]:t[i-1]);
	}
	while(low<n){
		int MAIN=t[0];
		a[low++]=MAIN;
		int u=len-1;
		while(t[u]!=MAIN){
			u--;
		}
		t[u]=0x3f3f3f3f;
		while(u>0){
			if(u%2==0){
				t[(u-1)/2]=(t[u-1]>t[u]?t[u]:t[u-1]);
				u=(u-1)/2;
			}
			else{
				t[u/2]=(t[u+1]>t[u]?t[u]:t[u+1]);
				u=(u/2);
			}
		}
	}
	
}
void down(int a[],int i,int n){
	int p=i;
	int c=2*i+1;
	while(c<n){
		if(c+1<n&&a[c]<a[c+1]){
			c++;
		}
		if(a[p]<a[c]){
			int t=a[p];
			a[p]=a[c];
			a[c]=t;
			p=c;
		}
		c=2*c+1;
	}
	
}
void Heap_sort(int a[]){//堆排序
	for(int i=n/2-1;i>=0;i--){
		down(a,i,n);
	}
	for(int i=n-1;i>=0;i--){
		int t=a[0];
		a[0]=a[i];
		a[i]=t;
		down(a,0,i);
	}
}
void Merge(int a[],int l,int r){
	int mid=(l+r)/2;
	int b[mid-l+2];
	int c[r-mid+1];
	int b1=0,c1=0,i=l,j=mid+1;
	while(i<=mid){
		b[b1]=a[i];
		b1++;
		i++;
	}
	while(j<=r){
		c[c1]=a[j];
		c1++;
		j++;
	}
	i=0,j=0;
	int k=l;
	while(i<b1&&j<c1){
		if(b[i]<c[j]){
			a[k]=b[i];
			i++;
			k++;
		}
		else{
			a[k]=c[j];
			k++;
			j++;
		}
	}
	while(i<b1){
		a[k]=b[i];
		k++;
		i++;
	}
	while(j<c1){
		a[k]=c[j];
		k++;
		j++;
	}
	
}
void Merge_sort(int a[],int l,int r){//归并排序
	if(l<r){
		int mid=(l+r)/2;
		Merge_sort(a,l,mid);
		Merge_sort(a,mid+1,r);
		Merge(a,l,r);
	}
}
void Radix_sort(int a[]){//基数排序
	int k=5;
	int b[n+2];
	int c[10];
	int rad=1;
	for(int i=1;i<=k;i++){
		for(int i=0;i<10;i++){
			c[i]=0;
		}
		for(int i=0;i<n;i++){
			int m=(a[i]/rad)%10;
			c[m]++;
		}
		for(int i=1;i<10;i++){
			c[i]+=c[i-1];
		}
		for(int i=n-1;i>=0;i--){
			int m=(a[i]/rad)%10;
			b[c[m]-1]=a[i];
			c[m]--;
		}
		for(int i=0;i<n;i++){
			a[i]=b[i];
		}
		rad*=10;
	}
}
int main(){
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
		fp.open(s.c_str(),ios::in);
		int t=n;
		while(t--){
			fp>>a[n-t-1];
		}
		
		cout<<"样本"<<i<<":"<<endl;
		clock_t startTime,endTime;
		//直接插入排序
		for(int i=0;i<n;i++){
			b[i]=a[i];
		}
		startTime = clock();//计时开始
		Insert_sort(b);
		endTime = clock();//计时结束
		cout << "直接插入排序运行时间:" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		
		//希尔排序
		for(int i=0;i<n;i++){
			b[i]=a[i];
		}
		startTime = clock();//计时开始
		Shell_sort(b);
		endTime = clock();//计时结束
		cout << "希尔排序运行时间:" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		
		//冒泡排序
		for(int i=0;i<n;i++){
			b[i]=a[i];
		}
		startTime = clock();//计时开始
		Bubble_sort(b);
		endTime = clock();//计时结束
		cout << "冒泡排序运行时间:" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		
		//快速排序
		for(int i=0;i<n;i++){
			b[i]=a[i];
		}
//		startTime = clock();//计时开始
//		//cout<<"--"<<endl;
//		Quick_sort(b,0,n-1);
//		//cout<<"**"<<endl;
//		endTime = clock();//计时结束
//		cout << "快速排序运行时间:" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		
		//选择排序
		for(int i=0;i<n;i++){
			b[i]=a[i];
		}
		startTime = clock();//计时开始
		Select_sort(b);
		endTime = clock();//计时结束
		cout << "选择排序运行时间:" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		
		//树形选择排序
		for(int i=0;i<n;i++){
			b[i]=a[i];
		}
		startTime = clock();//计时开始
		treeSelectSort(b);
		endTime = clock();//计时结束
		cout << "树形选择排序运行时间:" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		
		//堆排序
		for(int i=0;i<n;i++){
			b[i]=a[i];
		}
		startTime = clock();//计时开始
		Heap_sort(b);
		endTime = clock();//计时结束
		cout << "堆排序运行时间:" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		
		//归并排序
		for(int i=0;i<n;i++){
			b[i]=a[i];
		}
		startTime = clock();//计时开始
		Merge_sort(b,0,n-1);
		endTime = clock();//计时结束
		cout << "归并排序运行时间:" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		
		//基数排序
		for(int i=0;i<n;i++){
			b[i]=a[i];
		}
		startTime = clock();//计时开始
		Radix_sort(b);
		endTime = clock();//计时结束
		cout << "基数排序运行时间:" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		
		cout<<endl;
	
	}
	
	fp.close();
	return 0;
}
