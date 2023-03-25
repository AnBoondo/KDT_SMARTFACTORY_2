#include <iostream>


int main() {
	// 2 2 2
	// 2 23 1
	int num[2][3] = { {2, 2, 2}, 
		{2, 23, 1} }; //[첫번째는 행2] [두번째는 열3]
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
	

}
