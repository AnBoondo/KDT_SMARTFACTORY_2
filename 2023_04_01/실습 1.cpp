#include <iostream>
using namespace std;

class Snack {
protected:
	int price;
	string name;
	string Comp;
public:
	string get_name() {
		return name;
	}
	string get_Comp() {
		return Comp;
	}
	int get_price() {
		return price;
	}
};

class Candy : public Snack {
	string taste;
public:
	Candy(string name, string Comp, int price, string taste) : Snack() {
		this->name = name;
		this->Comp = Comp;
		this->price = price;
		this->taste = taste;
	}
	string get_taste() {
		return taste;
	}
};

class Choco : public Snack {
	string shape;
public:
	Choco(string name, string Comp, int price, string shape) : Snack() {
		this->name = name;
		this->Comp = Comp;
		this->price = price;
		this->shape = shape;
	}
	string get_shape() {
		return shape;
	}
};

int main() {
	Snack snackBasket[4] = { Candy("��","��", 100, "��"), Choco("����", "��ī", 1001, "�ձٸ��"), Candy("���ڸ�", "������", 10013, "��"), Choco("��ī��", "�ڿ�����", 1230, "�ﰢ��") };

	for (int i = 0; i < 4; i++) {
		cout << "name :" << snackBasket[i].get_name() << endl;

	}
}
	

