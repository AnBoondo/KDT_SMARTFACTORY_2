#include <iostream>
#include <cstdlib>
#include <ctime> // �ð��� ��Ÿ���� ��
using namespace std;


int main()
{
	srand(time(NULL));
	int num = rand();
	cout << num;
	int tmp = num % 25 + 1;

}