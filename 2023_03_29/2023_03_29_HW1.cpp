#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

	ofstream member("member.txt");

	cout << "3���� ȸ���� ���� �̸�, ��й�ȣ�� ���������� �Է��ϼ���.\n";

	for (int i = 0; i < 3; i++) {
		cout << i + 1 << "��° ȸ�� : ";

		string info;
		getline(cin, info);

		if (member.is_open()) member << info << endl;
	}

	member.close();

	ifstream member_r("member.txt");
	string line;

	if (member_r.is_open()) {
		while (getline(member_r, line)) {
			cout << line << endl;
		}
	}

	member_r.close();
}