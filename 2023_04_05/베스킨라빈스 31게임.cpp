#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	int i, j, k = 0;
	int n1, n2;

	while (1) {
		if (k >= 31) {
			break;
		}
		else cout << "������ �Է��ϼ��� :";
		cin >> n1;

		j = k;
		for (i = j + 1; i <= (n1 + j); i++) {
			cout << i << endl;
			k++;
		}
		if (k == 31) {
			cout << "��ǻ�� ��" << endl;
			break;
		}

		j = k;
		srand(time(NULL));
		int num = rand();
			n2 = num % 3 + 1;
			cout << "��ǻ�Ͱ� �Է��� �� :" << n2 << endl;
			for (i = j + 1; i <= (n2 + j); i++) {
				cout << i << endl;
				k++;
				if (k == 31) {
					cout << "����� ��" << endl;
					break;
				}
			}
		
	}
	
}