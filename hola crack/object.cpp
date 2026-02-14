#include <iostream>
#include <string>

using namespace std;

class Animal {
private:
    int id;

protected:
    int energy;

public:
    string name;

    Animal(string name, int id) {
        this->name = name;
        this->id = id;
        energy = 100;
    }

    void rest() {
        energy += 10;
        cout << name << " rests. Energy = " << energy << endl;
    }

    void eat() {  
        energy += 15;
        cout << name << " eats. Energy = " << energy << endl;
    }

    void showId() {
        cout << name << " has id = " << id << endl;
    }

    void setEnergy(int e) {
        energy = e;
    }
};

class Dog : public Animal {
public:
    Dog(string name, int id) : Animal(name, id) {}

    void play() {
        energy -= 20;
        cout << name << " plays. Energy = " << energy << endl;
    }

    void bark() {
        energy -= 5;
        cout << name << " barks. Energy = " << energy << endl;
    }
};

class Cat : public Animal {
public:
    Cat(string name, int id) : Animal(name, id) {}

    void sleep() {
        energy += 5;
        cout << name << " sleeps. Energy = " << energy << endl;
    }
};

int main() {
    cout << "=== Creating objects ===" << endl;

    Animal a("GenericAnimal", 1);
    Dog d("Max", 2);
    Cat c("Michi", 3);

    cout << "\n=== public access ===" << endl;
    a.name = "RenamedAnimal";
    cout << "Animal name: " << a.name << endl;

    cout << "\n=== calling public methods ===" << endl;
    a.rest();
    d.play();
    c.sleep();

    cout << "\n=== private: not accessible from main ===" << endl;
    a.showId();

    cout << "\n=== main can modify protected indirectly (through a derived class method) ===" << endl;
    d.setEnergy(200);
    d.play();

    cout << "\n=== Done ===" << endl;

    cout << "\n=== Max commands loop (type SAFE to exit) ===\n";

    string action;

    while (true) {
        cout << "\nType bark, eat, or SAFE to exit:\n> ";
        cin >> action;

        if (action == "SAFE") {
            cout << "Exiting game\n";
            break;
        }
        else if (action == "bark") {
            d.bark();
        }
        else if (action == "eat") {
            d.eat(); 
        }
        else {
            cout << "Unknown command\n";
        }
    }

    return 0;
}
