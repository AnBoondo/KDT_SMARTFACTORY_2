#include <iostream>
using namespace std;

class Snack {
public:
	void name() {
		cout << "name  :" << "��" << endl;
  }
};

class Candy : public Snack {
public:
	void name_c() {
		cout << "name  :" << "ĵ��" << endl;
	}
};

class Choco : public Snack {
public:
	void name_ch() {
		cout << "name  :" << "���ݷ�" << endl;
	}

};

int main() {
	Candy c;
	Snack* s = &c;
	cout << "���ɽ���" << endl;
	s->name();
	
	Snack* s2 = new Candy();
	Candy* c2 = (Candy*)s2;
	cout << "�ٿ��ɽ���" << endl;
	c2->name();
	c2->name_c();	

	Choco ch;
	Snack* s4 = &ch;
	cout << "���ɽ���" << endl;
	s->name();

	Snack* s5 = new Choco();
	Choco* c3 = (Choco*)s5;
	cout << "�ٿ��ɽ���" << endl;
	c3->name();
	c3->name_ch();
}