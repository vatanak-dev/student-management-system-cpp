#include <iostream>
#include <vector>
using namespace std;

class Student {
private:
    int id;
    string name;
    int age;

public:
    void setData();
    void display();
    int getId();
};
void Student::setData() {
    cout << "Enter ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Age: ";
    cin >> age;
}

void Student::display() {
    cout << "ID: " << id
         << " | Name: " << name
         << " | Age: " << age << endl;
}

int Student::getId() {
    return id;
}
int main() {
    vector<Student> students;
    int choice;

    do {
        cout << "\n1. Add Student";
        cout << "\n2. View Students";
        cout << "\n3. Search Student";
        cout << "\n4. Exit";
        cout << "\nChoose: ";
        cin >> choice;

        if (choice == 1) {
            Student s;
            s.setData();
            students.push_back(s);
        }
        else if (choice == 2) {
            for (auto &s : students) {
                s.display();
            }
        }
        else if (choice == 3) {
            int searchId;
            cout << "Enter ID to search: ";
            cin >> searchId;

            bool found = false;
            for (auto &s : students) {
                if (s.getId() == searchId) {
                    s.display();
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Student not found!\n";
        }

    } while (choice != 4);

    return 0;
}
