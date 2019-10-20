#include "Header.h"

//здесь мог быть нерелевантный комментарий
bool checkMapStringFormCorrection(std::string const& checkString)
{
	std::regex pattern("\\((\\(\\w [01]+\\))+\\)");
	return std::regex_match(checkString, pattern);
}


bool checkCodeCorrection(std::string const& checkString)
{
	return std::find_if(checkString.begin(), checkString.end(), [](char c) {return c != '0' && c != '1'; }) == checkString.end();
}

ReturnCode checkDataCorrection(std::string const& code, std::string const& charactersCodes)
{
	bool resultCodeCorrectionCheck = checkCodeCorrection(code);
	if (!resultCodeCorrectionCheck)
		return ReturnCode::IncorrectSymbols;

	bool mapStringFormCorrection = checkMapStringFormCorrection(charactersCodes);
	if (!mapStringFormCorrection)
		return ReturnCode::IncorrectMapStringForm;

	return ReturnCode::Correct;
}

void readFileData(StringVector& fileData, std::ifstream& in)
{
	std::string currentFileString;
	while (std::getline(in, currentFileString))
	{
		if (currentFileString.back() == '\r')
			currentFileString.erase(currentFileString.end() - 1);
		fileData.push_back(currentFileString);
	}
}

ReturnCode formHaffmanTree(std::string const& code, char character, std::shared_ptr<Node>& head)
{
	std::shared_ptr<Node> headCopy(head);

	for (char element : code)
	{
		if (headCopy->character != 0)
			return ReturnCode::BadPreffixForm;

		if (element == '0')
		{
			if (headCopy->left == nullptr)
			{
				auto newElement = std::make_shared<Node>();
				headCopy->left = newElement;
			}

			headCopy = headCopy->left;
			
		}
		else
		{
			if (headCopy->right == nullptr)
			{
				auto newElement = std::make_shared<Node>();
				headCopy->right = newElement;
			}
			headCopy = headCopy->right;
		}
	}
	if (headCopy->character != 0)
		return ReturnCode::BadPreffixForm;

	headCopy->character = character;

	return ReturnCode::Correct;
}

ReturnCode dictCreation(CharactersCodeMap& dict, std::string& parsedString)
{
	std::regex pattern("\\(\\w [01]+\\)");
	std::smatch match;

	while (std::regex_search(parsedString, match, pattern) != 0)
	{
		std::string matchedBrackets(match.str());

		std::string characterCode(matchedBrackets.find(" ") + 1 + matchedBrackets.begin(), matchedBrackets.find(")") + matchedBrackets.begin());
		char character = matchedBrackets[1];
		if (dict.find(character) != dict.end())
			return ReturnCode::CollisionError;

		dict[character] = characterCode;

		parsedString.erase(match.position() + parsedString.begin(), match.length() + match.position() + parsedString.begin());
	}

	return ReturnCode::Correct;
}

//Возвращаемое функции зависит от того стоит ли продолжать поиск или нет
bool findCodeInTree(std::shared_ptr<Node>& head, std::string const& code, char& character)
{

	if (code.back() == '1')
	{
		if (head->right == nullptr)
			return false;

		else
		{
			if (head->right->character != 0)
				character = head->right->character;
			else
				head = head->right;
			return true;
		}
	}
	else
	{
		if (head->left == nullptr)
			return false;
		else
		{
			if (head->left->character != 0)
				character = head->left->character;
			else
				head = head->left;
			return true;
		}

	}
}

DecodePair decode(std::string const& code, std::shared_ptr<Node> const& head)
{
	std::string currentCheckedCode;
	std::string decodeResult;

	std::shared_ptr<Node> startPoint(head);

	for (char element : code)
	{
		currentCheckedCode += element;

		char character = 0;
		bool findResult = findCodeInTree(startPoint, currentCheckedCode, character);
		if (findResult == false)
			return DecodePair("", false);

		if (character != 0)
		{
			decodeResult += character;
			startPoint = head;
			currentCheckedCode.clear();
		}
	}

	return DecodePair(decodeResult, true);
}

int main(int argc, char** argv)
{
	if (argc > 2)
	{
		std::ifstream in(argv[1]);
		if (!in.is_open())
		{
			std::cout << "Incorrect input file\n";
			return 0;
		}

		std::ofstream out(argv[2]);
		if (!out.is_open())
		{
			std::cout << "Incorrect output file\n";
			return 0;
		}

		StringVector fileData;
		readFileData(fileData, in);

		if (fileData.size() < 2 || fileData.size() % 2 != 0)
		{
			std::cout << "File should consist of an even number of lines (0 is not even)\n";
			return 0;
		}

		for (auto it = fileData.begin(); it != fileData.end(); it += 2)
		{
			std::string checkCode(*it);
			std::string checkMapStringForm(*std::next(it));

			ReturnCode checkResult = checkDataCorrection(checkCode, checkMapStringForm);
			if (checkResult == ReturnCode::IncorrectSymbols)
			{
				out << "Code contains incorrect symbols\n";
				continue;
			}
			if (checkResult == ReturnCode::IncorrectMapStringForm)
			{
				out << "Your map-string is incorrect\n";
				continue;
			}

			CharactersCodeMap dict;
			ReturnCode creationResult =	dictCreation(dict, checkMapStringForm);
			if (creationResult == ReturnCode::CollisionError)
			{
				out << "Collision\n";
				continue;
			}

			auto head = std::make_shared<Node>();
			bool isGoodPrefixForm = true;

			for (auto i : dict)
			{
				//second - код символа, first - сам символ 
				//Я считаю это нужным комментарием т.к. из-за непонятных имен полей first и second нам было запрещено пользоваться std::pair
				ReturnCode formResult = formHaffmanTree(i.second, i.first, head);
				if (formResult == ReturnCode::BadPreffixForm)
				{
					isGoodPrefixForm = false;
					break;
				}
			}

			if (isGoodPrefixForm == false)
			{
				out << "Bad prefix form\n";
				continue;
			}

			DecodePair result = decode(checkCode, head);
			if (result.decodeResult == false)
			{
				out << "Your code is incorrect\n";
				continue;
			}

			out << result.value << "\n";
		}
	}

	return 0;
}
