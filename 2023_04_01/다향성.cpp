#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
class Shape {
	int line_num;
public:
	Shape(int line_num) {
		this->line_num = line_num;
	}
	int getLineNum() {
		return line_num;
	}
};

class Rect : public Shape {
public:
	int height;
public:
	Rect(int height) : Shape(4) {
		this->height = height;
	}
	int getHeigth() {
		return height;
	}
};

class Tria : public Shape {
public:
	Tria() : Shape(3) {
	}
	// Tria() : Shape(){  }
};

int main() {
	Shape shape = Rect(5);
	cout << shape.getLineNum() << endl;
	// Shape에 있는 public 멤버에만 접근 가능함.
	// Rect에 있는 멤버에는 접근 불가능.

	Shape shapes[2] = { Rect(5), Tria() };
	cout << shapes[0].getLineNum() << endl;
	cout << shapes[1].getLineNum() << endl;


	//cout << shape.getHeigth() << endl; //

	//Rect rect = Shape(); // 안됨

	return 0;
}