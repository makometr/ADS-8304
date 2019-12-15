#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::cin;
using std::cerr;

std::string decodingFanoShannon(std::string &encodedText, std::map<std::string, std::string> &codeTable);

std::string readText(std::istream& in);

std::string readText(std::ifstream& in);

std::map<std::string, std::string> readTable(std::istream& in);

std::map<std::string, std::string> readTable(std::ifstream& in);

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "");

	if (argc < 3) {
		std::map<std::string, std::string> codeTable;
		std::string encodedText;
		std::string result;

		if (argc == 2) {
			std::string fileName = argv[1];
			result += "Read encoded text from file " + fileName + "\n";

			std::ifstream inputFile(fileName, std::ios::in);
			codeTable = readTable(inputFile);
			encodedText = readText(inputFile);
			inputFile.close();
		}
		else {
			cout << "Enter a character code table. \nIn the format: symbol_code\n";
			codeTable = readTable(cin);
	

			cout << "Enter encoded text:";
			encodedText = readText(cin);
		}
		
		result += "\nInput code table:\n";
		std::map<std::string, std::string>::iterator it = codeTable.begin(); 
  		while (it != codeTable.end()) { 
    			result += it->second + "- " + it->first + "\n"; 
    			++it; 
  		}
		
		result += "Input encoded text:\n" + encodedText + "\n";
		result += "Decoded text:\n" + decodingFanoShannon(encodedText, codeTable) + "\n\n\n";

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


std::string readText(std::istream& in) {
	std::string result;
	getline(in, result);

	return result;
}

std::map<std::string, std::string> readTable(std::istream& in) {
	std::string oneLineStr;
	std::map<std::string, std::string> codeTable;
	std::string symbol;
	std::string code;

	getline(in, oneLineStr);
	while (oneLineStr != "") {
		symbol = oneLineStr.substr(0, 1);
		code = oneLineStr.substr(2);
		codeTable.insert(std::make_pair(code, symbol));
		getline(in, oneLineStr);
	}
	
	return codeTable;
}


std::string readText(std::ifstream& in) {
	if (!in.is_open()) {
		cerr << "Error: incorrect file name!\n";
		return "";
	}

	std::string result;
	getline(in, result);

	return result;
}

std::map<std::string, std::string> readTable(std::ifstream& in) {
	std::string oneLineStr;
	std::map<std::string, std::string> codeTable;
	std::string symbol;
	std::string code;

	getline(in, oneLineStr);
	while (oneLineStr != "") {
		symbol = oneLineStr.substr(0, 1);
		code = oneLineStr.substr(2);
		codeTable.insert(std::make_pair(code, symbol));
		getline(in, oneLineStr);
	}

	return codeTable;
}

std::string decodingFanoShannon(std::string &encodedText, std::map<std::string, std::string> &codeTable) {
	std::string code;
	std::string decodedText;

	for (auto elem : encodedText) {
		code += elem; 
		if (codeTable.count(code)) {
			decodedText += codeTable[code];
			code = "";
		}
	}

	return decodedText;
}

