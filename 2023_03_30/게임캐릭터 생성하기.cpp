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
		cout << "현재 레벨 출력 :" << level;
	}
	void setitem_num() {
		this->item_num = item_num++;
		cout << "현재 아이템 수 출력 :" << item_num;
	}
	void setitem_num1() {
		this->item_num = item_num--;
		cout << "현재 아이템 수 출력 :" << item_num;
	}
	void setall() {
		this->name, level, item_num;
	cout << "이름" << name << "레벨" << level<< "아이템" << item_num;
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
				cout << "이름 변경 :" << endl;
				cin >> name;
				game.setname(name);
			}
			else if (i == 2) {
				cout << "level up" << endl;
				game.setlevel();

			}
			else if (i == 3) {
				cout << "아이템 줍기" << endl;
				game.setitem_num();
			}
			else if (i == 4) {
				cout << "아이템 사용" << endl;
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
