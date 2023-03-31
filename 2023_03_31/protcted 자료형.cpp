#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::endl;

//private 자기 자신(해당 클래스 내)에서만 접근 가능
//protected 라는 자료형 : 자기 자신과, 자식 클래스에서 접근 가능
//public 모든곳에서 접근 가능
class Person { //Student의 부모 클래스, 슈퍼 클래스, 상위 클래스
protected:
	string name;
	int age;
	// 필드, 메소드, 생성자
public: // private, protected
	//Person() { return ???; } // 기본 생성자
	Person(string name, int age) {
		this->name = name;
		this->age = age;
	}
	Person() {}
	/*Person(int age) {
	}*/
	//Person p = Person("김소연");
	//Person() {}
	//Person p = Person();
	void sleep() { cout << "잠자기 zzzz"; }
};

class Student : public Person {
	// 부모 클래스에서 상속받은 멤버들의 접근제어자의 한계를 지정함.
	string stu_id;
protected:
	string name;
	int age;
public:
	//Student 생성자를 작성하지 않은 경우. 기본 형태
	//Student(){ Person(); ~~~~~; return; }
	Student(string name, int age) : Person(name, age) {
		//this->name = name;
		//this->age = age;
		//부모클래스의 생성자를 선택함.
		this->stu_id = "11111111111";
		//return 값;
	}
	void study() {
		sleep();
		cout << "공부하기";
	}
};

int main() {
	//Person p = Person("김소연"); // 객체를 생성하는 순간.
	//Person p = Person();

	//Person p = Person(1,3);
	Student s = Student("김ㅅ오ㅕㄴ", 99);
	s.sleep();

	return 0;
}