//�а� �ܿ��
	//������ : �޸� �ּҸ� �����ϴ� ����
	//�����͸� �̿��ϸ�, ���� �޸𸮸� ������ �� �ִ�.
	//�����Ͱ� ������ ���� ��� ����, �迭 -> ���� �޸�
	//���� �޸� : int n; int arr[3]
	//���� �޸� : �� ���� : ���� �޸𸮰� ����� , �Ҵ�� ������ ���� ����������Ѵ�.
	//���� ���� : ���� �޸𸮰� �����, ���� �Ҷ� ũ�Ⱑ �����Ǿ� �־�� �Ѵ�.
    //���� : �����͸� �̿��ϸ� ���� �޸𸮸� ������ �� �ִٴ� ����, �����͸� �̿��� ��� ������ ���� �޸𸮴� �ƴ� 
    //���� �޸𸮴� new�� ������ �´�. new�� �Ҵ� delete�� �ݳ�
#include <iostream>

using namespace std;

int main() {

	//int* p = new int;

	//delete p;
	int num;
	std::cin >> num;
	//int arr[num];

	int* arr = new int[num];//�迭�� ������ delete[] arr;�� ����
	for (int i = 0; i < num; i++) {
		arr[i] = 1 + i;
	cout << arr[i] << " ";
	//}

//	delete[] arr;

	//num*num ��� �����(**���ָ� �Ǵ°� ����)
	//int* arr1 = new int [num];
	//{int int int}

	int** arr2 = new int* [num];
	//{{} ,{}, {}}

	for (int i = 0; i < num; i++) { //num�� {,,,}�ȿ� �ĸ��� � ��ư����� �������ִ� ��
		arr2[i] = new int[num];
	}
	//{{,,,},{,,,,}}:{{,,}}���� �ȿ� �ִ� , ����
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