#include <iostream>


int main() {
	// 2 2 2
	// 2 23 1
	std::string country[5][5] = { "korea", "china", "japen", "USA", "germany" }; //[첫번째는 행2] [두번째는 열3]
	int j;
	int i;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 5; j++) {
			std::cout << country[i][j] << "" << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << i;
	std::cout << j;
}