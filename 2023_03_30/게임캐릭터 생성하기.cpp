#include <iostream>

using namespace std;

class Character {
	string name;
	string all;
	int level=0, item_num=0;

public:
	Character(string name) {
		//this->name = name;
		//this->level = 0;
		//this->item_num = 0;

		cout << "name :" << name << "   " << "level :" << level << "   " << "item_num" << item_num << endl;
	}
	int getlevel() {

	}
	int getitem_num() {
		item_num++;
	}
	void setname(string name) {
		this->name = name;
	}
	void setlevel() {
		this->level = level++;
		cout << "���� ���� ��� :" << level;
	}
	void setitem_num() {
		this->item_num = item_num++;
		cout << "���� ������ �� ��� :" << item_num;
	}
	void setitem_num1() {
		this->item_num = item_num--;
		cout << "���� ������ �� ��� :" << item_num;
	}
	void setall() {
		this->name, level, item_num;
	cout << "�̸�" << name << "����" << level<< "������" << item_num;
	}

};

	int main() {
		int i;
		string name;
		cin >> name;
		Character game(name);

		do {
			cin >> i;
			if (i == 1) {
				cout << "�̸� ���� :" << endl;
				cin >> name;
				game.setname(name);
			}
			else if (i == 2) {
				cout << "level up" << endl;
				game.setlevel();

			}
			else if (i == 3) {
				cout << "������ �ݱ�" << endl;
				game.setitem_num();
			}
			else if (i == 4) {
				cout << "������ ���" << endl;
				game.setitem_num1();
			}
			else if (i == 5) {
				game.setall();
			}
			else if (i == 0) {
				break;
			}
		} while (i < 6);
		return(1);
	}
