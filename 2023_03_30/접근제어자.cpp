#include <iostream>

using namespace std;

class Cat {
	string name;
	int age;

public:
	Cat(string name, int age) {
		this->name = name;
		this->age = age;
		cout << name << " 고양이가 태어났습니다!\n";
	}

	string getName() {
		return name;
	}

	void setName(string name) {
		this->name = name;
	}

	void mew() {
		cout << "냐옹\n";
	}

};

int main() {
	Cat cat1("나비", 5);

	cout << cat1.getName() << endl;
	cat1.setName("도라에몽");
	cout << cat1.getName();
}