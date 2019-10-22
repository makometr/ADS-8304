#include "BracketAnalyzer.h"


std::vector<std::string> BracketAnalyzer::GetTextData(const char * filename)
{
	std::vector<std::string> textdata;

	std::ifstream input;

	input.open(filename);

	if (!input) {
		std::cout << "Couldn't open source file";
		exit(1);
	}

	char tmp;
	std::string processed_string = "";

	while (input.get(tmp))
	{
		if (tmp != '\n')
			processed_string += tmp;
		else {
			textdata.push_back(processed_string);
			processed_string = "";
		}
	}

	textdata.push_back(processed_string);

	input.close();

	return textdata;
}

void BracketAnalyzer::Analyze(const char* textfile, const char* parametersfile)
{
	int test_cnt = 1;
	
	text = BracketAnalyzer::GetTextData(textfile);
	parameters = BracketAnalyzer::GetTextData(parametersfile);

	while (text.size() && text.back().size() && parameters.back().size()) {

		iter left = text.back().begin();
		iter right = text.back().end(); 
		right--;
		
		std::cout << "Test #" << test_cnt++ << std::endl;
		std::cout << "Processed string : " << text.back() << std::endl
			<< "Parameters : " << parameters.back() << std::endl;

		if (isbrackets(left, right)) {
			std::cout << "This is a correct Bracket(T) sequence\n________" << std::endl;
		}
		else {
			std::cout << "This is NOT a correct Bracket(T) sequence\n________" << std::endl;
		}

		text.pop_back();
		parameters.pop_back();
	}
}

bool BracketAnalyzer::isbrackets(iter& left, iter& right)
{
	return (iselement(left) && (left == right)) || islist(left, right);

}

bool BracketAnalyzer::iselement(iter& left)
{
	return (std::find(parameters.back().begin(), parameters.back().end(), *left) != parameters.back().end());
}

bool BracketAnalyzer::islist(iter& left, iter& right)
{
	return ((*left == 'N') && (left == right)) || ((*left == '[') && (*right == ']') && isrow(++left, --right));
}

bool BracketAnalyzer::isrow(iter& left, iter& right)
{
	bool result = true;

	while (left != right + 1) {
		if (*left != '[') {
			result = result && isbrackets(left, left);
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
					result = result && isrow(++left, --tmp_iter);
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
