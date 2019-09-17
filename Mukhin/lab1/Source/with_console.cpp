#include "iostream"


using namespace std;
char s;
bool rowBrackets();
bool first_error = true;   // error retry check


bool bracket() {
    if (cin.peek() == 'A') {
        cin.get(s);
        if (cin.peek() == '\n')
            return true;
        else if (cin.peek() == '(') {
            cin.get(s);
            if (rowBrackets())
                if (cin.peek() == ')') {
                    cin.get(s);
                    return true;
                }
                else if (first_error) {
                    cout << "Нет закрывающей скобки" << endl;
                    first_error = false;
                }
        }
        else
            return true;
    }
    else if (first_error) {
        cout << "Скобки должны начинаться с A" << endl;
        first_error = false;
    }
    return false;
}


bool rowBrackets() {
    if (bracket()) {
        if (cin.peek() == ';') {
            cin.get(s);
            return rowBrackets();
        }
        return true;
    }
    else if (first_error) {
        cout << "Это не ряд_скобок" << endl;
        first_error = false;
    }
    return false;
}


int main() {
    cout << "Введите строку для проверки: ";
    bool result = bracket();
    cin.peek() == '\n' ? (result ? cout << "True" : cout << "False") : (first_error ? cout << "Лишние символы в конце" << endl << "False" : cout << "False");
    cout << '\n';
    return 0;
}
