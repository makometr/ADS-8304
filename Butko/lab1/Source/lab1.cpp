#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void permutation(ofstream &file, vector<string> &arr, int i, int n) {
    if (i == arr.size() - 1) {
        for (int j = 0; j < n; j++) file <<' ';
        for (const string &j : arr) file << j;
        file << '\n';
    } else {
        for (unsigned long long j = i; j < arr.size(); j++) {
            swap(arr[i], arr[j]);
            permutation(file, arr, i + 1, n++);
            swap(arr[i], arr[j]);
        }
    }
}

int vectorCheck(vector<string> &arr) {
    int flag = 0, global_counter_num = 0, global_counter_ch = 0;
    for (auto &i : arr) {
        int counter_num = 0, counter_ch = 0;
        for (char j : i) {
            if (isdigit(j)) counter_num++;
            if (isalpha(j)) counter_ch++;
        }
        if (counter_num == i.length()) global_counter_num++;
        if (counter_ch == i.length()) global_counter_ch++;
    }
    if (global_counter_ch == arr.size() || global_counter_num == arr.size()) flag = 1;
    return flag;
}

void check(vector<string> &arr, ofstream &file) {
    if (arr.empty()) file << "ERROR: Empty array!" << endl;
    else if (vectorCheck(arr)) permutation(file, arr, 0, 0);
    else file << "ERROR: Numbers OR letters only!" << endl;
}

int fromFile() {
    string file_name, log_file;
    cout << " Enter test-file location: " << endl;
    cin >> file_name;
    ifstream file;
    file.open(file_name);
    if (!file.is_open()) {
        cout << "ERROR: File is not open" << endl;
        return 0;
    }
    cout << " Enter where to save results (location with <name>.txt): " << endl;
    cin >> log_file;
    ofstream log(log_file);
    if (!log.is_open()) {
        cout << "ERROR: File is not open" << endl;
        return 0;
    }
    string str, word;
    int i = 1;
    while (!file.eof()) {
        getline(file, str);
        cout << str << endl;
        istringstream iss(str);
        vector<string> array;
        while (iss >> word) array.push_back(word);
        array.erase(array.begin());
        log << "TEST #" << i << endl;
        log << str << endl;
        log << "RESULT:" << endl;
        check(array, log);
        log << endl;
        i++;
    }
    log.close();
    return 0;
}

int fromConsole() {
    string log_file, str, word;
    cout << " Enter your test: " << endl;
    cin.ignore();
    getline(cin, str, '\n');
    cout << " Enter where to save results (location with <name>.txt): " << endl;
    cin >> log_file;
    ofstream log(log_file);
    if (!log.is_open()) {
        cout << "ERROR: File is not open" << endl;
        return 0;
    } else cout << "SAVED";
    istringstream iss(str);
    vector<string> array;
    while (iss >> word) array.push_back(word);
    check(array, log);
    log << endl;
    return 0;
}

void menu() {
    int choice = 0;
    cout << "* * * * SEARCH FOR PERMUTATIONS * * * *" << endl;
    cout << "  What type of test do you want to do?" << endl;
    cout << "        1) from the file" << endl;
    cout << "        2) from the console" << endl;
    cout << "  enter any other number to exit." << endl;
    cout << "* * * * * * * * * * * * * * * * * * * *" << endl;
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "* * * * SEARCH FOR PERMUTATIONS * * * *" << endl;
            cout << "* * * * * * * FROM THE FILE * * * * * *" << endl;
            fromFile();
            break;
        case 2:
            cout << "* * * * SEARCH FOR PERMUTATIONS * * * *" << endl;
            cout << "* * * * *  FROM THE CONSOLE * * * * * *" << endl;
            fromConsole();
            break;
        default:
            cout << "               * EXIT *                 " << endl;
            break;
    }
}

int main() {
    menu();
    return 0;
}
