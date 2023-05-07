#include <iostream>
using namespace std;
int main()
{
    int myArray[5];
    myArray[0] = 1;
    myArray[1] = 3;
    myArray[2] = 5;
    myArray[3] = 7;
    myArray[4] = 9;
    int size = sizeof myArray / 4;
    for (int i = 0; i < size; i++)
    {
        cout << myArray[i] << ", ";
     
    }
    cout << endl;


    cout << "[---------------]" << endl;
    int yourArray[5] = { 2, 4, 6, 8, 10 };
    for (int i = 0; i < size; i++)
    {
        cout << yourArray[i] << ", ";
   
    }
    cout << endl;
}