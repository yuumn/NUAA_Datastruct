#include<iostream>
#include<cstring>
#include<algorithm>
#include <fstream>
#include<ctime>

using namespace std;

const int N = 10;		//��������г��� 
const int mod = 113;

//�������  ��ʽ��  У���� + �ո� + ������Ϣ 
int main() {
	// ÿ���ַ���ASCII�뷶ΧΪ1-127 ����ĩλ������\0����
	// ������ \0 �������м� ��س���Ӳ�س���13 �� 10�� \t (9)�ĳ���  ���ǲ�û�к��Կո�32�� 
	//tips��'\0'ASCII��Ϊ0��cin����Կո�(32)
	srand(time(0));
	
	ofstream out;
	fstream out1;
	int op = 1;	//�������ĳ�2 �ǻ������ЧУ������ı� 
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
	int pos = -1;		//��ǳ��ֵ��׸���Ч�ڵ�   �����ڿ���̨���һ����Ч�ڵ��λ�þ���˵ 

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
			str += r1, sum += r1;		// ���������� �Ͳ�ȥģ���� 
			out1<<r1<<" ";
		}
		//str += '\0';
		out1<<endl<<sum<<endl;
		int res = (cnt  + sum + i) % mod;
		
		if (op == 2)		//op Ϊ 2 ʱ ����С�����Ŷ� 
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
