#include <iomanip>
#include <ios>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT36.h"


// DANH SÁCH SINH VIÊN - 3
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT36.txt";
    ifstream file(filename); // Mở file để đọc
    if (!file) {
        cerr << "Khong the mo file input " << filename << endl;
        return 1;
    }

    string line;
    if (!getline(file, line)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const int N = parse_int(line);
    if (N < 1 || N > 50) {
        cerr << "N phai lon hon 0 va nho hon 50" << endl;
        return 2;
    }
    vector<Student> students;
    for (int i = 0; i < N; i++) {
        string fullname, dateStr, clazz, gpaMarkStr;
        if (!getline(file, fullname)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (!getline(file, clazz)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (!getline(file, dateStr)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (!getline(file, gpaMarkStr)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        try {
            Student student(fullname, clazz, dateStr, gpaMarkStr);
            students.push_back(student);
        } catch (const exception &ex) {
            cerr << ex.what() << endl;
            return 2;
        }
    }

    file.close();
    // Sort by GPA descending
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.gpaMark > b.gpaMark;
    });
    for (const Student& student : students) {
        cout << student << endl;
    }
    return 0;
}

Student::Student(const std::string &fullname, const std::string &clazz, const std::string &dateStr,
                 const std::string &gpaMarkStr) {
    using namespace std;
    ++counter;
    std::ostringstream oss;
    oss << "B20DCCN" << setw(3) << setfill('0') << counter;
    this->code = oss.str();
    this->fullname = normalize_and_validate_name(fullname);
    this->clazz = validate_ptit_clazz(clazz);
    this->dateOfBirth = parse_date(dateStr);
    this->gpaMark = parse_float(gpaMarkStr);
    if (this->gpaMark < 0) {
        throw invalid_argument("Diem mon 1 khong hop le");
    }
}

std::ostream &operator<<(std::ostream &os, const Student &student) {
    using namespace std;
    os
            << student.code << " "
            << student.fullname << " "
            << print_date(student.dateOfBirth) << " "
            << student.clazz << " "
            << fixed << setprecision(2) << student.gpaMark;
    return os;
}
