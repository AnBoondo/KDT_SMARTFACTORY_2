
#include <iostream>
using namespace std;

class Subject {
protected:
	string name;
	string teacher;
	string exam;
};

class Korean : public Subject {
protected:
	string bookReview;
public:
	Korean() {
		this->name = "국어";
		this->teacher = "홍길동";
		this->exam = "9월 16일";
		this->bookReview = "10월 4일";
	}

	void printInfo() {
		cout << "과목명 : " << this->name << endl;
		cout << "선생님 : " << this->teacher << endl;
		cout << "시험날짜 : " << this->exam << endl;
		cout << "독후감 제출 : " << this->bookReview << endl;
	}
};

class Math : public Subject {
protected:
	string miniTest;
public:
	Math() {
		this->name = "수학";
		this->teacher = "성춘향";
		this->exam = "8월 16일";
		this->miniTest = "11월 24일";
	}

	void printInfo() {
		cout << "과목명 : " << this->name << endl;
		cout << "선생님 : " << this->teacher << endl;
		cout << "시험날짜 : " << this->exam << endl;
		cout << "쪽지시험 : " << this->miniTest << endl;
	}
};

int main(void) {
	Korean korean = Korean();
	Math math = Math();

	korean.printInfo();
	math.printInfo();
}