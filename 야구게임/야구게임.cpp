#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


int main() {
	int com[3];  // 컴퓨터와 사용자가 3자리 숫자를 저장하는 배열
	int user[3];
	int strike, ball, out; // 컴퓨터와 사용자가 입력한 숫자를 비교하기 위한 변수

	srand(time(NULL)); // 난수 발생기를 현재 시간으로 설정 시간 설정
	for (int i = 0; i < 3; i++) {  //for문을 사용해서 배열에 숫자 3개를 입력
		int num = rand(); 
		com[i] = num % 9 + 1; //1부터 9까지의 숫자를 랜덤으로 배정
		for (int j = 0; j < i; j++) { 
			if (com[i] == com[j]) {
				i--;   // if문을 사용해서 전에 나왔던 숫자랑
				break; 
			}
		}
	}
	while (1) {  //game win 코드까지 가기전까지 반복해주기 위해 while 사용
		for (int i = 0; i < 3; i++) {
			cin >> user[i]; // 유저도 3자리 숫자를 받았기 때문에 3자리 숫자 입력
		}
		strike = ball = out = 0; // 스트라이크 볼 아웃 초기화 (처음에 아무것도 없기 때문에 변수에 숫자를 입력해주는걸 초기화 하라고 한다.)
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (user[i] == com[j]) {
					if (i == j) { //컴퓨터와 사용자의 숫자가와 자리가 같으면 스트라이크
						strike++;
					}
					else {
						ball++;//숫자만 같으면 볼
					}
				}
			}
		}
		if (strike == 0 && ball == 0) {
			out++; // out 변수를 1 증가시키고 아웃을 출력
			cout << "아웃" << endl; //스트라이크도 없고 볼도 없으면 아웃
		}
		else {
			cout << strike << "strike" << "  "; //그게 아니라면 스트라이크 또는 볼이 뜨게
			cout << ball << "ball" << "  ";
		}
		if (strike == 3) {
			cout << "game win" << endl; //숫자 3개 다 맞추면 game win한다.
			break;
		}
	}
	return 0;
}