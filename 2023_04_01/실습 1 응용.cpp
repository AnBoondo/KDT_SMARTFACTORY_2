#include <iostream>
using namespace std;

class Snack {
public:
	void name() {
		cout << "name  :" << "초" << endl;
  }
};

class Candy : public Snack {
public:
	void name_c() {
		cout << "name  :" << "캔디" << endl;
	}
};

class Choco : public Snack {
public:
	void name_ch() {
		cout << "name  :" << "초콜렛" << endl;
	}

};

int main() {
	Candy c;
	Snack* s = &c;
	cout << "업케스팅" << endl;
	s->name();
	
	Snack* s2 = new Candy();
	Candy* c2 = (Candy*)s2;
	cout << "다운케스팅" << endl;
	c2->name();
	c2->name_c();	

	Choco ch;
	Snack* s4 = &ch;
	cout << "업케스팅" << endl;
	s->name();

	Snack* s5 = new Choco();
	Choco* c3 = (Choco*)s5;
	cout << "다운케스팅" << endl;
	c3->name();
	c3->name_ch();
}