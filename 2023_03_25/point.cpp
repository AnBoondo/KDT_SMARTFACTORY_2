#include <iostream>

using namespace std;

int main() {
	//int num[3];
//��������� �Է¹��� ���� �迭�� ũ�⸦ ������ ��
	//int size;
	//std::cin >> size;
	//int num1[size];
	int n = 3;
	
	int*p = &n;
	cout << p << endl; 
	cout << *p << endl;
	
	n=10; //p�� �̿��ؼ� n�� ���� *p�� ����ؼ� ������ �� �ִ�. 
	cout << p << endl; //�׳� ���� �̸����� �����ϸ�, �ּҰ��� ����.
	cout << *p; // n=10�̶�� �߱� ������ 10���� ��µȴ�.
	string str = "aaa";
	string* str_p = &str;
	cout << str_p << endl;
	cout << *str_p << endl;
	
	int& num = n; // num ���� ����
	//n�̶�� ������ �ִµ�, n�̶�� ������ num�̶�� ������ ���� ��Ȳ
	//�̷��� num�� n�� n�� �� ��Ȳ�̴�.

	num = 5;
	cout << n << endl;
	cout << &n << endl;
	cout << num << endl;
	//cout << *num << endl;
	cout << &num << endl;

	//�а� �ܿ��
	//������ : �޸� �ּҸ� �����ϴ� ����
	//�����͸� �̿��ϸ�, ���� �޸𸮸� ������ �� �ִ�.
	//�����Ͱ� ������ ���� ��� ����, �迭 -> ���� �޸�
	//���� �޸� : int n; int arr[3]
	//���� �޸� : �� ���� : ���� �޸𸮰� ����� , �Ҵ�� ������ ���� ����������Ѵ�.
	// ���� ���� : ���� �޸𸮰� �����
	
}

