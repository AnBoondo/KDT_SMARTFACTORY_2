
#include <iostream>

int main()
{
    std::cout << "1부터 n까지의 합 구하기";
    int n, sum = 0;
    std::cout << "\n";
    std::cout << "숫자를 입력하세요";
    std::cin >> n;

    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    std::cout << sum;

    return 0;
}
