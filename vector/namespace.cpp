#include <stdio.h>
#include <iostream>
using namespace std;

namespace seoul {
	int number = 02;
	string landmark = "�溹��";
	
}

namespace busan {
	int number = 51;
	string landmark = "�ؿ��";
	}


	
	
	
	
	
	int main()
	{
		cout << "����" << endl;
		cout << seoul::number << endl;
		cout << seoul::landmark << endl;
		cout << "�λ�" << endl;
		cout << busan::number << endl;
		cout << busan::landmark << endl;
	}