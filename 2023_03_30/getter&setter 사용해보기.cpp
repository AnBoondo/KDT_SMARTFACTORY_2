#include <iostream>

using namespace std;

class Rectangle {
	int width;
	int height;

public:
	Rectangle() {
		// this->width = width;
		// this->height = height;
		cout << "width :" << width << "height :" << height << endl;
	}
	int getwidth() {
		return width;
	}
	int getheight() {
		return height;
	}
	void setwidth(int width) {
		this->width = width;
	}
	void setheight(int height) {
		this->height = height;
	}

	
	
};
int main() {
	int a, b;
	cin >> a;
	cin >> b;
	Rectangle area2;
	area2.setwidth(a);
	cout << area2.getwidth();
	area2.setheight(b);
	cout << area2.getheight();
	cout << endl << "area  :" << a * b;
}