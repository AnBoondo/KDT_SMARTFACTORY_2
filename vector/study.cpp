#include <iostream>
using namespace std;
namespace wooriBank {
	int balance = 0;
	double deposit(int money) {
		double money_d = (double)money;
		return money_d + 0.03 * money_d;
	}
}
namespace hanaBank {
	int balance = 0;
	double deposit(int money) {
		double money_d = (double)money;
		return money_d + 0.05 * money_d;
	}
}

int main() {
	int money;
	string bank;
	cout << "���� ���� ������� ���⸦ �������� �Է��ϼ��� ";
	cin >> bank >> money; //�츮 10000

	if (bank == "�츮")
		cout << "���� ��� �ݾ�: " << wooriBank::deposit(money);
	else if (bank == "�ϳ�")
		cout << "���� ��� �ݾ�: " << hanaBank::deposit(money);
	else { cout << "������ �߸��Ǿ����ϴ�."; }
}