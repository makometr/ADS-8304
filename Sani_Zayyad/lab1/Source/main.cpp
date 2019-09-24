#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//declaration of Functions
void ProceedInput();
string ReadFromConsole();
void ReadFromFile(string filename);
bool checkValidity(string str);
string notFunction(string str);
bool expression(string str, int pointer);
void calculate(string input);

//this is the starting point of the progran
// it asks user to select input option and uses the input to calculate the logic
void ProceedInput()
{
    //dialog
    cout << "> Lab work #1" << endl;
    cout << "> Choose your input" << endl;
    cout << "> 0 - from console" << endl;
    cout << "> 1 - from file default file (input.txt)" << endl;
    cout << "> 2 - from custom file" << endl;
    cout << "> Any other key to Exit!" << endl;

    int command = 0;
    //command input
    cin >> command;
    cin.ignore();

    //default test file path
    string FilePath = "/Users/sanizayyad/Documents/input.txt";
    string input;

    // I used switch statement to trigger the action base on the dialog
    switch (command)
    {
    case 0:
        cout << "> Your input: ";
        input = ReadFromConsole();
        calculate(input);
        break;
    case 1:
        ReadFromFile(FilePath);
        break;
    case 2:
        cout << "> FilePath: ";
        cin >> FilePath;
        ReadFromFile(FilePath);
        break;
    default:
        cout << "GOODBYE!";
    }
}
// this function basically just get input from the console
string ReadFromConsole()
{
    string input;
    getline(cin, input);
    return input;
}
//this function iterates the lines of the file and trigger calculate on every line as input
void ReadFromFile(string filename)
{
    ifstream file;
    file.open(filename);

    if (file.is_open())
    {
        cout << "Reading from file:"
             << "\n";

        int super_count = 0;

        while (!file.eof())
        {
            super_count++;
            string str;
            getline(file, str);
            cout << "test #" << super_count << " \"" + str + "\""
                 << "\n";
            calculate(str);
        }
    }
    else
    {
        cout << "File not opened";
    }
    file.close();
}
// checking if the brackets are balanced
bool checkValidity(string str)
{
    int balanceBracket = 0;
    int i = 0;
    for (i; i < str.size(); i++)
    {
        if (str[i] == ')')
            balanceBracket--;
        else if (str[i] == '(')
            balanceBracket++;
    }
    if (balanceBracket == 0)
        return true;
    return false;
}
//the main recursive function to check expression
bool expression(string str, int pos)
{
    if (str == "TRUE")
        return true;
    if (str == "FALSE")
        return false;
    if (str == "NOT(TRUE)")
        return false;
    if (str == "NOT(FALSE)")
        return true;

    if (str[pos] == '(')
    {
        pos++;
        bool a, b;
        string exp_1, exp_2, sign;

        //I splitted the expression three which means for every expression there's
        //expression1 Sign expression2//

        //checking the main demarcation between two expression
        //for example (TRUE AND FALSE) , here the first space after TRUE is our demarcation
        int breakspace = 0;
        int bracket = 0;
        for (breakspace = pos; breakspace < str.size(); breakspace++)
        {
            if (str[breakspace] == ' ')
            {
                if (bracket == 0)
                    break;
            }
            if (str[breakspace] == ')')
                bracket--;
            else if (str[breakspace] == '(')
                bracket++;
        }
        int tmp = breakspace - 1;

        //////expression 1
        exp_1 = str.substr(pos, tmp);
        //if there's a Not statement in expression1
        //we call notFunction to calculate the NOT(logic)
        if (exp_1.find("NOT") != string::npos)
        {
            exp_1 = notFunction(exp_1);
        }
        //////SIGN
        string tmpStr = str.substr(tmp + 2);
        int tmp_2 = tmpStr.find(" ");
        sign = tmpStr.substr(0, tmp_2);
        ////expression 2
        exp_2 = tmpStr.substr(tmp_2 + 1, tmpStr.size() - tmp_2 - 2);
        if (exp_2.find("NOT") != string::npos)
        {
            exp_2 = notFunction(exp_2);
        }

        //recursive on expression 1
        a = expression(exp_1, 0);
        // recursive on expression 2
        b = expression(exp_2, 0);

        // the  we return the outcome
        if (sign == "AND")
            return (a && b);
        else
            return (a || b);
    }
}
//this returns the negation of a logic.
string notFunction(string str)
{
    int tmp = str.find("NOT");
    string tmp_expression = str.substr(tmp + 3, str.size());
    int tmp_closing = tmp_expression.find(")");
    tmp_expression = tmp_expression.substr(0, tmp_closing);
    bool before;

    if (tmp_expression.find(" ") != string::npos)
    {
        before = expression(tmp_expression, 0);
    }
    else
    {
        tmp_expression = tmp_expression.substr(1, tmp_closing - 1);
        before = expression(tmp_expression, 0);
    }

    string notExp = before == true ? "NOT(TRUE)" : "NOT(FALSE)";
    return notExp;
}
void calculate(string input)
{
    if (checkValidity(input) && !input.empty())
    {
        if (expression(input, 0) == true)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;
    }
    else
        cout << "\t ERROR!!!" << endl;
}

int main()
{
    //start
    ProceedInput();

    return 0;
}
