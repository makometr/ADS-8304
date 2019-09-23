#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

static bool isDebug = true;

string f(string_view str, unsigned indent = 0)
{
    auto getIndent = [indent] {
        string indentStr;
        for (unsigned i = 0; i < indent; i++)
            indentStr += "│ ";
        return indentStr;
    };
    auto showResult = [getIndent](string_view result) {
        cout << getIndent() << "└ = " << result << endl;
    };

    if (isDebug)
        cout << getIndent() << "f(" << str << "):" << endl;

    auto p = str.find('/');

    if (p == string::npos) {
        if (isDebug) {
            cout << getIndent() << "│ " << str << endl;
            showResult(str);
        }
        return string(str);
    }
    else {
        auto left = str.substr(0, p);
        auto right = str.substr(p + 1);
        auto result = f(right, indent + 1) + string(left);
        if (isDebug) {
            cout << getIndent() << "│ +" << endl;
            cout << getIndent() << "│ " << left << endl;
            showResult(result);
        }
        return result;
    }
}

void launchTests() {
    auto oldIsDebug = isDebug;
    isDebug = false;
    ifstream fin("Tests/test");
    if (fin.is_open()) {
        string in, out;
        int i = 1;
        while (true) {
            getline(fin, in);
            getline(fin, out);
            if (fin.eof())
                break;
            cout << "Test " << i++ << " is ";
            if (f(in) == out)
                cout << "ok";
            else
                cout << "FAILED";
            cout << endl;
        }
        fin.close();
    }
    else {
        cerr << "The test file is not found.";
    }
    isDebug = oldIsDebug;
}

int main(int argc, char** argv)
{
    auto showHelp = []() {
        cout << "Enter the string as a command-line argument." << endl;
        cout << "Use --test to launch the tests." << endl;
    };

    if (argc > 1) {
        if (strcmp(argv[1], "--test") == 0)
            launchTests();
        else {
            auto result = f(argv[1]);
            cout << "Result: " << result << endl;
        }
    }
    else {
        showHelp();
    }
    return 0;
}
