#include <iostream>


int main() {
	// 2 2 2
	// 2 23 1
	int num[2][3] = { {2 , 2 , 2}, {2 , 23 , 1} }; //[ù��°�� ��2] [�ι�°�� ��3]
	int i, j;
	
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			std::cout << num[i][j] << "";
		}
		std::cout << std::endl;
	}
	std::cout << i;
	std::cout << j;
	// a b c d
	//e f g h
	std::string alpha[2][4] = { {"a","b","c","d"},{"e","f","g","h"} };
	
	int num2[3] = { 1 , 2 , 3 };
	for (int i = 0; i < 3; i++) {
		std::cout << num2[i] << " ";
	}
	std::cout << std::endl;

	//ó�� ������ n = 1 �ι�° ������ n = 2 �ؿ� �ڵ�� �ۼ��ϸ� �ϳ��� ������� �Ѵٴ� �� ���� 
	for (auto n : num2) { 
		//�迭���� �ϳ��ϳ��� �����ϰڴٴ� ��
		//�迭 : ����
		std::cout << n << "";
	}
	std::cout << std::endl;

	for (auto i = 0; i < 3; i++) {
		
	}
}
