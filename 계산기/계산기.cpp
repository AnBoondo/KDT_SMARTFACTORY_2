#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class calculator {
	int num1, num2;

public:
	void sum(int num1, int num2);
	int add();
	int sub();
	int mul();
	double div();
};

void calculator::sum(int x, int y)
{
	num1 = x;
	num2 = y;
}

int calculator::add() {
	return num1 + num2;
}

int calculator::sub() {
	return num1 - num2;
}

int calculator::mul() {
	return num1 * num2;
}

double calculator::div() {
	return (double)num1 / (double)num2;
}


int main() {
	calculator cal;
	string input = "AC";
	int result = 0;
	while (true) {
		int num1 = 0, num2 = 0;
		char c;
		if (input == "EXIT") break;
		else if (input == "AC") {
			cout << "첫번째 수를 입력하세요: ";
			cin >> num1;
		}
		else if (input == "Y") {
			num1 = result;
		}

		cout << "연산자를 입력하세요(+,-,*,/): ";
		cin >> c;

		cout << "두번째 수를 입력하세요: ";
		cin >> num2;

		cal.sum(num1, num2);

		switch (c) {
		case '+':
			result = cal.add();
			break;
		case '-':
			result = cal.sub();
			break;
		case '*':
			result = cal.mul();
			break;
		case '/':
			result = cal.div();
			break;
		}
		cout << "결과 :" << result << endl;
		cout << "AC를 입력하면 초기화, Y를 입력하면 계속 계산, EXIT는 종료: ";
		cin >> input;


	}
	return 0;
}