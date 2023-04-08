#include <iostream>
#include <cstdlib>
#include <ctime>
#include<vector>

using namespace std;

int main() {

	int n;
	cout << "홀수 입력 :";
	cin >> n;
	int i = 0;
	while (n % 2 == 0) {
		cout << "홀수가 아닙니다. 다시 입력해 주세요" << endl;
		cout << "홀수 입력 :";
		cin >> n;
	}
	vector <vector<int>> MS(n, vector<int>(n));

		int num = 1;
		int row = 0;
		int col = n / 2;
		MS[row][col] = 1;

		for (int a = 2; a <= n * n; a++) {
			num++;
			int new_row = (row - 1 + n) % n;
			int new_col = (col + 1) % n;

			if (MS[new_row][new_col] == 0) {
				row = new_row;
				col = new_col;
			}
			else {
				row = (row + 1) % n;
			}
			MS[row][col] = num;
		}

	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << MS[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
