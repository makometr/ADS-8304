#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool isItLogicalExpression(string basicString, int *count);

bool isTrue(string basicString, int *count);

bool isFalse(string basicString, int *count);

bool isLetter(string basicString, int *count);

bool isOperandWithNot(string basicString, int *count);


bool isOperand(string basicString, int *count);

bool isOperationWithOperands(string basicString, int *count);

bool isOperands(string basicString, int *count);

bool isOperands(string basicString, int *count);

bool check(string basicString, int *count);

void work(string name);


int main() {
    ifstream fin;
    fin.open("Tests/test.txt");

    if (fin.is_open()) {
        cout << "Reading from file:" << "\n";

        int super_count = 0;

        while (!fin.eof()) {

            super_count++;

            string str;
            getline(fin, str);

            cout << "test #" << super_count << " \"" + str + "\"" << "\n";
            work(str);

        }
    } else {
        cout << "File not opened";
    }

    fin.close();

    return 0;
}

void work(string name) {
    int count = 0;
    if (isItLogicalExpression(name, &count)) {
        if (count == name.size()) {

            cout << "OK" << " ";
            cout << count << " ";
            cout << name.size() << "\n";

        } else {
            cout << "Not OK" << " ";
            cout << count << " ";
            cout << name.size() << "\n";
        }
    } else {
        cout << "Not OK (from logical)" << "\n";
    }
}

bool isItLogicalExpression(string name, int *count) {

    int num = *count;

    if (isTrue(name, count)) {
        return true;
    } else {
        if (isFalse(name, count)) {
            return true;
        } else {

            if (isOperandWithNot(name, count)) {
                return true;
            } else {

                if (isOperationWithOperands(name, count)) {
                    return true;
                } else {
                    *count = num;
                    if (isLetter(name, count)) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool isTrue(string basicString, int *count) {
    int num = *count;
    if (basicString[num] == 'T' && basicString[num + 1] == 'R' && basicString[num + 2] == 'U' &&
        basicString[num + 3] == 'E') {
        *count = *count + 4;
        return true;
    } else {
        return false;
    }
}

bool isFalse(string basicString, int *count) {
    int num = *count;
    if (basicString[num] == 'F' && basicString[num + 1] == 'A' && basicString[num + 2] == 'L' &&
        basicString[num + 3] == 'S' && basicString[num + 4] == 'E') {
        *count = *count + 5;
        return true;
    } else {
        return false;
    }
}

bool isLetter(string basicString, int *count) {
    int num = *count;
    if (isalpha(basicString[num]) && check(basicString, count)) {
        *count = *count + 1;
        return true;
    } else {
        return false;
    }
}

bool isOperandWithNot(string basicString, int *count) {
    string aaa2 = basicString;
    string aaa3 = basicString;
    string aaa4 = aaa3.replace(*count, 1, "x");

    int num = *count;
    if (basicString[num] == 'N' && basicString[num + 1] == 'O' && basicString[num + 2] == 'T' &&
        basicString[num + 3] == '(') {
        *count = *count + 4;
        if (isOperand(basicString, count)) {
            int s = *count;
            if (basicString[s] == ')') {
                *count = *count + 1;
                return true;
            } else {
                return false;
            }
        }
    } else {
        return false;
    }
}


bool isOperand(string basicString, int *count) {
    if (isItLogicalExpression(basicString, count)) {
        return true;
    }

    return false;
}

bool isOperationWithOperands(string basicString, int *count) {
    int num = *count;
    if (basicString[num] == 'O' && basicString[num + 1] == 'R' && basicString[num + 2] == '(') {
        *count = *count + 3;
        if (isOperands(basicString, count)) {
            int s = *count;
            if (basicString[s] == ')') {
                *count = *count + 1;
                return true;
            }
        }
    }

    if (basicString[num] == 'A' && basicString[num + 1] == 'N' && basicString[num + 2] == 'D' &&
        basicString[num + 3] == '(') {
        *count = *count + 4;
        if (isOperands(basicString, count)) {
            int s = *count;
            if (basicString[s] == ')') {
                *count = *count + 1;
                return true;
            }
        }
    }

    return false;
}

bool isOperands(string basicString, int *count) {
    int num = *count;

    if (isOperand(basicString, count)) {
        int s = *count;

        if (basicString[s] != ',') {
            return true;
        } else {
            *count = num;
        }
    }

    if (isOperand(basicString, count)) {
        int s = *count;

        if (basicString[s] == ',') {
            *count = *count + 1;
            if (isOperands(basicString, count)) {
                return true;
            }
        } else {
            *count = num;
        }

    }
    return false;
}

bool check(string basicString, int *count) {
    int num = *count;

    if (basicString[num] == 'T' && basicString[num + 1] == 'R' && basicString[num + 2] == 'U' &&
        basicString[num + 3] == 'E') {
        return false;
    }

    if (basicString[num] == 'F' && basicString[num + 1] == 'A' && basicString[num + 2] == 'L' &&
        basicString[num + 3] == 'S' && basicString[num + 4] == 'E') {
        return false;
    }

    if (basicString[num] == 'N' && basicString[num + 1] == 'O' && basicString[num + 2] == 'T') {
        return false;
    }

    if (basicString[num] == 'A' && basicString[num + 1] == 'N' && basicString[num + 2] == 'D') {
        return false;
    }

    if (basicString[num] == 'O' && basicString[num + 1] == 'R') {
        return false;
    }

    return true;
}
