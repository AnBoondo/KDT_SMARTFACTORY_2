#include <iostream>

using namespace std;

class Person {
	int age;
	string name;
public:
	Person(int age, string name) {
		this->age = age;
	    this->name = name;
	}
	void sleep() {
		cout << "���ڱ�" << endl;
	}
	int override_test(int num) {
		return num;
	}
	int getAge() {
		return age;
	}
	
	//�Ű������� �޶�� �Ѵ�.
};

class Student : public Person {
	string stu_id;
public:
	Student(int age, string name, string stu_id) : Person(age, name){
		this->stu_id = stu_id;
	}
	//�޼ҵ� �������̵� ���Ͼ
	void study() {
		cout << "�����ϱ�" << endl;
	}
	//�޼ҵ� �������̵� �Ͼ
		void sleep() { //�θ𿡼� ������ �޼ҵ带 �ڽ� �Լ����� �ٽ� �����ϴ°�
			cout << "10�ÿ� ���ڱ�" << endl;
	}
		int override_test(int num) {
			return num + getAge();  //getter�� ����ؼ� private�� ������ ���ų�/ ���������ڸ� protected�� �ٲٰų�
			//Student���� �������̵��ϱ�
			//Student���� num�� age�� ���ؼ� return�ϴ� �Լ������
		}
	
		//�Լ�(�޼ҵ�)�� ������ ����. �Լ� �̸�, �Ű����� ����, ��������  �� ���ƾߵ�
};

int main() {
	Student s = Student(99, "ȫ�浿", 132334121);
	
	s.sleep();
	cout << s.override_test(10);
	return 0;
}