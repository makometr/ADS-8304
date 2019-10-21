#include "Header.h"

ReturnType streamsCheck(std::ifstream& in, std::ofstream& out)
{
	return (in && out) ? ReturnType::Correct : ReturnType::IncorrectStreams;
}

TypeCode determineType(std::string const& checkString)
{
	TranformPair<int> intTransform = from_string<int>(checkString);
	if (intTransform.transformResult == true)
		return TypeCode::TypeInt;

	TranformPair<char> charTransform = from_string<char>(checkString);
	if (charTransform.transformResult == true)
		return TypeCode::TypeChar;

	TranformPair<double> doubleTransform = from_string<double>(checkString);
	if (doubleTransform.transformResult == true)
		return TypeCode::TypeDouble;

	return TypeCode::TypeString;
}

void readFileData(std::ifstream& in, StringVector& fileData)
{
	std::string currentFileString;

	while (std::getline(in, currentFileString))
	{
		if (currentFileString.back() == '\r')
			currentFileString.erase(currentFileString.end() - 1);

		fileData.push_back(currentFileString);
	}
}

int main(int argc, char** argv)
{
	srand(time(0));

	if (argc > 2)
	{
		std::ifstream in(argv[1]);
		std::ofstream out(argv[2]);
		ReturnType streamsCheckResult = ReturnType::Correct;

		streamsCheckResult = streamsCheck(in, out);
		if (streamsCheckResult == ReturnType::IncorrectStreams)
		{
			out << "Incorrect streams\n";
			return 0;
		}


		StringVector fileData;
		readFileData(in, fileData);

		for (auto it = fileData.begin(); it != fileData.end(); ++it)
		{
			std::string& arrStringForm = *it;

			auto searchResult = std::find(arrStringForm.begin(), arrStringForm.end(), ' ');
			if (searchResult == arrStringForm.end())
			{
				out << arrStringForm << '\n';
				continue;
			}

			std::string firstELement(arrStringForm.begin(), searchResult);
			TypeCode type = determineType(firstELement);
			auto cmp = [](auto a, auto b) {return a < b; };
	//		auto reverseCmp = [](auto a, auto b) {return a > b; };

			switch (type)
			{
			case TypeCode::TypeInt:
			{
				std::vector<int> arr;
				ReturnType formResult = formArr(arr, arrStringForm);
				if (formResult == ReturnType::IncorrectFileData)
				{
					out << "Array elements don't have same type\n";
					continue;
				}

				quickItSort(arr, cmp);
				for (auto i : arr)
					out << i << ' ';
				out << '\n';

				break;
			}
			case TypeCode::TypeChar:
			{
				std::vector<char> arr;
				ReturnType formResult = formArr(arr, arrStringForm);
				if (formResult == ReturnType::IncorrectFileData)
				{
					out << "Array elements don't have same type\n";
					continue;
				}

				quickRecSort(arr, cmp);
				for (auto i : arr)
					out << i << ' ';
				out << '\n';

				break;
			}
			case TypeCode::TypeDouble:
			{
				std::vector<double> arr;
				ReturnType formResult = formArr(arr, arrStringForm);
				if (formResult == ReturnType::IncorrectFileData)
				{
					out << "Array elements don't have same type\n";
					continue;
				}

				quickRecSort(arr, cmp);
				for (auto i : arr)
					out << i << ' ';
				out << '\n';

				break;
			}
			case TypeCode::TypeString:
			{
				std::vector<std::string> arr;
				ReturnType formResult = formArr(arr, arrStringForm);
				if (formResult == ReturnType::IncorrectFileData)
				{
					out << "Array elements don't have same type\n";
					continue;
				}

				quickRecSort(arr, cmp);
				for (auto i : arr)
					out << i << ' ';
				out << '\n';

				break;
			}
			default:
				out << "Incorrect type!\n";
				continue;
			}
		}
	}

	return 0;
}