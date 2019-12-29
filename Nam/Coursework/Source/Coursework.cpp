#include "Source.h"

template <typename T1, typename T2>
void writeOutputData(std::ofstream& out, size_t testNumber, std::string type, T2 work_comb_time, T2 work_bubble_time, std::string const& arrStringForm,
	std::vector<T1> const& arr)
{
	out << "Test ¹" << testNumber << "\n";
	out << "Type: " << type << "\n";
	out << "Work comb time: " << work_comb_time << "mc\n";
	out << "Work bubble time: " << work_bubble_time << "mc\n";
	out << "Data: " << arrStringForm << "\n";

	out << "Result: ";
	for (auto const& elem : arr)
		out << elem << " ";
	out << "\n\n";
}

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

TypeCode determineType(std::string const& checkString)
{
	TransformPair<int> intTransform = from_string<int>(checkString);
	if (intTransform.transformResult == true)
		return TypeCode::TypeInt;

	TransformPair<char> charTransform = from_string<char>(checkString);
	if (charTransform.transformResult == true)
		return TypeCode::TypeChar;

	TransformPair<double> doubleTransform = from_string<double>(checkString);
	if (doubleTransform.transformResult == true)
		return TypeCode::TypeDouble;

	return TypeCode::TypeString;
}

int main(int argc, char** argv)
{
	if (argc > 2)
	{
		std::ifstream in(argv[1]);
		if (!in)
		{
			std::cout << "Uncorrect input file";
			return 0;
		}

		std::ofstream out(argv[2]);
		if (!out)
		{
			std::cout << "Uncorrect output file";
			return 0;
		}

		std::vector<std::string> fileData;
		readInputData(in, fileData);

		size_t testIndex = 1;
		for (auto const& line : fileData)
		{
			size_t firstSpaceInd = line.find(' ');
			if (firstSpaceInd == std::string::npos)
			{
				std::vector<std::string> arr = { line };
				writeOutputData(out, testIndex, "No need in calculation, because one-element array is already sorted", 0, 0, line, arr);
				++testIndex;
				continue;
			}

			std::string firstElement(line.begin(), line.begin() + firstSpaceInd);
			auto typeCalculationResult = determineType(firstElement);
			auto cmp = [](auto a, auto b) { return a < b; };

			switch (typeCalculationResult)
			{

			case TypeCode::TypeInt:
			{
				std::vector<int> arr;
				auto splitResult = split(arr, line, ' ');
				if (splitResult == false)
				{
					out << "Test ¹" << testIndex << "\n";
					out << "Uncorrect input data\n";
					++testIndex;
					continue;
				}

				auto start_comb = std::chrono::system_clock::now();
				comb(arr, cmp);
				auto end_comb = std::chrono::system_clock::now();

				auto start_bubble = std::chrono::system_clock::now();
				bubble(arr, cmp);
				auto end_bubble = std::chrono::system_clock::now();

				writeOutputData(out, testIndex, "Int", std::chrono::duration_cast<std::chrono::microseconds>(end_comb - start_comb).count(),
					std::chrono::duration_cast<std::chrono::microseconds>(end_bubble - start_bubble).count(), line, arr);

				break;
			}
			case TypeCode::TypeChar:
			{
				std::vector<char> arr;
				auto splitResult = split(arr, line, ' ');
				if (splitResult == false)
				{
					out << "Test ¹" << testIndex << "\n";
					out << "Uncorrect input data\n";
					++testIndex;
					continue;
				}

				auto start_comb = std::chrono::system_clock::now();
				comb(arr, cmp);
				auto end_comb = std::chrono::system_clock::now();

				auto start_bubble = std::chrono::system_clock::now();
				bubble(arr, cmp);
				auto end_bubble = std::chrono::system_clock::now();

				writeOutputData(out, testIndex, "Char", std::chrono::duration_cast<std::chrono::microseconds>(end_comb - start_comb).count(),
					std::chrono::duration_cast<std::chrono::microseconds>(end_bubble - start_bubble).count(), line, arr);

				break;
			}
			case TypeCode::TypeDouble:
			{
				std::vector<double> arr;
				auto splitResult = split(arr, line, ' ');
				if (splitResult == false)
				{
					out << "Test ¹" << testIndex << "\n";
					out << "Uncorrect input data\n";
					++testIndex;
					continue;
				}

				auto start_comb = std::chrono::system_clock::now();
				comb(arr, cmp);
				auto end_comb = std::chrono::system_clock::now();

				auto start_bubble = std::chrono::system_clock::now();
				bubble(arr, cmp);
				auto end_bubble = std::chrono::system_clock::now();

				writeOutputData(out, testIndex, "Double", std::chrono::duration_cast<std::chrono::microseconds>(end_comb - start_comb).count(),
					std::chrono::duration_cast<std::chrono::microseconds>(end_bubble - start_bubble).count(), line, arr);

				break;
			}
			case TypeCode::TypeString:
			{
				std::vector<std::string> arr;
				auto splitResult = split(arr, line, ' ');
				if (splitResult == false)
				{
					out << "Test ¹" << testIndex << "\n";
					out << "Uncorrect input data\n";
					++testIndex;
					continue;
				}

				auto start_comb = std::chrono::system_clock::now();
				comb(arr, cmp);
				auto end_comb = std::chrono::system_clock::now();

				auto start_bubble = std::chrono::system_clock::now();
				bubble(arr, cmp);
				auto end_bubble = std::chrono::system_clock::now();

				writeOutputData(out, testIndex, "String", std::chrono::duration_cast<std::chrono::microseconds>(end_comb - start_comb).count(),
					std::chrono::duration_cast<std::chrono::microseconds>(end_bubble - start_bubble).count(), line, arr);

				break;
			}
			default:
				out << "Incorrect type!\n";
				continue;
			}
			++testIndex;
		}
	}

	return 0;
}