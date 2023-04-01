#include <iostream>
using namespace std;

class Shape {
protected:
	virtual void draw() = 0;
};

class Circle : public Shape {
public:
	void draw() {
		cout << "�����̸�  :" << "circle" << endl;
	}
};

class Rect : public Shape {
public:
	void draw() {
		cout << "�����̸�  :" << "Rect" << endl;
	}
};

class Tria : public Shape {
public:
	void draw() {
		cout << "�����̸�  :" << "Tria" << endl;
	}
};

int main() {
	Circle c = Circle();
	c.draw();
	Rect r = Rect();
	r.draw();
	Tria t = Tria();
	t.draw();
}