#include <iostream>


int main() {
	int num = 0; // ������ ����� �ʱ�ȭ�� ���ÿ�
	int num1; //������ ����
	num1 = 0; //������ �ʱ�ȭ
	std::string str = "";

	std::string fruit[3] = { "apple", "banana", "grape" };
	//::string fruit[] = { "apple", "banana", "grape" };//�����ʿ� 3�� �������༭ ���� []�ȿ� 3�̶�� �Ƚᵵ ��
	//������ �� ũ�Ⱑ �������� ��

	std::cout << fruit << std::endl;
	std::cout << fruit[0] << std::endl;
	std::cout << fruit[1] << std::endl;
	std::cout << fruit[2] << std::endl;

	std::string fruit1[3]; //�迭�� ����
	//�ε����� ������ 0���� �����Ѵ� �׷��� 0�� ù��°
	fruit1[0] = "apple";
	fruit1[1] = "banana";
	fruit1[2] = "grape";
}