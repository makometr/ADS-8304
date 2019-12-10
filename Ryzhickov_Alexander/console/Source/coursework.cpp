#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>

const int right_overweight = 2;
const int left_overweight = -2;

struct Node // структура для представления узлов дерева
{
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

Node *rotateRight(Node *p) // правый поворот вокруг p
{
    Node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

Node *rotateLeft(Node *q) // левый поворот вокруг q
{
    Node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

Node *balance(Node *p) // балансировка узла p
{
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

Node *insert(Node *p, int k) // вставка ключа k в дерево с корнем p
{
    if (!p) return new Node(k);
    if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

Node *findMin(Node *p) // поиск узла с минимальным ключом в дереве p
{
    return p->left ? findMin(p->left) : p;
}

Node *removeMin(Node *p) // удаление узла с минимальным ключом из дерева p
{
    if (p->left == 0)
        return p->right;
    p->left = removeMin(p->left);
    return balance(p);
}

Node *remove(Node *p, int k) // удаление ключа k из дерева p
{
    if (!p) return 0;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else //  k == p->key
    {
        Node *q = p->left;
        Node *r = p->right;
        delete p;
        if (!r) return q;
        Node *min = findMin(r);
        min->right = removeMin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void printAVLTree(Node *p) {
    std::cout << "(";
    std::cout << p->key;
    if (p->left) {
        //std::cout << "L";
        printAVLTree(p->left);
    }
    if (p->right) {
        //std::cout << "R";
        printAVLTree(p->right);
    }
    std::cout << ")";
}

std::string createString(Node *p) {
    std::string myString;
    myString += "(";
    myString += std::to_string(p->key);
    if (p->left) {
        myString += createString(p->left);
    }
    if (p->right) {
        myString += createString(p->right);
    }
    myString += ")";
    return myString;
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
    ofs << p->key;

    if (p->right) {
        printAVLTree3(p->right, ofs);
    }

}

void deleteTree(Node *p) {
    if (p->left) {
        deleteTree(p->left);
    }
    if (p->right) {
        deleteTree(p->right);
    }
    delete p;
}

int chooseComplexity() {
    int complexity = 0;

    std::cout << "Choose the difficulty\n";
    std::cout << "If you want to choose a simple difficulty - enter 1\n";
    std::cout << "If you want to choose a medium difficulty - enter 2\n";
    std::cout << "If you want to choose a high difficulty   - enter 3\n";
    std::cout << "If you want to choose a custom difficulty - enter 4\n";


    std::cin >> complexity;

    if ((complexity != 1) && (complexity != 2) && (complexity != 3) && (complexity != 4)) {
        std::cout << "You entered incorrect complexity\n";
        return 0;
    }

    return complexity;


}


int countOptions() {
    int countOptions = 0;
    std::cout << "Enter the number of options (from 1 to 30)\n";

    std::cin >> countOptions;
    if (!(countOptions > 0 && countOptions <= 30)) {
        std::cout << "You entered incorrect options\n";
        return 0;
    }

    return countOptions;
}

int random(int min, int max) {
    return min + rand() % (max - min);
}


void createRandomArray(int *arrayNumbers, int *arrayOptions, int sizeArray) {
    for (int j = 0; j < sizeArray; ++j) {

        if (arrayNumbers[arrayOptions[j] - 1] != 0) {
            arrayNumbers[arrayOptions[j] - 1] = 0;
        } else {
            int min = 0;
            for (int i = 0; i < sizeArray; ++i) {
                if (arrayNumbers[i] != 0) {
                    min = arrayNumbers[i];
                    break;
                }
            }

            arrayOptions[j] = min;
            arrayNumbers[min - 1] = 0;

        }
    }
}

void printTask(int *arrayOptions, int *arrayDeleteElements, int sizeArray, int countDeleteElements, std::ofstream &ofs) {
    std::cout << "      Insert: ";
    ofs << "      Insert: ";
    for (int i = 0; i < sizeArray; ++i) {
        std::cout << arrayOptions[i] << " ";
        ofs << arrayOptions[i] << " ";
    }
    std::cout << "\n      Delete: ";
    ofs << "\n      Delete: ";
    for (int j = 0; j < countDeleteElements; ++j) {
        std::cout << arrayDeleteElements[j] << " ";
        ofs << arrayDeleteElements[j] << " ";
    }
    std::cout << "\n";
    ofs << "\n";
}

void createVariant(int complexity, std::istream &fin, bool isReadFromUser, std::ofstream &ofs) {
    int sizeArray = 0;
    int countDeleteElements = 0;

    if (complexity == 1) {
        sizeArray = 5;
        countDeleteElements = 1;
    }
    if (complexity == 2) {
        sizeArray = 10;
        countDeleteElements = 2;
    }
    if (complexity == 3) {
        sizeArray = 15;
        countDeleteElements = 3;
    }

    if (complexity == 4) {
        if (isReadFromUser) {
            std::cout << "Enter count elements:\n";
        }
        fin >> sizeArray;
        if (sizeArray > 0 && sizeArray <= 20) {
            countDeleteElements = sizeArray;
        } else {
            if(!isReadFromUser){
                return;
            }
            std::cout << "You entered inccorect count elements\n";
            std::cout << "Count elements = 20\n";
            sizeArray = 10;
            countDeleteElements = sizeArray;
        }
    }

    int *arrayNumbers = new int[sizeArray];
    int *arrayOptions = new int[sizeArray];
    int *arrayDeleteElements = new int[countDeleteElements];

    if (complexity != 4) {
        for (int i = 0; i < sizeArray; ++i) {
            arrayNumbers[i] = i + 1;
            arrayOptions[i] = random(1, sizeArray + 1);
        }

        createRandomArray(arrayNumbers, arrayOptions, sizeArray);

        for (int i = 0; i < countDeleteElements; ++i) {
            arrayDeleteElements[i] = arrayOptions[i];
            arrayDeleteElements[i] = arrayOptions[arrayDeleteElements[i] - 1];
        }
    } else {
        if (isReadFromUser) {
            std::cout << "Enter elements:\n";
        }
        for (int i = 0; i < sizeArray; ++i) {
            fin >> arrayOptions[i];
        }
        if (isReadFromUser) {
            std::cout << "Enter count delete elements: \n";
        }
        fin >> countDeleteElements;


        if (!(countDeleteElements > 0 && countDeleteElements <= sizeArray)) {
            std::cout << "You entered inccorect delete count elements\n";
            std::cout << "Count delete elements = 0\n";
            countDeleteElements = 0;
        }

        if (isReadFromUser) {
            std::cout << "Enter delete elements:\n";
        }

        for (int i = 0; i < countDeleteElements; ++i) {
            fin >> arrayDeleteElements[i];
        }
    }

    printTask(arrayOptions, arrayDeleteElements, sizeArray, countDeleteElements,ofs);

    auto *avlTree = new Node(arrayOptions[0]);
    for (int j = 1; j < sizeArray; ++j) {
        avlTree = insert(avlTree, arrayOptions[j]);
    }

    for (int k = 0; k < countDeleteElements; ++k) {
        avlTree = remove(avlTree, arrayDeleteElements[k]);
    }

    std::cout << "      Answer: ";
    ofs << "      Answer: ";
    if (avlTree != 0) {
        std::cout << createString(avlTree);
        ofs << createString(avlTree);
    } else {
        std::cout << "Empty tree";
        ofs << "Empty tree";
    }
    std::cout << "\n";
    ofs << "\n";
    if (avlTree != 0) {
        deleteTree(avlTree);
    }
    delete[] arrayNumbers;
    delete[] arrayOptions;
    delete[] arrayDeleteElements;

}

int main() {

    srand(time(nullptr));
    std::ofstream ofs("output.txt", std::ios_base::app);


    std::cout << "Welcome to the verification program\n"
                 "The program creates variants of different and answers\n\n";

    std::cout << "If you want to see tests entre 'test', otherwise just any characters\n";

    std::string test;

    std::cin >> test;

    if (test == "test") {
        std::ifstream fin;
        fin.open("Tests/test.txt");

        if (fin.is_open()) {
            std::cout << "Reading from file:" << "\n";

            int super_count = 0;

            while (!fin.eof()) {

                std::cout << "Option number " << super_count + 1 << "\n";
                ofs << "Option number " << super_count + 1 << "\n";
                createVariant(4, fin, false,ofs);
                super_count++;

            }
        } else {
            std::cout << "File not opened";
        }

        fin.close();
    }

    int count = 0;
    int complexity = 0;
    while (true) {
        complexity = chooseComplexity();
        if (complexity == 0) {
            break;
        }
        if (complexity != 4) {
            count = countOptions();
            if (count == 0) {
                break;
            }
        } else {
            count = 1;
        }
        for (int i = 0; i < count; ++i) {
            std::cout << "Option number " << i + 1 << "\n";
            ofs << "Option number " << i + 1 << "\n";
            createVariant(complexity, std::cin, true,ofs);
        }
        char choice;
        std::cout << "If you want to finish, enter 'Y/N'\n";
        std::cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            break;
        }
    }

    ofs.close();

    return 0;
}


