#include <iostream>

using namespace std;

class Rectangle {
	int width;
	int height;

public:
	Rectangle(int width, int height) {
		this->width = width;
		this->height = height;
		cout << "width :" << width << "height :" << height << endl;
	}

	void area() {
		int area1;
		area1 = width * height;
		cout << "area :" << area1;
	}
};

int main() {
	int a, b;
	cin >> a;
	cin >> b;
	Rectangle area2(a, b);
	area2.area();
}