#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>   
using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    string major;
    float gpa;
};

vector<Student> students;
void loadStudents() {
    students.clear();
    ifstream file("students.txt");
    if (!file) return;

    string line;
    int lineNum = 0;
    while (getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;

        try {
            stringstream ss(line);
            string token;
            Student s;

            
            if (!getline(ss, token, '|')) throw runtime_error("missing id");
            s.id = stoi(token);

            if (!getline(ss, s.name, '|'))  throw runtime_error("missing name");
            if (!getline(ss, token, '|'))   throw runtime_error("missing age");
            s.age = stoi(token);

            if (!getline(ss, s.major, '|')) throw runtime_error("missing major");
            if (!getline(ss, token, '|'))   throw runtime_error("missing gpa");
            s.gpa = stof(token);

            students.push_back(s);
        } catch (exception &e) {
            cout << "Warning: skipping invalid line " << lineNum
                 << " in students.txt (" << e.what() << ")\n";
        }
    }

    file.close();
}
void saveStudents() {
    ofstream file("students.txt");

    if (!file) {
        cout << "Error saving file.\n";
        return;
    }
    for (auto &s : students) {
        file << s.id    << "|"
             << s.name  << "|"
             << s.age   << "|"
             << s.major << "|"
             << s.gpa   << "\n";
    }

    file.close();
}
bool idExists(int id) {
    for (auto s : students) {
        if (s.id == id)
            return true;
    }
    return false;
}
void addStudent() {
    Student s;

    cout << "Enter ID: ";
    cin >> s.id;
    cin.ignore();
    if (idExists(s.id)) {
        cout << "Student ID already exists.\n";
        return;
    }

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Age: ";
    cin >> s.age;
    cin.ignore();

    cout << "Enter Major: ";
    getline(cin, s.major);

    cout << "Enter GPA: ";
    cin >> s.gpa;

    students.push_back(s);
    saveStudents();

    cout << "Student added successfully.\n";
}
void printTable(ostream &out, const vector<Student> &data) {
    out << "\n"
        << left
        << setw(6)  << "ID"
        << setw(22) << "Name"
        << setw(6)  << "Age"
        << setw(22) << "Major"
        << "GPA"
        << "\n" << string(60, '-') << "\n";

    for (auto &s : data) {
        out << left
            << setw(6)  << s.id
            << setw(22) << s.name
            << setw(6)  << s.age
            << setw(22) << s.major
            << fixed << setprecision(2) << s.gpa
            << "\n";
    }
    out << string(60, '-') << "\n";
}
void displayStudents() {
    if (students.empty()) {
        cout << "No students found.\n";
        return;
    }

//    cout << "===== STUDENT LIST =====";
    printTable(cout, students);
}
void searchByID() {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    for (auto &s : students) {
        if (s.id == id) {
            cout << "Found Student:\n";
            cout << "Name: "  << s.name  << "\n";
            cout << "Age: "   << s.age   << "\n";
            cout << "Major: " << s.major << "\n";
            cout << "GPA: "   << s.gpa   << "\n";
            return;
        }
    }

    cout << "Student not found.\n";
}
string toLowerCase(string str) {
    for (char &c : str) {
        c = tolower(c);
    }
    return str;
}
void searchByName() {
    string keyword;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, keyword);

    keyword = toLowerCase(keyword);
    bool found = false;

    for (auto s : students) {

        string nameLower = toLowerCase(s.name);

        if (nameLower.find(keyword) != string::npos) {

            string name = s.name;

            for(char &c : name){
                if(c == '_')
                    c = ' ';
            }

            cout << "\nID: " << s.id << endl;
            cout << "Name: " << name << endl;
            cout << "Age: " << s.age << endl;
            cout << "Major: " << s.major << endl;
            cout << "GPA: " << s.gpa << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "No matching students found.\n";
    }
}
void updateStudent() {
    int id;
    cout << "Enter ID to update: ";
    cin >> id;
    cin.ignore(); 

    for (auto &s : students) {
        if (s.id == id) {
            cout << "Enter new Name: ";
            getline(cin, s.name);

            cout << "Enter new Age: ";
            cin >> s.age;
            cin.ignore();

            cout << "Enter new Major: ";
            getline(cin, s.major);

            cout << "Enter new GPA: ";
            cin >> s.gpa;

            saveStudents();
            cout << "Student updated successfully.\n";
            return;
        }
    }

    cout << "Student not found.\n";
}
void deleteStudent() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            students.erase(students.begin() + i);
            saveStudents();
            cout << "Student deleted.\n";
            return;
        }
    }

    cout << "Student not found.\n";
}
void gpaStatistics() {
    if (students.empty()) {
        cout << "No student data.\n";
        return;
    }

    float total   = 0;
    float highest = students[0].gpa;
    float lowest  = students[0].gpa;

    for (auto &s : students) {
        total += s.gpa;
        if (s.gpa > highest) highest = s.gpa;
        if (s.gpa < lowest)  lowest  = s.gpa;
    }

    cout << "Average GPA: " << total / students.size() << "\n";
    cout << "Highest GPA: " << highest << "\n";
    cout << "Lowest GPA: "  << lowest  << "\n";
}
void topStudents() {
    if (students.empty()) {
        cout << "No students found.\n";
        return;
    }

    vector<Student> temp = students;

    sort(temp.begin(), temp.end(), [](const Student &a, const Student &b) {
        return a.gpa > b.gpa;
    });

    cout << "\nTop Students:\n";
    for (size_t i = 0; i < temp.size() && i < 3; i++) {
        cout << i + 1 << ". "
             << temp[i].name
             << " | GPA: " << temp[i].gpa << "\n";
    }
}
void sortByGPA() {
    if (students.empty()) {
        cout << "No students to sort.\n";
        return;
    }

    int order;
    cout << "Sort order:\n";
    cout << "  1. Highest to Lowest\n";
    cout << "  2. Lowest to Highest\n";
    cout << "Choose: ";
    cin >> order;

    if (order == 1) {
        sort(students.begin(), students.end(),
             [](const Student &a, const Student &b) { return a.gpa > b.gpa; });
        cout << "\nSorted: Highest to Lowest GPA\n";
    } else if (order == 2) {
        sort(students.begin(), students.end(),
             [](const Student &a, const Student &b) { return a.gpa < b.gpa; });
        cout << "\nSorted: Lowest to Highest GPA\n";
    } else {
        cout << "Invalid option. No sorting applied.\n";
        return;
    }

    printTable(cout, students);
    saveStudents();   // persist the new order
}
void exportReport() {
    if (students.empty()) {
        cout << "No students to export.\n";
        return;
    }

    ofstream file("student_report.txt");

    if (!file) {
        cout << "Error: could not create report file.\n";
        return;
    }

    file << "===== STUDENT REPORT =====";
    printTable(file, students);

    file.close();
    cout << "Report exported to student_report.txt\n";
}
void totalStudents() {
    cout << "Total Students: " << students.size() << endl;
}
int main() {
    loadStudents();

    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search by ID\n";
        cout << "4. Search by Name\n";
        cout << "5. Update Student\n";
        cout << "6. Delete Student\n";
        cout << "7. GPA Statistics\n";
        cout << "8. Top Students\n";
        cout << "9. Export Report\n";
        cout << "10. Sort by GPA\n";
        cout << "11. Total Students\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent();     break;
        case 2: displayStudents();break;
        case 3: searchByID();     break;
        case 4: searchByName();   break;
        case 5: updateStudent();  break;
        case 6: deleteStudent();  break;
        case 7: gpaStatistics();  break;
        case 8: topStudents();    break;
        case 9: exportReport();   break;
        case 10: sortByGPA();     break;
        case 11: totalStudents(); break;
        case 0: 
				 cout << "Program exitted...\n"; break;
        default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}