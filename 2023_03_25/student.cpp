#include <iostream> 

using namespace std;

int main() {
	string name;
	const int student = 5;
	int score[student];
	int sum;
	
	for (int i = 0; i < student; i++) {
		cout << i + 1 << "번 학생 점수를 입력해주세요." << endl;
		cin >> score[i];
		sum += score[i];
	}

	cout << endl << "지도교수명 : " << name << endl;
	cout << "합 : " << sum << ",   평균 : " << (float)sum / student << endl;
}
