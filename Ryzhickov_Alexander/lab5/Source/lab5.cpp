
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

const int right_overweight = 2;
const int left_overweight = -2;
const int indent = 0;

struct Node {
    int key;
    unsigned char height;
    Node *left;
    Node *right;

    Node(int k) {
        key = k;
        left = right = 0;
        height = 1;
    }
};

unsigned char height(Node *p) {
    return p ? p->height : 0;
}

int bFactor(Node *p) {
    return height(p->right) - height(p->left);
}

void fixHeight(Node *p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

Node *rotateRight(Node *p) {
    Node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

Node *rotateLeft(Node *q) {
    Node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

Node *balance(Node *p) {
    fixHeight(p);
    if (bFactor(p) == right_overweight) {
        if (bFactor(p->right) < 0)
            p->right = rotateRight(p->right);
        return rotateLeft(p);
    }
    if (bFactor(p) == left_overweight) {
        if (bFactor(p->left) > 0)
            p->left = rotateLeft(p->left);
        return rotateRight(p);
    }
    return p; // балансировка не нужна
}

Node *insert(Node *p, int k) {
    if (!p) return new Node(k);
    if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

void printAVLTree(Node *p) {
    std::cout << "(";
    std::cout << p->key;
    if (p->left) {
        std::cout << "L";
        printAVLTree(p->left);
    }
    if (p->right) {
        std::cout << "R";
        printAVLTree(p->right);
    }
    std::cout << ")";
}

void printAVLTree2(Node *p, int maxHeight) {

    for (int i = 0; i < maxHeight; ++i) {
        std::cout << " ";
    }

    std::cout << p->key;
    std::cout << "\n";

    if (p->left) {
        printAVLTree2(p->left, maxHeight + 1);
    }
    if (p->right) {
        printAVLTree2(p->right, maxHeight + 1);
    }

}

void printAVLTree3(Node *p, std::ofstream &ofs) {

    if (p->left) {
        printAVLTree3(p->left, ofs);
    }
    ofs << p->key ;

    if (p->right) {
        printAVLTree3(p->right,  ofs);
    }

}

void deleteTree(Node *p){
    if (p->left) {
        deleteTree(p->left);
    }
    if (p->right) {
        deleteTree(p->right);
    }
    delete p;
}

bool checkExpression(std::string &name, int &my_length) {
    int length = name.length();
    for (int j = 0; j < length; ++j) {
        if (!isdigit(name[j]) && name[j] != ',') {
            return false;
        }
        if (name[j] == ',') {
            name[j] = ' ';
            (my_length)++;
        }
    }

    return true;
}


void mainCheck(std::string &name) {

    int my_lenght = 0;

    if (checkExpression(name, my_lenght)) {
        std::istringstream iss;
        std::string strvalues = name;
        iss.str(strvalues);

        int val2;
        iss >> val2;
        auto *myTree = new Node(val2);
        for (int i = 0; i < my_lenght; i++) {
            int val;
            iss >> val;
            myTree = insert(myTree, val);
        }
        printAVLTree(myTree);
        std::cout << '\n';
        myTree = balance(myTree);

        printAVLTree2(myTree, indent);

        std::ofstream ofs("output.txt", std::ios_base::app);
        printAVLTree3(myTree,ofs);
        ofs << '\n';
        ofs.close();

        deleteTree(myTree);
    } else {
        std::cout << "Unwanted characters\n";
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


