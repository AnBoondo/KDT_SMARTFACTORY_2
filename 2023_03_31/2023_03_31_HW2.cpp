#include <iostream>

using namespace std;
class Student {
	string name, school;
	int age, grade;
public:
	Student(string name, int age, string school, int grade) {
		this->name = name;
		this->school = school;
		this->grade = grade;
		this->age = age;
		cout << "name :" << name << endl << "age :" << age <<endl << "school :" << school <<endl << "grade :" << grade << endl;
		return;
	}
	void lunch() {
		cout << "점심은 학식" << endl;
	}
};
class KIM : public Student {

public:
	KIM(string name, int age, string school, int grade) : Student(name, age, school, grade) {
		cout << "name :" << name << endl << "age :" << age << endl << "school :" << school << endl << "grade :" << grade << endl;
		return;
	}
	void lunch() {
		cout << "점심은 맛있다." << endl;
	}
};

class Baek : public Student {

public:
	Baek(string name, int age, string school, int grade) : Student(name, age, school, grade) {
		cout << "name :" << name << endl << "age :" << age << endl << "school :" << school << endl << "grade :" << grade << endl;
		return;
	}
	void lunch() {
		cout << "점심은 맛djqtek." << endl;
	}
};

int main() {
	string n, s;
	int a, g, i;
	do {
		cin >> i;


		if (i == 1) {
			cin >> n;
			cin >> a;
			cin >> s;
			cin >> g;
			Student r = Student(n, a, s, g);
			r.lunch();
		}
		else if (i == 2) {
			cin >> n;
			cin >> a;
			cin >> s;
			cin >> g;
			KIM k = KIM(n, a, s, g);
			k.lunch();
		}
		else if (i == 3) {
			cin >> n;
			cin >> a;
			cin >> s;
			cin >> g;
			Baek b = Baek(n, a, s, g);
			b.lunch();
		}
		else if (i == 0) {
			break;
		}
	} while (i < 3);
	return(0);
}
	