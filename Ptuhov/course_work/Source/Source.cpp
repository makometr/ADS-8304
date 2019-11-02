#include "Header.h"

// Demonstration

//проверка входных потоков на корректность
ReturnType streamsCheck(std::ifstream& in, std::ofstream& out)
{
	return (in && out) ? ReturnType::Correct : ReturnType::IncorrectStreams;
}

//определение типа, хранящегося в считанном ранее массиве
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

//чтение очередных входных данных и запись их в массив
StringVector readFileData(std::ifstream& in)
{
	StringVector fileData;
	std::string currentFileString;

	while (std::getline(in, currentFileString))
	{
		if (currentFileString.back() == '\r')
			currentFileString.erase(currentFileString.end() - 1);

		fileData.push_back(currentFileString);
	}

	return fileData;
}

int main(int argc, char** argv)
{
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


		StringVector fileData = readFileData(in);

		std::cout << "Sorts variant: ";
		std::cout << "\n\t1) Iter merge sort\n\t2) Rec merge sort\n\t3) Iter quick sort\n\t4) Rec quick sort\n\n";
		std::cout << "Enter your variant: ";
		int sortChoise = 0;
		std::cin >> sortChoise;


		for (auto it = fileData.begin(); it != fileData.end(); ++it)
		{
			std::string& arrStringForm = *it;

			out << "Test #" + std::to_string(it - fileData.begin() + 1) << "\nEntered array:\n" << arrStringForm << "\n\n";

			//считывание первого эл-та массива и определение его типа
			auto searchResult = std::find(arrStringForm.begin(), arrStringForm.end(), ' ');

			std::string firstELement(arrStringForm.begin(), searchResult);
			TypeCode type = determineType(firstELement);
			//


			switch (type)
			{
			case TypeCode::TypeInt:
			{
				std::vector<int> arr;

				//преобразование строки массив с ранее определеенным типом первого эл-та 
				//аналогично для остальных ветвей
				ReturnType formResult = formArr(arr, arrStringForm);
				if (formResult == ReturnType::IncorrectFileData)
				{
					out << "Array elements don't have same type\n\n";
					continue;
				}

				//сортировка массива
				//аналогично для остальных ветвей
				chooseSortVariant(sortChoise, arr, out);
				
				out << "Sorted array:\n";
				for (auto i : arr)
					out << i << ' ';
				out << "\n\n";

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

				chooseSortVariant(sortChoise, arr, out);

				out << "Sorted array:\n";
				for (auto i : arr)
					out << i << ' ';
				out << "\n\n";

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

				chooseSortVariant(sortChoise, arr, out);

				out << "Sorted array:\n";
				for (auto i : arr)
					out << i << ' ';
				out << "\n\n";

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

				chooseSortVariant(sortChoise, arr, out);

				out << "Sorted array:\n";
				for (auto i : arr)
					out << i << ' ';
				out << "\n\n";

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