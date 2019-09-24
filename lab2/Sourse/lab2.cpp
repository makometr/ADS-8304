#include <iostream>
#include <string>
#include <fstream>

using namespace std;
typedef struct List;
typedef struct Node;

typedef struct Node {
    string my_data;
    bool isAtom;
    Node *next;
    List *list;
};

typedef struct List {
    Node *head;
};


bool isOrImplication(string myString, int num);

bool isAnd(string myString, int count);

bool isNot(string myString, int count);

bool isArgument(string myString, int *count, Node *node);

bool isEquenceArguments(string myString, int *count, Node *node);

bool isLogicExpression(string myString, int *count, Node *node);

bool isOrImplication(string myString, int num) {
    if (myString[num] == 'O' && myString[num + 1] == 'R' || myString[num] == '-' && myString[num + 1] == '>') {
        return true;
    }
    return false;
}

bool isAnd(string myString, int num) {
    if (myString[num] == 'A' && myString[num + 1] == 'N' && myString[num + 2] == 'D') {
        return true;
    }
    return false;
}

bool isNot(string myString, int num) {
    if (myString[num] == 'N' && myString[num + 1] == 'O' && myString[num + 2] == 'T') {
        return true;
    }
    return false;
}

bool isArgument(string myString, int *count, Node *node) {
    int num = *count;
    if (isalpha(myString[num]) && islower(myString[num])) {
        *count = *count + 1;
        string aaa = {myString[num]};

        Node *my_node = node;
        Node *newNode = new Node;
        newNode->my_data = aaa;
        newNode->isAtom = true;
        newNode->next = nullptr;
        my_node->next = newNode;

        return true;
    }
    if (myString[num] == '(' && isNot(myString, num + 1)) {

        if (isalpha(myString[num + 4]) && islower(myString[num + 4])) {

            if (myString[num + 5] == ')') {
                *count = *count + 6;
                string aaa = {myString[num], myString[num + 1], myString[num + 2], myString[num + 3], myString[num + 4],
                              myString[num + 5]};

                Node *my_node = node;
                Node *newNode = new Node;
                newNode->my_data = aaa;
                newNode->isAtom = true;
                newNode->next = nullptr;
                my_node->next = newNode;

                return true;
            }

        }

    }

    Node *newNode = new Node;
    newNode->isAtom = false;
    newNode->my_data = '#';
    newNode->list = new List;
    newNode->list->head = new Node;
    newNode->list->head->next = nullptr;
    newNode->list->head->isAtom = true;
    newNode->next = nullptr;

    if (isLogicExpression(myString, count, newNode->list->head)) {
        Node *my_node = node;
        my_node->next = newNode;
        return true;
    }
    return false;
}

bool isEquenceArguments(string myString, int *count, Node *node) {
    int countArguments = 0;
    Node *tmp = node;
    while (isArgument(myString, count, tmp)) {
        tmp = tmp->next;
        countArguments++;
    }
    return countArguments > 0;
}

bool isLogicExpression(string myString, int *count, Node *node) {
    int num = *count;
    if (myString[num] == '(') {
        if (isOrImplication(myString, num + 1)) {
            *count = *count + 3;
            if(myString[num+1]=='O') {
                node->my_data = "OR";
            } else{
                node->my_data = "->";
            }
            if (isEquenceArguments(myString, count, node)) {
                int s = *count;
                if (myString[s] == ')') {
                    *count = *count + 1;
                    return true;
                }
            }
        }
        if (isAnd(myString, num + 1)) {
            *count = *count + 4;
            node->my_data = "AND";
            if (isEquenceArguments(myString, count, node)) {
                int s = *count;
                if (myString[s] == ')') {
                    *count = *count + 1;
                    return true;
                }
            }
        }
    }
    return false;
}

string getString(List *list) {

    string my_string = "";

    if (list->head != nullptr) {
        Node *my_node = list->head;
        while (my_node->next != nullptr) {
            if (my_node->isAtom) {
                my_string += my_node->my_data;
                my_node = my_node->next;
            } else {
                my_string += "(";
                my_string += getString(my_node->list);
                my_string += ")";
                my_node = my_node->next;
            }
        }
        if (my_node->isAtom) {
            string abc = my_node->my_data;
            my_string += abc;
        } else {
            my_string += "(";
            my_string += getString(my_node->list);
            my_string += ")";
        }
    }

    return my_string;
}

void deleteAll(List *list) {

    if (list->head != nullptr) {
        Node *my_node = list->head;
        while (my_node->next != nullptr) {
            if (my_node->isAtom) {
                Node *tmp = my_node->next;
                delete(my_node);
                my_node = tmp;
            } else {
                getString(my_node->list);
                Node *tmp = my_node->next;
                delete(my_node);
                my_node = tmp;
            }
        }
        if (my_node->isAtom) {
            delete(my_node);
        } else {
            getString(my_node->list);
        }
    }

}

int check(string name) {

    List *list = new List;
    list->head = new Node;
    list->head->isAtom = true;
    list->head->next = nullptr;


    int c = 0;

    if(isLogicExpression(name, &c, list->head)){
        if("("+getString(list)+")"==name){
            cout << "OK"<<"\n";
        } else{
            cout << "NOT OK"<<"\n";
        }
    } else{
        cout << "NOT OK"<<"\n";
    }

    deleteAll(list);
    delete (list->head);
    delete (list);

    return 0;
}


int main() {

    int your_choose = 0;

    cout << "If you want to enter data from a file, enter \'1\'\n";
    cout << "If you want to enter data manually, enter \'2\'\n";

    cin >> your_choose;

    if (your_choose==1) {
        ifstream fin;
        fin.open("C:\\Users\\Alex\\Desktop\\test2.txt");

        if (fin.is_open()) {
            cout << "Reading from file:" << "\n";

            int super_count = 0;

            while (!fin.eof()) {

                super_count++;

                string str;
                getline(fin, str);

                cout << "test #" << super_count << " \"" + str + "\"" << "\n";
                check(str);

            }
        } else {
            cout << "File not opened";
        }

        fin.close();
    } else{
        if(your_choose==2){
            cout << "Enter data \n";
            string str;
            cin >> str;
            check(str);
        }
    }

    return 0;
}
