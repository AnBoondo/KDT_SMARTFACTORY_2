// vector.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector> // STL std::vector 이다.

using namespace std;

int main()
{
	//vector<int> v = { 1, 2, 3 };
	// 크기가 3인 배열. 원소가 1, 2, 3으로 초기화
	//vector<int> v(5);
	// 크기가 5인 배열을 만듦. 모든 값 0으로 초기화
	//vector<int> v(4, 1);
	// 크기가 4인 배열을 만듦. 모든 값을 1로 초기화
	// {1,1,1,1}
	//vector<int> v;
	//v.assign(5, 2);
	// 크기가 5인 배열을 만듦. 모든 값을 2로 초기화
	vector<int> v(6);
	//for (int i = 0; i < v.size(); i++) {
	//	cout << v[i] << "    ";
	//	cout << v.at(i) << endl;
	//}

	// 백터의 인덱스 0 ~ 4 까지(0부터 시작해서 5개만) 모두 2로 초기화
	//ex
	//v.size();//vector는 size를 제공해서 이런식으로 벡테 v의 사이즈를 반환해준다,
	//v.assign(5, 2);
	//for (int i = 0; i < 6; i++) {
	//	cout << v[i] << "   ";//오류를 out of range가 발생한다.
	//	cout << v.at(i) << endl;
	//}

	v.push_back(6); //vector의 제일 마지막에 원소 또는 문자를 넣는거
	//ex{2,2,2,2,6}이런 식으로 된다.
	v.pop_back(); // vector의 제일 마지막에 있는 원소 또는 문자를 꺼낸다.
	//ex{2,2,2,2} 다시 이렇게 변한다. 
	v.begin(); //vector의 시작 주소를 반환함
	v.insert(v.begin(), 5);
	//ex{5,2,2,2}
	v.erase(v.begin(), v.begin() + 3);
	//ex{2}
	v.clear();//vector를 싹 지우겠다
	
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << "    ";//v.at(i)로 교체 가능하다.
		cout << v.at(i) << endl;
	}
	vector<vector<int>> v2 = { {1,  2}, {3,   4} };
	for (int i = 0; i < v2.size(); i++) {
		for (int j = 0; j < v2.size(); j++) {
			cout << v2.at(i).at(j) << "    ";
		}
		cout << endl;
	}
	int n;
	cin >> n;
	vector <int> v;
	v.push_back(1);
	v.push_back(2);
	return (0);

}
