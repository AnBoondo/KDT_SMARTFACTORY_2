//읽고 외우기
	//포인터 : 메모리 주소를 저장하는 변수
	//포인터를 이용하면, 동적 메모리를 생성할 수 있다.
	//포인터가 나오기 전에 배운 변수, 배열 -> 정적 메모리
	//정적 메모리 : int n; int arr[3]
	//동적 메모리 : 힙 영역 : 동적 메모리가 저장됨 , 할당과 해제를 직접 관리해줘야한다.
	//스택 영역 : 정적 메모리가 저장됨, 빌드 할때 크기가 지정되어 있어야 한다.
    //주의 : 포인터를 이용하면 동적 메모리를 생성할 수 있다는 거지, 포인터를 이용한 모든 변수가 동적 메모리는 아님 
    //동적 메모리는 new를 데리고 온다. new로 할당 delete로 반납
#include <iostream>

using namespace std;

int main() {

	//int* p = new int;

	//delete p;
	int num;
	std::cin >> num;
	//int arr[num];

	int* arr = new int[num];//배열인 변수는 delete[] arr;로 해제
	for (int i = 0; i < num; i++) {
		arr[i] = 1 + i;
	cout << arr[i] << " ";
	//}

//	delete[] arr;

	//num*num 행렬 만들기(**해주면 되는거 같음)
	//int* arr1 = new int [num];
	//{int int int}

	int** arr2 = new int* [num];
	//{{} ,{}, {}}

	for (int i = 0; i < num; i++) { //num은 {,,,}안에 컴마가 몇개 들아가는지 지정해주는 것
		arr2[i] = new int[num];
	}
	//{{,,,},{,,,,}}:{{,,}}제일 안에 있는 , 지정
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			arr2[i][j] = 1;

		}
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				cout << arr2[i][j] << " ";

			}
		}
		cout << endl;
		for (int i = 0; i < num; i++) {
			delete[] arr2[i];
		}
		delete[] arr2;
	}
}