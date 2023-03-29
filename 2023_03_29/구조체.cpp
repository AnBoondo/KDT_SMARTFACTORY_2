#include <iostream>
using namespace std;

struct Position {
	int width;
	int height;
};

int main() {
	Position p;
	int v;
	cin >> p.width ;
	cin >> p.height;
	

	cout << "가로 세로 길이를 입력하시오" << p.width << "    " << p.height << endl;

	v = p.width * p.height;

	cout <<"넓이 :" << v;

}