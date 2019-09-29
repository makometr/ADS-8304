#include <iostream>


char s;
bool rowBrackets();
bool first_error = true;   // error retry check


bool bracket() {
    if (std::cin.peek() == 'A') {
        std::cin.get(s);
        if (std::cin.peek() == '\n')
            return true;
        else if (std::cin.peek() == '(') {
            std::cin.get(s);
            if (rowBrackets())
                if (std::cin.peek() == ')') {
                    std::cin.get(s);
                    return true;
                }
                else if (first_error) {
                    std::cout << "Нет закрывающей скобки" << std::endl;
                    first_error = false;
                }
        }
        else
            return true;
    }
    else if (first_error) {
        std::cout << "Скобки должны начинаться с A" << std::endl;
        first_error = false;
    }
    return false;
}


bool rowBrackets() {
    if (bracket()) {
        if (std::cin.peek() == ';') {
            std::cin.get(s);
            return rowBrackets();
        }
        return true;
    }
    else if (first_error) {
        std::cout << "Это не ряд_скобок" << std::endl;
        first_error = false;
    }
    return false;
}


int main() {
    std::cout << "Введите строку для проверки: ";
    bool result = bracket();
    std::cin.peek() == '\n' ? (result ? std::cout << "True" : std::cout << "False") : (first_error ? std::cout << "Лишние символы в конце" << std::endl << "False" : std::cout << "False");
    std::cout << '\n';
    return 0;
}
