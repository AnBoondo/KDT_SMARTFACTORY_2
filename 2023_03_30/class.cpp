#include <iostream>

using namespace std;

class Cat {
	string name;
	int age;
	
public:
	Cat(string name, int age) {
		this->name = name; //this�� Ŭ���� �Լ��� �ִ� ������ �����Լ��� �������ش� ���̴�.
		this->age = age;
		cout << name << "����̰� �¾���ϴ�!\n";
	}


	void mew() {
		cout << "�Ŀ�\n";
	}



};

int main() {
	Cat cat1("����", 5);

	cat1.mew();
}