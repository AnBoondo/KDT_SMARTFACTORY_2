
#include <iostream>

int main()
{
    std::cout << "1���� n������ �� ���ϱ�";
    int n, sum = 0;
    std::cout << "\n";
    std::cout << "���ڸ� �Է��ϼ���";
    std::cin >> n;

    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    std::cout << sum;

    return 0;
}
