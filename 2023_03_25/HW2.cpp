#include <iostream>

using namespace std;

int main() {
	int x;
	int y;
	cout << "x�� �Է����ּ���" << endl;
	cin >> x;
	cout << "y�� �Է����ּ���" << endl;
	cin >> y;
	int** num;
	num = new int* [x];
	for (int i = 0; i < x; i++) {
		num[i] = new int[y];
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			num[i][j] = i * y + j;
		}
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			cout << num[i][j] << "   ";
		}
		cout << endl;
	}

}
