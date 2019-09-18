
#include "BracketAnalyzer.h"


BracketAnalyzer::BracketAnalyzer()
{
}


BracketAnalyzer::~BracketAnalyzer()
{
}

std::vector<std::vector<char>> BracketAnalyzer::GetTextData(const char * filename)
{
	std::vector<std::vector<char>> textdata;

	std::vector<char> tmp_vect;

	textdata.push_back(tmp_vect);

	std::ifstream input;

	input.open(filename);

	if (!input) {
		std::cout << "Couldn't open source file";
		exit(1);
	}

	char tmp;

	while (input.get(tmp))
	{
		if (tmp!='\n')
			textdata.back().push_back(tmp);
		else {
			textdata.push_back(tmp_vect);
		}
	}
	input.close();

	return textdata;
}

void BracketAnalyzer::Analyze(const char* textfile, const char* parametersfile)
{
	text = BracketAnalyzer::GetTextData(textfile);
	parameters = BracketAnalyzer::GetTextData(parametersfile);

	while (text.size()) {

		std::vector<char>::iterator left = text.back().begin();
		std::vector<char>::iterator right = text.back().end(); right--;

		if (brackets(left, right)) {
			std::cout << "This is a correct Bracket(T) sequence" << std::endl;
		}
		else {
			std::cout << "This is NOT a correct Bracket(T) sequence" << std::endl;
		}

		text.pop_back();
		parameters.pop_back();
	}
}

bool BracketAnalyzer::brackets(std::vector<char>::iterator left, std::vector<char>::iterator right)
{
	return (element(left) && (left == right)) || list(left, right);

}

bool BracketAnalyzer::element(std::vector<char>::iterator left)
{
	return (std::find(parameters.back().begin(), parameters.back().end(), *left) != parameters.back().end());
}

bool BracketAnalyzer::list(std::vector<char>::iterator left, std::vector<char>::iterator right)
{
	return ((*left == 'N') && (left == right)) || ((*left == '[') && (*right == ']') && row(left + 1, right - 1));
}

bool BracketAnalyzer::row(std::vector<char>::iterator left, std::vector<char>::iterator right)
{
	bool result = true;

	while (left != right + 1) {
		if (*left != '[') {
			result = result && brackets(left, left);
			left++;
		}

		else {
			auto tmp_iter = left + 1;
			int cnt = 1;

			while (tmp_iter != right + 1) {
				if (*tmp_iter == '[')
					cnt++;
				if (*tmp_iter == ']')
					cnt--;

				if (!cnt) {
					result = result && row(left + 1, tmp_iter - 1);
					left = tmp_iter + 1;
					break;
				}

				tmp_iter++;
			}

			if (tmp_iter == right + 1)
				return false;
		}
	}
	
	return result;
}