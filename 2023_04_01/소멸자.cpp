#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::endl;

//Ŭ������ �ʵ�, �޼ҵ�, ������, �Ҹ��ڷ� ������.
//������ : ��ü�� ������ �� �ڵ����� ����Ǵ� �޼ҵ�
//�Ҹ��� : ��ü�� �Ҹ�� �� �ڵ����� ����Ǵ� �޼ҵ�

class Person {
public:
	Person() {
		cout << "Person ������ �Դϴ�" << endl;
	}
	//�����Լ� : �θ�Ŭ�������� ���ǵ� ����. 
	//�ڽ�Ŭ������ ������(�������̵�)�� ���̶�� ����ϴ� �Լ�
	//���� �����Լ� : ������ �ȵǾ� �ִ� �Լ� ( = 0)
	//virtual void sleep() = 0;
	virtual void sleep() { //���� �Լ� : ���� ���ε��� �ϱ� ����
		cout << "���ڱ�" << endl;
	}
};

class Student : public Person {
public:
	Student() : Person() {
		cout << "Student ������ �Դϴ�" << endl;
	}
	void sleep() { //���� �Լ��� ������(�������̵�)�� ��
		cout << "10�ÿ� ���ڱ�" << endl;
	}
};

int main() {
	Student s = Student();
	//Person ������ �Դϴ�
	//Student ������ �Դϴ�
	s.sleep(); // ���� ���ε�

	Person* s2 = new Student(); //��ĳ����
	s2->sleep(); // ���� ���ε�


	delete s2;

	return 0;
}