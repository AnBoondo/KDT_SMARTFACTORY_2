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
	

	cout << "���� ���� ���̸� �Է��Ͻÿ�" << p.width << "    " << p.height << endl;

	v = p.width * p.height;

	cout <<"���� :" << v;

}