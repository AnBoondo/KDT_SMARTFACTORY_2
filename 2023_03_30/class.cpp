#include <iostream>

using namespace std;

class Cat {
	string name;
	int age;
	
public:
	Cat(string name, int age) {
		this->name = name; //this가 클래스 함수에 있는 변수를 메인함수로 지정해준단 말이다.
		this->age = age;
		cout << name << "고양이가 태어났습니다!\n";
	}


	void mew() {
		cout << "냐옹\n";
	}



};

int main() {
	Cat cat1("나비", 5);

	cat1.mew();
}