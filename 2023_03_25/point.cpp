#include <iostream>

using namespace std;

int main() {
	//int num[3];
//사용자한테 입력받은 수로 배열의 크기를 지정할 때
	//int size;
	//std::cin >> size;
	//int num1[size];
	int n = 3;
	
	int*p = &n;
	cout << p << endl; 
	cout << *p << endl;
	
	n=10; //p를 이용해서 n의 값을 *p를 사용해서 변경할 수 있다. 
	cout << p << endl; //그냥 변수 이름으로 접근하면, 주소값이 나옴.
	cout << *p; // n=10이라고 했기 때문에 10으로 출력된다.
	string str = "aaa";
	string* str_p = &str;
	cout << str_p << endl;
	cout << *str_p << endl;
	
	int& num = n; // num 참조 변수
	//n이라는 변수가 있는데, n이라는 변수에 num이라는 별명을 붙인 상황
	//이러면 num도 n도 n이 된 상황이다.

	num = 5;
	cout << n << endl;
	cout << &n << endl;
	cout << num << endl;
	//cout << *num << endl;
	cout << &num << endl;

	//읽고 외우기
	//포인터 : 메모리 주소를 저장하는 변수
	//포인터를 이용하면, 동적 메모리를 생성할 수 있다.
	//포인터가 나오기 전에 배운 변수, 배열 -> 정적 메모리
	//정적 메모리 : int n; int arr[3]
	//동적 메모리 : 힙 영역 : 동적 메모리가 저장됨 , 할당과 해제를 직접 관리해줘야한다.
	// 스택 영역 : 정적 메모리가 저장됨
	
}

