#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(){
    ifstream file;
    file.open("hello.txt.txt");

   
    
    if (file.is_open()) {
        
      
    }
    string line;
    vector<string> lines;
    while (getline(file, line)) {
        lines.push_back(line);

        cout << endl;
        for (int i = lines.size() - 1; i >= 0; i--) {
            cout << lines[i] << endl;
        }
    }
 

    file.close();
}