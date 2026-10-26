
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Student {
private:
    int rollNumber;
    string name;
    vector<double> marks;
    double total;
    double percentage;
    string grade;
    bool passed;

    void calculateResult() {
        total = 0;
        passed = true;

        for (double mark : marks) {
            total += mark;

            if (mark < 35) {
                passed = false;
            }
        }

        percentage = total / marks.size();

        if (!passed) {
            grade = "F";
        } else if (percentage >= 90) {
            grade = "A+";
        } else if (percentage >= 80) {
            grade = "A";
        } else if (percentage >= 70) {
            grade = "B";
        } else if (percentage >= 60) {
            grade = "C";
        } else if (percentage >= 50) {
            grade = "D";
        } else {
            grade = "E";
        }
    }

public:
    Student(int roll, string studentName,
            vector<double> subjectMarks) {
        rollNumber = roll;
        name = studentName;
        marks = subjectMarks;
        calculateResult();
    }

    int getRollNumber() const {
        return rollNumber;
    }

    void displayResult() const {
        cout << fixed << setprecision(2);

        cout << "\n======= STUDENT RESULT =======\n";
        cout << "Roll Number : " << rollNumber << endl;
        cout << "Name        : " << name << endl;

        for (int i = 0; i < (int)marks.size(); i++) {
            cout << "Subject " << i + 1
                 << " Marks : " << marks[i] << "/100\n";
        }

        cout << "Total Marks : " << total
             << "/" << marks.size() * 100 << endl;
        cout << "Percentage  : " << percentage << "%\n";
        cout << "Grade       : " << grade << endl;
        cout << "Result      : "
             << (passed ? "PASS" : "FAIL") << endl;
        cout << "==============================\n";
    }
};

class ExaminationSystem {
private:
    vector<Student> students;
    int numberOfSubjects;

public:
    ExaminationSystem(int subjects) {
        numberOfSubjects = subjects;
    }

    void addStudent() {
        int roll;
        string name;
        vector<double> marks;

        cout << "Enter roll number: ";
        cin >> roll;

        for (const Student& s : students) {
            if (s.getRollNumber() == roll) {
                cout << "Roll number already exists!\n";
                return;
            }
        }

        cout << "Enter student name: ";
        cin >> ws;
        getline(cin, name);

        for (int i = 0; i < numberOfSubjects; i++) {
            double mark;

            cout << "Enter marks for subject "
                 << i + 1 << " (0-100): ";
            cin >> mark;

            if (mark < 0 || mark > 100) {
                cout << "Invalid marks! Registration cancelled.\n";
                return;
            }

            marks.push_back(mark);
        }

        students.emplace_back(roll, name, marks);
        cout << "Student result added successfully!\n";
    }

    void displayAllResults() const {
        if (students.empty()) {
            cout << "No examination records available!\n";
            return;
        }

        for (const Student& s : students) {
            s.displayResult();
        }
    }

    void searchStudent() const {
        int roll;

        cout << "Enter roll number to search: ";
        cin >> roll;

        for (const Student& s : students) {
            if (s.getRollNumber() == roll) {
                s.displayResult();
                return;
            }
        }

        cout << "Student record not found!\n";
    }
};

int main() {
    ExaminationSystem exam(5);
    int choice;

    do {
        cout << "\n===== EXAMINATION MANAGEMENT =====\n";
        cout << "1. Add Student Result\n";
        cout << "2. Display All Results\n";
        cout << "3. Search Student Result\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            exam.addStudent();
            break;

        case 2:
            exam.displayAllResults();
            break;

        case 3:
            exam.searchStudent();
            break;

        case 4:
            cout << "Exiting examination system...\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
