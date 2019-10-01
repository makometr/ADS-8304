#include <iostream>
#include <string>
#include <fstream>
#include <memory>

struct Node;

struct Node {
    char data;
    bool isAtom;
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> list;
};

bool checkWord(std::string name);

std::string getUpdateString(std::string name, std::string removeSubstring, std::string newSubstring);

std::shared_ptr<Node> create();

void createList(std::string name, int *count, std::shared_ptr<Node>node);

bool counting(std::shared_ptr<Node>tmp);

int getCountNode(std::shared_ptr<Node>node);

bool checkList(std::shared_ptr<Node>node);

bool isAllLower(std::string name);


bool checkWord(std::string name) {

    if (name.size() <= 2) {
        return false;
    }

    if (!(name[0] == '(' && name[name.size() - 1] == ')')) {
        return false;
    }

    int count = 0;

    for (char i : name) {
        if (i == '(') {
            count++;
        } else {
            if (i == ')') {
                count--;
            } else {
                if (!isalpha(i) && i != '-' && i != '>') {
                    return false;
                }
            }

        }
    }

    return count == 0;
}

std::string getUpdateString(std::string name, std::string removeSubstring, std::string newSubstring) {

    size_t index = 0;
    while (true) {
        index = name.find(removeSubstring, index);
        if (index == std::string::npos) break;
        name.replace(index, removeSubstring.size(), newSubstring);
        index += newSubstring.size();
    }

    return name;

}

void createList(std::string name, int *count, std::shared_ptr<Node> node) {

    std::shared_ptr<Node> tmp = node;

    while (name[*count] != ')') {
        if ((isalpha(name[*count]) && islower(name[*count])) || isdigit(name[*count])) {
            tmp->next = create();
            tmp->next->data = name[*count];
            tmp->next->isAtom = true;
        } else {
            if (name[*count] == '(') {
                tmp->next = create();
                tmp->next->list = create();

                *count = *count + 1;
                createList(name, count, tmp->next->list);

            }
        }

        *count = *count + 1;
        tmp = tmp->next;
    }
}

std::shared_ptr<Node> create() {
    Node *newNode = new Node;
    newNode->next = (nullptr);
    newNode->list = (nullptr);
    newNode->isAtom = false;
    newNode->data = ' ';
    std::shared_ptr<Node> sharedPtr (newNode);
    return sharedPtr;
}

void printList(std::shared_ptr<Node>node) {
    std::shared_ptr<Node>tmp = node;
    while (tmp != nullptr) {
        if (tmp->isAtom) {
            std::cout << tmp->data;
        } else {
            std::cout << '(';
            printList(tmp->list->next);
            std::cout << ')';
        }
        tmp = tmp->next;
    }
}

int getCountNode(std::shared_ptr<Node>node) {
    std::shared_ptr<Node>tmp = node;
    int count = 0;
    while (tmp != nullptr) {
        count++;
        tmp = tmp->next;
    }

    return count - 1;
}

bool counting(std::shared_ptr<Node>tmp) {
    if (isdigit(tmp->data)) {
        switch (tmp->data) {
            case '1':
                if (getCountNode(tmp) >= 1) {
                    return true;
                }
                break;
            case '2':
                if (getCountNode(tmp) >= 1) {
                    return true;
                }
                break;
            case '3':
                if (getCountNode(tmp) == 2) {
                    return true;
                }
                break;
            case '4':
                if (getCountNode(tmp) == 1) {
                    return true;
                }
                break;
        }
    }
    return false;
}

bool checkList(std::shared_ptr<Node>node) {
    std::shared_ptr<Node>tmp = node;

    if (isdigit(tmp->data)) {
        if (!counting(tmp)) {
            return false;
        };
    } else {
        return false;
    }

    tmp = tmp->next;

    while (tmp != nullptr) {
        if (!tmp->isAtom) {
            if (!checkList(tmp->list->next)) {
                return false;
            };
        } else {
            if (isdigit(tmp->data)) {
                return false;
            }
        }
        tmp = tmp->next;
    }
    return true;
}

bool isAllLower(std::string name) {
    for (char i : name) {
        if (isalpha(i)) {
            if (!islower(i)) {
                return false;
            }
        }
    }
    return true;
}

void mainCheck(std::string name) {

    if (checkWord(name)) {
        name = getUpdateString(name, "AND", "1");
        name = getUpdateString(name, "OR", "2");
        name = getUpdateString(name, "->", "3");
        name = getUpdateString(name, "NOT", "4");

        if (isAllLower(name)) {


            int count = 1;

            std::shared_ptr<Node> list (create());

            createList(name, &count, list);

            std::cout << checkList(list->next);
            std::cout << '\n';
        } else {
            std::cout << "0 not ok Unnecessary сapital letters in the expression";
            std::cout << '\n';
        }

    } else {
        std::cout << "0 not ok The expression is wrong";
        std::cout << '\n';
    }


}


int main() {

    int your_choose = 0;

    std::cout << "If you want to enter data from a file, enter \'1\'\n";
    std::cout << "If you want to enter data manually, enter \'2\'\n";

    std::cin >> your_choose;

    if (your_choose == 1) {
        std::ifstream fin;
        fin.open("test.txt");

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
