#include <fstream>
#include <cstring>
#include "iostream"


using namespace std;
char s;
ifstream in("/home/mukhamux/CLionProjects/algoritms/lab1/Mukhin/lab1/Tests/tests.txt");
ofstream out("/home/mukhamux/CLionProjects/algoritms/lab1/Mukhin/lab1/Tests/out.txt");
bool rowBrackets();
bool first_error = true;


bool bracket() {
    if (in.peek() == 'A') {
        in.get(s);
        if (in.peek() == EOF || in.peek() == '\n')
            return true;
        else if (in.peek() == '(') {
            in.get(s);
            if (rowBrackets())
                if (in.peek() == ')') {
                    in.get(s);
                    return true;
                }
                else if (first_error) {
                    out << "Нет закрывающей скобки" << endl;
                    first_error = false;
                }
        }
        else
            return true;
    }
    else if (first_error) {
        out << "Скобки должны начинаться с A" << endl;
        first_error = false;
    }
    return false;
}


bool rowBrackets() {
    if (bracket()) {
        if (in.peek() == ';') {
            in.get(s);
            return rowBrackets();
        }
        return true;
    }
    else if (first_error) {
        out << "Это не ряд_скобок" << endl;
        first_error = false;
    }
    return false;
}


bool check_EL(bool result) {
    if (in.peek() == EOF || in.peek() == '\n') {
        in.get(s);
        if (result)
            out << "True";
        else
            out << "False";
    }
    else {
        if (first_error)
            out << "Лишние символы в конце" << endl << "False";
        else
            out << "False";
    }
    out << "\n\n";
    first_error = true;
    while (s != '\n' && !in.eof())
        in.get(s);
}


int main() {
    char* k = (char*)calloc(150, sizeof(char));
    while (!in.eof()) {
        in.getline(k, 151);
        out << "Данные файла: " << k << endl;
        if (strlen(k) == 0 && in.peek() == EOF) {    // if last line is \n
            in.get(s);
            check_EL(false);
            break;
        }
        if (in.eof())                                // if last line without \n
            in.seekg(-strlen(k), ios::cur);
        else                                         //no last line
            in.seekg(-strlen(k) - 1, ios::cur);
        bool result = bracket();
        check_EL(result);
    }
    in.close();
    out.close();
    free(k);
    cout << "Done, output in out.txt.\n";
    return 0;
}
