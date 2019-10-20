#include "BinaryTree.h"

int getVariableType(std::string const& checkString)
{
	TransformPair<char> charTransform = fromString<char>(checkString);
	if (charTransform.transformResult)
		return CharType;

	TransformPair<int> intTranform = fromString<int>(checkString);
	if (intTranform.transformResult)
		return IntType;

	TransformPair<double> doubleTransform = fromString<double>(checkString);
	if (doubleTransform.transformResult)
		return DoubleType;

	return StringType;
}

void determineTreeValuesType(std::string& currentCheckTree, std::ostream& out)
{
	//запись значения хранящегося в главном узле, 1 - пропуск (
	size_t mainNodeNameStart = 1;
	std::string variableStringValue;
	while (currentCheckTree[mainNodeNameStart] != '(' && currentCheckTree[mainNodeNameStart] != ')' &&	mainNodeNameStart < currentCheckTree.size())
	{
		variableStringValue += currentCheckTree[mainNodeNameStart];
		mainNodeNameStart++;
	}
	//

	//если дерево состоит из одного узла, то в нем не может быть повторяющихся узлов
	if (currentCheckTree[mainNodeNameStart] == ')')
	{
		out << "NO" << std::endl;
		return;
	}
	//

	int variableType = getVariableType(variableStringValue);

	int checkResult = -1;
	switch (variableType)
	{
	case 1:
		checkResult = treeCheck(treeCreation<int>(currentCheckTree));
		break;
	case 2:
		checkResult = treeCheck(treeCreation<double>(currentCheckTree));
		break;
	case 3:
		checkResult = treeCheck(treeCreation<char>(currentCheckTree));
		break;
	case 4:
		checkResult = treeCheck(treeCreation<std::string>(currentCheckTree));
		break;
	}
	if (checkResult == -1)
	{
		out << "Your binary tree is incorrect!\n";
		return;
	}

	out << ((checkResult) ? "YES\n" : "NO\n");
}

bool checkBracketsPlacement(std::string const& checkString)
{
	if (*checkString.begin() != '(' || *(checkString.end() - 1) != ')')
		return false;

	size_t openBracketCnt = 0;
	size_t closeBracketCnt = 0;

	for (char symb : checkString)
	{
		if (symb == '(')
			openBracketCnt++;

		if (symb == ')')
			closeBracketCnt++;

		if (closeBracketCnt > openBracketCnt)
			return false;
	}

	return closeBracketCnt == openBracketCnt;
}

std::string extractBracketsValue(std::string const& stringTreeForm, size_t* stringIndexPointer)
{
	//error - переменная необходимая для обработки данного случая (...(...)...) она позволяет получить значение 
	//лежащее точно от уже найденной открывающей до корректной закрывающей скобки
	size_t tmp_ind = *stringIndexPointer;
	int error = 0;
	std::string bracketsValue;

	while (1)
	{
		//запись очередного символа
		bracketsValue += stringTreeForm[tmp_ind];
		tmp_ind++;

		if (stringTreeForm[tmp_ind] == '(')
			error++;
		if (stringTreeForm[tmp_ind] == ')')
			error--;
		if (error < 0)
			break;
	}

	//запись ')'
	bracketsValue += stringTreeForm[tmp_ind];

	//перенос индекса за выражение в скобках дял считывания второго аргумента
	*stringIndexPointer = tmp_ind + 1;
	return bracketsValue;
}

int main(int argc, char** argv)
{
	if (argc > 2)
	{
		std::ifstream in(argv[1]);
		std::ofstream out(argv[2]);

		if (!in.is_open())
		{
			std::cout << "Hmmm, maybe you will give me input file that exist? Goodbye\n";
			return 0;
		}

		if (!out.is_open())
		{
			std::cout << "Hmmm, maybe you will give me output file that exist? Goodbye\n";
			return 0;
		}

		std::string currentCheckTree;
		while (std::getline(in, currentCheckTree))
		{
			if (!currentCheckTree.empty() && *(currentCheckTree.end() - 1) == '\r')
				currentCheckTree.erase(currentCheckTree.end() - 1);

			//удаление пробелов
			currentCheckTree.erase(std::remove_if(currentCheckTree.begin(), currentCheckTree.end(), [](char c) {return c == ' '; }), currentCheckTree.end());

			if (!checkBracketsPlacement(currentCheckTree))
			{
				out << "Hmm, uncorect brackets statement\n";
				continue;
			}

			determineTreeValuesType(currentCheckTree, out);
		}

		return 0;
	}

	std::string currentCheckTree;
	std::cout << "Enter binary tree:";
	std::getline(std::cin, currentCheckTree);

	//удаление пробелов
	currentCheckTree.erase(std::remove_if(currentCheckTree.begin(), currentCheckTree.end(), [](char c) {return c == ' '; }), currentCheckTree.end());

	if (!checkBracketsPlacement(currentCheckTree))
	{
		std::cout << "Hmm, uncorect brackets statement\n";
		return 0;
	}

	determineTreeValuesType(currentCheckTree, std::cout);

	return 0;
}
