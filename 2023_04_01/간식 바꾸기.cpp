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
		cout << "종류 : 사탕" << endl;
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
		cout << "종류 : 초콜렛" << endl;
		cout << "name :" << name << endl;
		cout << "Comp :" << Comp << endl;
		cout << "price :" << price << endl;
		cout << "shape :" << shape << endl;
	}
};

int main() {
	Snack* snackBasket[4] = { new Candy("초","코리아산업", 100, "굿"), new Choco("차차", "코카산업", 1001, "둥근모양"), new Candy("초코링", "오에코", 10013, "굿"), new Choco("차카링", "코에가나", 1230, "삼각형") };

	for (int i = 0; i < 4; i++) {
		snackBasket[i]->candy_status();
		cout << "--------------------\n";
	}
}




