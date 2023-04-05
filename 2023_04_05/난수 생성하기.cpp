#include <iostream>
#include <cstdlib>
#include <ctime> // 시간을 나타내는 거
using namespace std;


int main()
{
	srand(time(NULL));
	int num = rand();
	cout << num;
	int tmp = num % 25 + 1;

}