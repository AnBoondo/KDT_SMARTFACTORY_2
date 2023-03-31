#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::endl;
//private 자기 자신(해당 클래스 내)에서만 접근 가능
//protcted 라는 자료형 : 자기 자신과, 자식 클래스에서 접근 가능
//public 모든곳에서 접근 가능
class Person { //Student의 부모 클래스, 슈퍼 클래스, 상위 클래스
	string name;
	int age;
	// 이렇게 아무것도 변수 지정 안되어 있는게 ptivate이다.
	// 필드, 메소드, 생성자
public: // private, protected
	//Person() { return ???; } // 기본 생성자
	Person(string name,int age) { 
		this->name = name; 
		this->age = age;
		cout << "name  :" << name << endl << "age  :" << age << endl;
		return;
	}
	//Person p = Person("김소연");

	//Person p = Person();
	void sleep() { cout << "잠자기 zzzz"; }
};

class Student : public Person { //public은 부모클래스에서 상속받은 멤버(필드, 메소드, 생성자)들의 접근제어자의 한계를 지정해준다.
	  string stu_id;

	// Student 생성자를 작성하지 않았다는 건. 
	// Student 기본생성자를 호출하고 부모의 기본생성자를 호출하게 됨.
public:
	Student(string name, int age) : Person(name, age) {
	
		//부모 클래스의 생성자를 선택함.
		//이 부분은 값을 읽는다
		//return(값)
		this->stu_id = "11111111";
		cout << stu_id << endl;
		cout << "name  :" << name << endl << "age  :" << age;
		return;
	}

};




int main() {
	Person p = Person("김소연", 15); // 객체를 생성하는 순간.

	Student s = Student("안분도", 3);

	s.sleep();

	//Person p = Person(1,3);

	//Student s = Student();

	return 0;
}