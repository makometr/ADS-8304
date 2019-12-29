#include "my_stack.h"

void readInputData(std::ifstream& in, std::vector<std::string>& data)
{
	std::string tmp;
	while (std::getline(in, tmp))
	{
		if (tmp.back() == '\r')
			tmp.erase(tmp.end() - 1);
		data.push_back(tmp);
	}
}

bool checkSymbolsCorection(std::string const& processedString)
{
	for (char c : processedString)
	{
		if (c < 'A' || c > 'D')
			return false;
	}

	return true;
}

bool check(std::string const& line)
{
	Stack<char> st;

	for (int i = 0; i < line.length(); ++i)
	{
		while (line[i] != 'C')
		{
			st.push(line[i]);

			++i;
			if (i == line.length())
				return false;
		}

		++i;
		while (line[i] != 'D')
		{
			if (st.empty())
				return false;

			char c = st.front();
			st.pop();

			if (c != line[i])
				return false;

			++i;
			if (i == line.length())
				return st.empty();
		}
	}

	return true;
}

int main(int argc, char** argv)
{
	if (argc > 2)
	{
		std::ifstream in(argv[1]);
		if (!in)
		{
			std::cout << "Uncorrect input file\n";
			return 0;
		}
		std::ofstream out(argv[2]);
		if (!out)
		{
			std::cout << "Uncorrect output file\n";
			return 0;
		}

		std::vector<std::string> inputData;
		readInputData(in, inputData);

		for (auto const& line : inputData)
		{
			bool symbolsCheckingResult = checkSymbolsCorection(line);
			if (symbolsCheckingResult == false)
			{
				out << "Uncorrect symbols\n";
				continue;
			}

			bool controlCheckResult = check(line);
			out << ((controlCheckResult) ? "YES\n" : "NO\n");
		}
	}

	return 0;
}