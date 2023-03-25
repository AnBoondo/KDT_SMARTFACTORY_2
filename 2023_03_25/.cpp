#include <iostream>


int main() {
	// 2 2 2
	// 2 23 1
	int num[2][3] = { {2 , 2 , 2}, {2 , 23 , 1} }; //[첫번째는 행2] [두번째는 열3]
	int i, j;
	
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			std::cout << num[i][j] << "";
		}
		std::cout << std::endl;
	}
	std::cout << i;
	std::cout << j;
	// a b c d
	//e f g h
	std::string alpha[2][4] = { {"a","b","c","d"},{"e","f","g","h"} };
	
	int num2[3] = { 1 , 2 , 3 };
	for (int i = 0; i < 3; i++) {
		std::cout << num2[i] << " ";
	}
	std::cout << std::endl;

	//처음 돌때는 n = 1 두번째 돌때는 n = 2 밑에 코드로 작성하면 하나씩 순서대로 한다는 말 같음 
	for (auto n : num2) { 
		//배열원소 하나하나에 접근하겠다는 말
		//배열 : 원소
		std::cout << n << "";
	}
	std::cout << std::endl;

	for (auto i = 0; i < 3; i++) {
		
	}
}
