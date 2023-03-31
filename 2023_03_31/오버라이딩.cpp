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
		cout << "잠자기" << endl;
	}
	int override_test(int num) {
		return num;
	}
	int getAge() {
		return age;
	}
	
	//매개변수가 달라야 한다.
};

class Student : public Person {
	string stu_id;
public:
	Student(int age, string name, string stu_id) : Person(age, name){
		this->stu_id = stu_id;
	}
	//메소드 오버라이딩 안일어남
	void study() {
		cout << "공부하기" << endl;
	}
	//메소드 오버라이딩 일어남
		void sleep() { //부모에서 정의한 메소드를 자식 함수에서 다시 정의하는거
			cout << "10시에 잠자기" << endl;
	}
		int override_test(int num) {
			return num + getAge();  //getter를 사용해서 private을 가지고 오거나/ 접근제어자를 protected로 바꾸거나
			//Student에서 오버라이딩하기
			//Student에서 num에 age를 더해서 return하는 함수만들기
		}
	
		//함수(메소드)의 원형과 같다. 함수 이름, 매개변수 종류, 개수까지  다 같아야됨
};

int main() {
	Student s = Student(99, "홍길동", 132334121);
	
	s.sleep();
	cout << s.override_test(10);
	return 0;
}