#include <iostream>


int main() {
	int num = 0; // 변수의 선언과 초기화가 동시에
	int num1; //변수의 선언
	num1 = 0; //변수의 초기화
	std::string str = "";

	std::string fruit[3] = { "apple", "banana", "grape" };
	//::string fruit[] = { "apple", "banana", "grape" };//오른쪽에 3개 지정해줘서 굳이 []안에 3이라고 안써도 됨
	//선언할 때 크기가 정해져야 함

	std::cout << fruit << std::endl;
	std::cout << fruit[0] << std::endl;
	std::cout << fruit[1] << std::endl;
	std::cout << fruit[2] << std::endl;

	std::string fruit1[3]; //배열의 선언
	//인덱스는 무조건 0부터 시작한다 그래서 0이 첫번째
	fruit1[0] = "apple";
	fruit1[1] = "banana";
	fruit1[2] = "grape";
	
	//sizeof() : 변수, 자료형의 크기를 byte 단위로 만들어준다
	//예를 들어 int는 4byte인데 3개있으면 sizeof()이거는 12가 나온다.
	for (int i = 0; i < sizeof(fruit)/sizeof(fruit[0]); i++) {
		//sizeof(fruit)는 전체 / sizeof(fruit[0])는 하나짜리
		std::cin >> fruit[i];
		std::cout << fruit[i] << std::endl;
	}
}
