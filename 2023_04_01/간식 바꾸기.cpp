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
public:
	virtual void candy_status() {

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
	void candy_status() {
		cout << "���� : ����" << endl;
		cout << "name :" << name << endl;
		cout << "Comp :" << Comp << endl;
		cout << "price :" << price << endl;
		cout << "taste :" << taste << endl;
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
	void candy_status() {
		cout << "���� : ���ݷ�" << endl;
		cout << "name :" << name << endl;
		cout << "Comp :" << Comp << endl;
		cout << "price :" << price << endl;
		cout << "shape :" << shape << endl;
	}
};

int main() {
	Snack* snackBasket[4] = { new Candy("��","�ڸ��ƻ��", 100, "��"), new Choco("����", "��ī���", 1001, "�ձٸ��"), new Candy("���ڸ�", "������", 10013, "��"), new Choco("��ī��", "�ڿ�����", 1230, "�ﰢ��") };

	for (int i = 0; i < 4; i++) {
		snackBasket[i]->candy_status();
		cout << "--------------------\n";
	}
}




