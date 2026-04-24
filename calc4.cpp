#include <iostream>

using namespace std;

int main() {

    bool condition = true;
    bool* pCondition = &condition; 
    cout << "condition = " << condition << "\n";

    cout << "Size of bool: " << sizeof(bool) << "byte(s)\n";
    cout << "Size of pointer to bool" << sizeof(pCondition) << " byte(s)\n";  

    delete pCondition;
    pCondition = nullptr;

    int x = 42;
    int* pX = &x;
    cout << "x =" << sizeof(int) << "byte(s)\n";
    cout << "Size of int: " << sizeof(pX) << " byte(s)\n";
    cout << "pX points to int with value: " << pX << "\n";

    char c= 'A';
    char* pC = &c;
    cout << "pC points to char with value: " << pC << "\n";
    cout << "pC pints to char with value: " << *pC << "\n";
    cout << "c = " << c << "\n";
    cout << "Size of char: " << sizeof(char) << " byte(s)\n";
    cout << "Size of pointer to char: " << sizeof(pC) << " byte(s)\n";

    pCondition = nullptr;
    pC = nullptr;
    pC = nullptr;

    cout << x << "\n";


    
    return 0;

}