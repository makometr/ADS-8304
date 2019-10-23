#include <iostream>
#include <memory>
#include <fstream>

struct Node {

    char data;
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;

    Node() {
        data = ' ';
        next = (nullptr);
        prev = (nullptr);
    }
};

class Stack {
    int count;
    std::shared_ptr<Node> lastElement;
public:

    Stack() {
        count = 0;
        lastElement = std::make_shared<Node>();;
    }


    void push(char i) {
        count++;
        lastElement->next = std::make_shared<Node>();
        lastElement->next->data = i;
        lastElement->next->prev = lastElement;
        lastElement = lastElement->next;
    }

    void pop() {
        if (count > 0) {
            count--;
            lastElement = lastElement->prev;
   	    lastElement->next = nullptr;
        }
    }

    int getCountStack() {
        return count;
    }

    char top() {
        return lastElement->data;
    }

};

bool checkExtraneousSigns(std::string &name) {

    for (char j : name) {
        if (j != '{' && j != '}' && j != '[' && j != ']' && j != '(' && j != ')' && j != 'x' && j != 'y' && j != 'z' &&
            j != '+' && j != '-') {
            return false;
        }
    }

    return name.length() != 0;

}


bool checkSubstring(std::string name) {

    int count = name.length();

    for (int i = 0; i < count; i++) {
        if (i % 2 == 0) {
            if (name[i] != 'x') {
                return false;
            }
        } else {
            if (i % 2 == 1) {
                if (name[i] != '+') {
                    return false;
                }
            }
        }
    }
    if (count == 0) {
        return false;
    }
    return count % 2 != 0;

}

bool checkExpression(std::string &name) {

    auto stack = std::make_shared<Stack>();

    for (char i :name) {
        if (i == '(' || i == 'x' || i == '+') {
            stack->push(i);
        } else {

            if (i == ')') {
                std::string newString;
                while (true) {
                    char topElement = stack->top();
                    stack->pop();
                    if (topElement == '(' || stack->getCountStack() == 0) {
                        if (!checkSubstring(newString)) {
                            return false;
                        }
                        stack->push('x');
                        break;
                    }
                    newString += topElement;
                }
            }

        }
    }

    if (stack->getCountStack() != 0) {
        std::string newString;
        while (stack->getCountStack() != 0) {
            char topElement = stack->top();
            newString += topElement;
            stack->pop();
        }

        if (!checkSubstring(newString)) {
            return false;
        }


    }


    return stack->getCountStack() == 0;

}


void mainCheck(std::string &name) {


    if (checkExtraneousSigns(name)) {


        for (char &i : name) {
            if (i == '{' || i == '[') {
                i = '(';
            }
            if (i == '}' || i == ']') {
                i = ')';
            }
            if (i == 'y' || i == 'z') {
                i = 'x';
            }
            if (i == '-') {
                i = '+';
            }
        }

        //std::cout << name << '\n';

        std::cout << checkExpression(name) << '\n';


    } else {
        std::cout << "extraneous signs or empty string" << '\n';
        std::cout << "0" << '\n';
    }

}

int main() {

    int your_choose = 0;

    std::cout << "If you want to enter data from a file, enter \'1\'\n";
    std::cout << "If you want to enter data manually, enter \'2\'\n";

    std::cin >> your_choose;

    if (your_choose == 1) {
        std::ifstream fin;
        fin.open("Tests/test.txt");

        if (fin.is_open()) {
            std::cout << "Reading from file:" << "\n";

            int super_count = 0;

            while (!fin.eof()) {

                super_count++;

                std::string str;
                getline(fin, str);

                std::cout << "test #" << super_count << " \"" + str + "\"" << "\n";
                mainCheck(str);

            }
        } else {
            std::cout << "File not opened";
        }

        fin.close();
    } else {
        if (your_choose == 2) {
            std::cout << "Enter data \n";
            std::string str;
            std::cin >> str;
            mainCheck(str);
        }
    }

    return 0;
}
