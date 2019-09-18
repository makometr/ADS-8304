#include "pch.h"
#include "BracketAnalyzer.h"


BracketAnalyzer::BracketAnalyzer()
{
}


BracketAnalyzer::~BracketAnalyzer()
{
}

std::vector<std::string> BracketAnalyzer::GetTextData(const char * filename)
{
	std::vector<std::string> textdata(1);

	std::ifstream input;

	input.open(filename);

	if (!input) {
		std::cout << "Couldn't open source file";
		exit(1);
	}

	char tmp;

	while (input.get(tmp))
	{
		if (tmp != '\n')
			textdata.back() += tmp;
		else {
			textdata.resize(textdata.size() + 1);
		}
	}
	input.close();

	return textdata;
}

void BracketAnalyzer::Analyze(const char* textfile, const char* parametersfile)
{
	text = BracketAnalyzer::GetTextData(textfile);
	parameters = BracketAnalyzer::GetTextData(parametersfile);

	while (text.size() && text.back().size() && parameters.back().size()) {

		iter left = text.back().begin();
		iter right = text.back().end(); right--;

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

bool BracketAnalyzer::brackets(iter& left, iter& right)
{
	return (element(left) && (left == right)) || list(left, right);

}

bool BracketAnalyzer::element(iter& left)
{
	return (std::find(parameters.back().begin(), parameters.back().end(), *left) != parameters.back().end());
}

bool BracketAnalyzer::list(iter& left, iter& right)
{
	return ((*left == 'N') && (left == right)) || ((*left == '[') && (*right == ']') && row(++left, --right));
}

bool BracketAnalyzer::row(iter& left, iter& right)
{
	bool result = true;

	while (left != right + 1) {
		if (*left != '[') {
			result = result && brackets(left, left);
			left++;
		}

		else {
			auto tmp_iter = left;
			tmp_iter++;

			int cnt = 1;

			while (tmp_iter != right + 1) {
				if (*tmp_iter == '[')
					cnt++;
				if (*tmp_iter == ']')
					cnt--;

				if (!cnt) {
					result = result && row(++left, --tmp_iter);
					left = tmp_iter + 2;
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