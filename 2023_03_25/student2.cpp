#include <iostream>

using namespace std;

int main() {
	int n;
	cout << "학생수 입력";
	cin >> n;
	int* arr = new int[n];
	const int student = 5;
	int score[student], sum = 0;
	for (int i = 0; i < n; i++) {
		arr[i] = 1 + i;
		cout << i + 1 << "번 학생의 성적을 입력해주세요" << endl;
		cin >> score[i];
		sum += score[i];
	}
	cout << (float)sum / student << endl;
	}

	//for (int i = 0; i < 5; i++) {
		//cout << i + 1 << "번 학생의 성적을 입력해주세요" << endl;
		//cin >> score[i];
		//sum += score[i];
//	}
	//cout << (float)sum / student << endl;

