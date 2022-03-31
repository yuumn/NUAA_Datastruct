#include<iostream>
#include<cstring>
#include<algorithm>
#include <fstream>
#include<ctime>

using namespace std;

const int N = 10;		//生成最长序列长度 
const int mod = 113;

//随机样本  格式：  校验码 + 空格 + 序列信息 
int main() {
	// 每个字符的ASCII码范围为1-127 （除末位），以\0结束
	// 避免了 \0 出现在中间 软回车和硬回车（13 和 10） \t (9)的出现  但是并没有忽略空格（32） 
	//tips；'\0'ASCII码为0，cin会忽略空格(32)
	srand(time(0));
	
	ofstream out;
	fstream out1;
	int op = 1;	//！！！改成2 是会出现无效校验码的文本 
	if (op == 1) out.open("demo_right1.txt", ios::out);
	else  out.open("demo_wrong1.txt", ios::out);
	out1.open("in.txt",ios::out);
	out1.close();
	
	out1.open("in.txt", ios::in);
	if (!out.is_open()) {
		printf("Init Error\n");
		return 0;
	}


	int cnt = 0;
	int flag = 1;
	int pos = -1;		//标记出现的首个无效节点   最后会在控制台输出一个无效节点的位置就是说 

	for (int i = 0; i < N; i ++ )
	{
		string str;
		int sum = 0; 
		int len = rand() % 30 + 5;//[1,30]
		for (int j = 0; j < len; j ++)
		{
			int r1 = rand() % 127+1;//[1,127]
			if (r1 == 13 || r1 == 10 || r1 == 9 || r1 == 26) 
			{
				j --; 
				continue;	
			}
			/*
			if(r1<10) str+=('0'+r1);
			else{
				str+=('0'+r1/10);
				str+=('0'+r1%10); 
			}
			*/
			str += r1, sum += r1;		// 数据量不大 就不去模了先 
			out1<<r1<<" ";
		}
		//str += '\0';
		out1<<endl<<sum<<endl;
		int res = (cnt  + sum + i) % mod;
		
		if (op == 2)		//op 为 2 时 发生小概率扰动 
		{
			
			int rr = rand() % 100;
			if (rr < 1)
			{
				int r2 = rand() % 20 + 1;
				res += r2;
				if (pos == -1) pos = i;
			}
		}
		
		out << res << " " << str << endl;
		cnt=res;
	}
	out.close();
	out1.close();
	cout << pos;
	return 0;
}
