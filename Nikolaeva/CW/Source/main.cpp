#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "fanoshannontree.h"
#include "huffmantree.h"
#include "decode.h"
#include <random>
#include <time.h>

using std::cout;
using std::cin;
using std::cerr;

std::string readTask(std::istream& in, size_t& numberOfOptions, size_t& lengthOfText, bool& encode,
                     bool& decode, bool& fanoShannon, bool& huffman);

std::string readTask(std::ifstream& in, size_t& numberOfOptions, size_t& lengthOfText, bool& encode,
                     bool& decode, bool& fanoShannon, bool& huffman);

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    if (argc < 3) {
        std::map<std::string, std::string> codeTable;
        std::string task;
        std::string result;

        size_t numberOfOptions;
        size_t lengthOfText;
        bool encode = true;
        bool decode = true;
        bool fanoShannon = true;
        bool huffman = true;
        bool corrEnt = true;

        if (argc == 2) {
            std::string fileName = argv[1];
            result += "Read encoded text from file " + fileName + "\n";

            std::ifstream inputFile(fileName, std::ios::in);
            task = readTask(inputFile, numberOfOptions, lengthOfText, encode, decode,
                            fanoShannon, huffman);

            inputFile.close();
        }
        else {
            task = readTask(cin, numberOfOptions, lengthOfText, encode, decode, fanoShannon, huffman);
        }


        if (numberOfOptions == SIZE_MAX || lengthOfText == SIZE_MAX || (encode && decode) || !(fanoShannon ^ huffman)){
            task = "Sorry. Incorrect entering..\n";
            corrEnt = false;
        }

        result += task;

        if (corrEnt) {
            std::string randomStr;
            std::string encodedText;
            std::string decodedText;
            srand(time(NULL));
            for (size_t i = 0; i < numberOfOptions; ++i) {
                result += "OPTION NUMBER " + std::to_string(i + 1) + ":\n";
                randomStr = "";
                for (size_t j = 0; j < lengthOfText; j++){
                    randomStr += 'a' + rand() % ('z' - 'a');
                }
                if (encode){
                    if (fanoShannon){
                        FanoShannonTree tree;
                        result += "Encode text using the Fano-Shannon algorithm. The result should contain a table of character codes and encoded text.\n";
                        result += "Text:" + randomStr + "\n\nAnswer(Option " + std::to_string(i + 1) + ")" + ":\nencoded text:" +
                                tree.encode(randomStr) + "\ncharacter codes:\n";
                        result += tree.createCodeSymbols(randomStr) + "\n\n";
                    } else {
                        HuffmanTree tree;
                        result += "Encode text using the Huffman algorithm. The result should contain a table of character codes and encoded text.\n";
                        result += "Text:" + randomStr + "\n\nAnswer" + "(Option " + std::to_string(i + 1) + ")" + ":\nencoded text:" +
                                tree.encode(randomStr) + "\ncharacter codes:\n";
                        result += tree.createCodeSymbols(randomStr) + "\n\n";
                    }
                }
                else {
                    if (fanoShannon){
                        FanoShannonTree tree;
                        encodedText = tree.encode(randomStr);
                        decodedText = decode::decode(&tree, encodedText);
                        result += "Decode text using the FanoShannon algorithm. The result should contain a table of character codes and decoded text.\n";
                        result += "encoded text:" + encodedText + "\nencoding tree:\n";
                        tree.printTree(result);
                        result += "\nAnswer(Option " + std::to_string(i + 1) + ")" + ":\ndecoded text:" + decodedText  + "\ncharacter codes\n";
                        result += tree.createCodeSymbols(randomStr) + "\n\n";
                    } else {
                        HuffmanTree tree;
                        encodedText = tree.encode(randomStr);
                        decodedText = decode::decode(&tree, encodedText);
                        result += "Decode text using the Huffman algorithm. The result should contain a table of character codes and decoded text.\n";
                        result += "encoded text:" + encodedText + "\nencoding tree:\n";
                        tree.printTree(result);
                        result += "\nAnswer(Option " + std::to_string(i + 1) + ")" + ":\ndecoded text:" + decodedText  + "\ncharacter codes\n";
                        result += tree.createCodeSymbols(randomStr) + "\n\n";
                    }
                }
            }
        }
        cout << result;

        std::ofstream resultFile("result.txt", std::ios::app);
        resultFile << result;
        resultFile.close();

    }
    else {
        cerr << "Error: incorect console's arguments\n";
    }

    return 0;
}


std::string readTask(std::istream& in, size_t& numberOfOptions, size_t& lengthOfText,bool& encode,
                     bool& decode, bool& fanoShannon, bool& huffman) {
    std::string oneLineStr;
    std::string task;

    cout << "Enter the number of options to generate:\n";
    std::cin >> numberOfOptions;
    std::cin.ignore(32767, '\n');

    task += "\nParameters:\nNumber of options:";
    task += std::to_string(numberOfOptions);
    task += "\n";

    cout << "Enter the length of text to generate:\n";
    std::cin >> lengthOfText;
    std::cin.ignore(32767, '\n');


    task += "Length of text:";
    task += std::to_string(numberOfOptions);
    task += "\n";

    cout << "Choose the type of jobs: enter 'e' to encode or 'd' to decode\n";
    getline(in, oneLineStr);

    if (oneLineStr == "e") {
        encode = true;
        decode = false;
        task += "encode ";
    }

    if (oneLineStr == "d"){
        encode = false;
        decode = true;
        task += "decode ";
    }

    cout << "Choose the type of encode/decode: enter 'F' to FanoShannon or 'H' to Huffman\n";
    getline(in, oneLineStr);

    if (oneLineStr == "F") {
        fanoShannon = true;
        huffman = false;
        task += "FanoShannon\n\n";
    }
    
    if (oneLineStr == "H"){
        fanoShannon = false;
        huffman = true;
        task += "Huffman\n\n";
    }

    return task;
}

std::string readTask(std::ifstream& in, size_t& numberOfOptions, size_t& lengthOfText, bool& encode,
                     bool& decode, bool& fanoShannon, bool& huffman) {
    std::string oneLineStr;
    std::string task;

    getline(in, oneLineStr);
    numberOfOptions = atoi(oneLineStr.c_str());
    task += "\nParameters:\nNumber of options:";
    task += std::to_string(numberOfOptions);
    task += "\n";

    getline(in, oneLineStr);
    lengthOfText = atoi(oneLineStr.c_str());
    task += "Length of text:";
    task += std::to_string(numberOfOptions);
    task += "\n\n";

    getline(in, oneLineStr);

    if (oneLineStr == "e") {
        encode = true;
        decode = false;
        task += "encode ";
    }

    if (oneLineStr == "d"){
        encode = false;
        decode = true;
        task += "decode ";
    }

    getline(in, oneLineStr);
    
    if (oneLineStr == "F") {
        fanoShannon = true;
        huffman = false;
        task += "FanoShannon\n\n";
    }
    
    if (oneLineStr == "H"){
        fanoShannon = false;
        huffman = true;
        task += "Huffman\n\n";
    }


    return task;
}


