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
	Person* p2 = &s; // ��ĳ����
	//delete p2; // ��Ÿ�� ����
	p2->test();
	//p2->test_stu(); // �Ұ���

	Person* p3 = new Student(); // ��ĳ����
	//��ĳ���� : �θ� Ŭ������ �����ͷ� �ڽ� Ŭ������ �ν��Ͻ��� ����Ű�� ��
	//�ٿ�ĳ���� : ��ĳ���� �� ���� �ٽ� �����·� ������ ��

	Student* stu = (Student*)p3; // �ٿ� ĳ����
	stu->test();
	stu->test_stu();

	//Person p = Student(); 
	//Student st = (Student)p; // ����!

	delete p3;
	return 0;
}