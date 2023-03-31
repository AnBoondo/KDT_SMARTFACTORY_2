#include <iostream>

using namespace std;

class Shape {
	int width_num, width_length;

public:
	Shape(int width_num, int width_length) {
		this->width_num = width_num;
		this->width_length = width_length;
	
		printf("���� ���� : %d, �غ��� ���� : %d", width_num, width_length);
		return;
	}
	int getwidth_length() {
		return width_length;
	}
};
	
class Rectangle : public Shape {
	
	int R_height;
public:
	Rectangle(int width_num, int width_length, int R_height) : Shape(width_num, width_length){
		this->R_height = R_height;
		cout << "���α���  :" << R_height << endl;
	}
	void area() {
		cout << "�簢�� area  :" << getwidth_length() * R_height << endl;
	}
};

class Triangle : public Shape{
	int T_height;

public:
	Triangle(int width_num, int width_length, int T_height) : Shape(width_num, width_length) {
		this->T_height = T_height;
		cout << "����  :" << T_height << endl;
	}
	void area1() {
		cout << "�ﰢ�� area  :" << getwidth_length() * T_height << endl;
	}
};


int main() {
	int a, b, c, d, i;
	cin >> a;
	cin >> b;
	if (a == 4) {
		cin >> c;
		Rectangle r = Rectangle(a, b, c);
		r.area();
	}
	else if (a == 3) {
		cin >> d;
		Triangle t = Triangle(a, b, d);
		t.area1();
	}
	return 0;
}