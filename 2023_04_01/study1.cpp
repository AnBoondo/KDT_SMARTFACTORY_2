#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Person {
public:
	void test() {
		cout << "test" << endl;
	}
};

class Student : public Person {
public:
	void test_stu() {
		cout << "test student" << endl;
	}
};


int main() {
	// Person p = Student(); 
	// p.test();
	// Student p = Person(); 

	Student s;
	Person* p2 = &s; // 업캐스팅
	//delete p2; // 런타임 오류
	p2->test();
	//p2->test_stu(); // 불가능

	Person* p3 = new Student(); // 업캐스팅
	//업캐스팅 : 부모 클래스의 포인터로 자식 클래스의 인스턴스를 가리키는 것
	//다운캐스팅 : 업캐스팅 된 것을 다시 원상태로 돌리는 것

	Student* stu = (Student*)p3; // 다운 캐스팅
	stu->test();
	stu->test_stu();

	//Person p = Student(); 
	//Student st = (Student)p; // 오류!

	delete p3;
	return 0;
}