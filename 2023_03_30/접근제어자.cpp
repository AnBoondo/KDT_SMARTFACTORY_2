#include <iostream>

using namespace std;

class Cat {
	string name;
	int age;

public:
	Cat(string name, int age) {
		this->name = name;
		this->age = age;
		cout << name << " ����̰� �¾���ϴ�!\n";
	}

	string getName() {
		return name;
	}

	void setName(string name) {
		this->name = name;
	}

	void mew() {
		cout << "�Ŀ�\n";
	}

};

int main() {
	Cat cat1("����", 5);

	cout << cat1.getName() << endl;
	cat1.setName("���󿡸�");
	cout << cat1.getName();
}