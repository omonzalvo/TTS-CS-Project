#include <iostream>
using namespace std;

int main() {
    int opcion;
    double a, b;

    while (true) {
        cout << "\n CALCULADORA \n";
        cout << "1. Sumar\n";
        cout << "2. Restar\n";
        cout << "3. Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        if (opcion == 3) {
            cout << "Adios \n";
            break;
        }

        cout << "Ingresa el primer numero: ";
        cin >> a;

        cout << "Ingresa el segundo numero: ";
        cin >> b;

        if (opcion == 1) {
            cout << "Resultado: " << a + b << endl;
        }
        else if (opcion == 2) {
            cout << "Resultado: " << a - b << endl;
        }
        else {
            cout << "Opcion invalida\n";
        }
    }

    return 0;
}
