#include <stdio.h>
#include <iostream>
using namespace std;

namespace seoul {
	int number = 02;
	string landmark = "경복궁";
	
}

namespace busan {
	int number = 51;
	string landmark = "해운대";
	}


	
	
	
	
	
	int main()
	{
		cout << "서울" << endl;
		cout << seoul::number << endl;
		cout << seoul::landmark << endl;
		cout << "부산" << endl;
		cout << busan::number << endl;
		cout << busan::landmark << endl;
	}