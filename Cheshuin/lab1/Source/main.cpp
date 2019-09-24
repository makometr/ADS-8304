#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

enum types{
    CONST_EXPR,
    SERIES_OF_NUMBER,
    OPERATION_SIGN,
    DIGIT,
    SPACE,
};

int dialog();
void cliHandler(int argc, char** argv);
int readCommand();
bool parse(types type, string& str);
bool typeIsEq(char chr, types type);
string typeToStr(types type);

int main(int argc, char** argv) {

    if(argc > 1){
        cliHandler(argc, argv);
    }
    else{
        dialog();
    }

    return 0;
}

bool parse(types type, string& str){
    static unsigned int position = 0;

    static int deep = 0;
    static int instanceCount = 0;
    int instanceNum = 0;

    if(deep == 0){
        position = 0;
        instanceCount = 0;
    }

    deep += 1;
    instanceCount += 1;

    instanceNum = instanceCount;

    cout << "Instance " << instanceNum << " Deep - "
         << deep << " Expected type - " << typeToStr(type) << endl;

    if(position == str.length()){
        cout << "Instance " << instanceNum << " Deep - " << deep << " Expected type - "
             << typeToStr(type) << " failed - end of string" << endl;
        return false;
    }

    int isCorrect = false;

    switch(type){
        case CONST_EXPR:{
            if(parse(SERIES_OF_NUMBER, str)){
                if(position + 1 >= str.length()){
                    isCorrect = true;
                    break;
                }
                position += 1;

                if(parse(OPERATION_SIGN, str)){
                    isCorrect = parse(CONST_EXPR, str);
                }
            }
            break;
        }

        case SERIES_OF_NUMBER:{
            if(typeIsEq(str[position], DIGIT)){
                if(position + 1 == str.length()){
                    isCorrect = true;
                    break;
                }
                if(typeIsEq(str[position + 1], SPACE)){
                    if(typeIsEq(str[position + 2], DIGIT)){
                        position += 2;
                        isCorrect = parse(SERIES_OF_NUMBER, str);
                    }
                    else{
                        isCorrect = true;
                    }
                }
            }
            break;
        }

        case OPERATION_SIGN:{
            if(typeIsEq(str[position], SPACE)){
                if(typeIsEq(str[position + 1], OPERATION_SIGN)){
                    if(typeIsEq(str[position + 2], SPACE)){
                        position += 3;
                        isCorrect = true;
                    }
                }
            }
            break;
        }

        default:{
            deep -= 1;

            cout << "Instance " << instanceNum << " Deep - " << deep << " Expected type - "
                 << typeToStr(type) << endl << " failed - incorrect expected type" << endl;

            return false;
        }
    }

    cout << "Instance " << instanceNum << " Deep - " << deep << " Expected type - "
         << typeToStr(type);

    if(isCorrect){
        cout << " - OK" << endl;
    }
    else{
        cout << " - failed - real type not equal with expected" << endl;
    }

    deep -= 1;

    return isCorrect;
}

bool typeIsEq(char chr, types type){
    if(chr == ' ' && type == SPACE){
        return true;
    }
    else if(isdigit(chr) && type == DIGIT){
        return true;
    }
    else if((chr == '+' || chr == '-' || chr == '*') && type == OPERATION_SIGN){
        return true;
    }
    else{
        return false;
    }
}

string typeToStr(types type){
    switch (type) {
        case CONST_EXPR:
            return "Const expression";

        case SERIES_OF_NUMBER:
            return "Series of number";

        case OPERATION_SIGN:
            return "Operation sign";

        case DIGIT:
            return "Number";

        case SPACE:
            return "Space";

    }

    return "Unknown type";
}

int dialog(){
    int command = 0;
    string expression;
    string filePath;
    ifstream inputFile;
    ofstream resultFile;

    while(true){
        cout << "1. Validate expression from console." << endl;
        cout << "2. Validate all expressions from file." << endl;
        cout << "3. Exit." << endl;
        cout << "Enter command." << endl;

        command = readCommand();

        switch(command){
            case 1:
                cout << "Enter expression." << endl;

                cin.clear();
                getline(cin, expression);

                cout << endl << "Expression to validate: " << expression << endl;
                if(parse(CONST_EXPR, expression) == 0){
                    cout << "Result - not const expression." << endl << endl;
                }
                else{
                    cout << "Result - const expression." << endl << endl;
                }
            break;

            case 2:
                cout << "Enter path of file." << endl;

                cin.clear();
                getline(cin, filePath);

                inputFile.open(filePath);

                if(inputFile.is_open()){
                    resultFile.open(filePath + " - result");

                    cout << "Opened file - " << filePath << endl;

                    while(getline(inputFile, expression)){
                        cout << endl << "Expression to validate: " << expression << endl;
                        resultFile << expression;

                        if(parse(CONST_EXPR, expression)){
                            cout << "Result - const expression." << endl << endl;
                            resultFile << " - OK" << endl;
                        }
                        else{
                            cout << "Result - not const expression." << endl << endl;
                            resultFile << " - FAILED" << endl;
                        }
                    }

                    inputFile.close();
                    resultFile.close();
                }
                else{
                    cout << "Cant't open file - " << filePath << ". Try again." << endl << endl;
                }
            break;

            case 3:
                return 0;
        }
    }
}

int readCommand(){
    string command;

    while(true){

        cin.clear();
        getline(cin, command);

        if(command == "1"){
            return 1;
        }
        else if (command == "2") {
            return 2;
        }
        else if (command == "3") {
            return 3;
        }
        else{
            cout << command << " - is incorrect command. Try again." << endl << endl;
        }
    }

}

void cliHandler(int argc, char** argv){
    string expression;
    string filePath;
    ifstream inputFile;
    ofstream resultFile;

    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "--file") == 0){
            i += 1;

            filePath = argv[i];

            inputFile.open(filePath);

            if(inputFile.is_open()){
                resultFile.open(filePath + " - result");

                cout << "Opened file - " << filePath << endl;

                while(getline(inputFile, expression)){
                    cout << endl << "Expression to validate: " << expression << endl;
                    resultFile << expression;

                    if(parse(CONST_EXPR, expression)){
                        cout << "Result - const expression." << endl << endl;
                        resultFile << " - OK" << endl;
                    }
                    else{
                        cout << "Result - not const expression." << endl << endl;
                        resultFile << " - FAILED" << endl;
                    }
                }

                inputFile.close();
                resultFile.close();
            }
            else{
                cout << "Cant't open file - " << filePath << ". Try again." << endl << endl;
            }
        }
    }
}
