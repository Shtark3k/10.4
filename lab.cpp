#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <limits>
using namespace std;

int getMenuChoice() {
    int c;
    while (true) {
        cout << "1.Sort by brand\n2.Append average mileage\n3.Append unique brand count\n0.Exit\nChoice: ";
        if (cin >> c && c >= 0 && c <= 3) {
            cin.ignore();
            return c;
        }
        cout << "Error\n";
        cin.clear();
        cin.ignore();
    }
}
void initializeFile(const string& fn) {
    ifstream check(fn);
    if (check.good()) {
        check.close();
        return;
    }
    ofstream out(fn);
    out << "Toyota 20000 150000\n";
    out << "Ford 18000 120000\n";
    out << "BMW 35000 80000\n";
    out.close();
}
string promptFileName(const string& p) {
    cout << p;
    string fn;
    getline(cin, fn);
    return fn;
}
string getFileName(const string& p) {
    cout << p;
    string fn;
    getline(cin, fn);
    return fn;
}

int countLines(const string& fn) {
    ifstream in(fn);
    int n = 0;
    string line;
    while (getline(in, line)) n++;
    return n;
}

string selectMinLine(const string& fn) {
    ifstream in(fn);
    string minLine, line, brand;
    bool first = true;
    while (getline(in, line)) {
        string b = line.substr(0, line.find(' '));
        if (first || b < brand) {
            brand = b; minLine = line; first = false;
        }
    }
    return minLine;
}

void removeFirstMatch(const string& fn, const string& target) {
    ifstream in(fn);
    ofstream out("tmp.txt");
    string line;
    bool removed = false;
    while (getline(in, line)) {
        if (!removed && line == target) { removed = true; continue; }
        out << line << "\n";
    }
    in.close(); out.close();
    remove(fn.c_str());
    rename("tmp.txt", fn.c_str());
}

void sortByBrand(const string& fn) {
    int n = countLines(fn);
    ofstream out("sorted.txt");
    for (int i = 0; i < n; i++) {
        string m = selectMinLine(fn);
        out << m << "\n";
        removeFirstMatch(fn, m);
    }
    out.close();
    remove(fn.c_str());
    rename("sorted.txt", fn.c_str());
}

double computeAverageMileage(const string& fn) {
    ifstream in(fn);
    string brand;
    double cost, m;
    double sum = 0;
    int cnt = 0;
    while (in >> brand >> cost >> m) {
        sum += m; cnt++;
    }
    return cnt ? sum / cnt : 0;
}

void appendAverageMileage(const string& fn, double avg) {
    ifstream in(fn);
    ofstream out("tmp.txt");
    string line;
    while (getline(in, line)) {
        out << line << " " << avg << "\n";
    }
    in.close(); out.close();
    remove(fn.c_str());
    rename("tmp.txt", fn.c_str());
}

int countUniqueBrands(const string& fn) {
    ifstream in(fn);
    set<string> s;
    string brand;
    double cost, m;
    while (in >> brand >> cost >> m) s.insert(brand);
    return s.size();
}

void appendUniqueCount(const string& fn, int cnt) {
    ofstream out("tmp.txt", ios::app);
    out << cnt << "\n";
    out.close();
    ifstream in("tmp.txt"); ofstream orig(fn);
    string line;
    while (getline(in, line)) orig << line << "\n";
    in.close(); orig.close();
    remove("tmp.txt");
}
int main() {
    string fn = promptFileName("Enter data file name: ");
    initializeFile(fn);
    bool run = true;
    while (run) {
        switch (getMenuChoice()) {
        case 1:
            sortByBrand(fn);
            cout << "Done\n";
            break;
        case 2: {
            double avg = computeAverageMileage(fn);
            appendAverageMileage(fn, avg);
            cout << "Done\n";
            break;
        }
        case 3: {
            int u = countUniqueBrands(fn);
            appendUniqueCount(fn, u);
            cout << "Done\n";
            break;
        }
        case 0:
            run = false;
            break;
        }
    }
    return 0;
}
