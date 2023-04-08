#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


int main() {
	int com[3];
	int user[3];
	int strike, ball, out = 0;

	srand(time(NULL));
	for (int i = 0; i < 3; i++) {
		int num = rand();
		com[i] = num % 9 + 1;
		for (int j = 0; j < i; j++) {
			if (com[i] == com[j]) {
				i--;
				break;
			}
		}
	}
	while (1) {
		for (int i = 0; i < 3; i++) {
			cin >> user[i];
		}
		strike = ball = out = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (user[i] == com[j]) {
					if (i == j) {
						strike++;
					}
					else {
						ball++;
					}
				}
			}
		}
		if (strike == 0 && ball == 0) {
			out++;
			cout << "아웃" << endl;
		}
		else {
			cout << strike << "strike" << "  ";
			cout << ball << "ball" << "  ";
		}
		if (strike == 3) {
			cout << "game win" << endl;
			break;
		}
	}
	return 0;
}