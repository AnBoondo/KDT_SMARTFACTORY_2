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
	Snack snackBasket[4] = { Candy("초","코", 100, "굿"), Choco("차차", "코카", 1001, "둥근모양"), Candy("초코링", "오에코", 10013, "굿"), Choco("차카링", "코에가나", 1230, "삼각형") };

	for (int i = 0; i < 4; i++) {
		cout << "name :" << snackBasket[i].get_name() << endl;

	}
}
	

