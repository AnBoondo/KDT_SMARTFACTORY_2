#include <iostream>

using namespace std;

int main() {
	string name;
	const int student = 5;
	int score[student], sum = 0;


	for (int i = 0; i < student; i++) {
		cout << i + 1 << "�� �л��� ������ �Է����ּ���" << endl;
		cin >> score[i];
		sum += score[i];
	}
	cout << (float)sum / student << endl;
}