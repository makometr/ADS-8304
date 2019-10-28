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


		for (auto it = fileData.begin(); it != fileData.end(); ++it)
		{
			std::string& arrStringForm = *it;

			out << "Entered array:\n" << arrStringForm << "\n\n";

			//считывание первого эл-та массива и определение его типа
			auto searchResult = std::find(arrStringForm.begin(), arrStringForm.end(), ' ');

			std::string firstELement(arrStringForm.begin(), searchResult);
			TypeCode type = determineType(firstELement);
			//

			// измняемый компаратор для эл-ов массива
			auto cmp = [](auto a, auto b) {return a < b; };

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
					out << "Array elements don't have same type\n";
					continue;
				}

				//сортировка массива
				//аналогично для остальных ветвей
				quickRecSort(arr, cmp, out);
				
				out << "Sorted array:\n";
				for (auto i : arr)
					out << i << ' ';
				out << "\n\n\n";

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

				quickRecSort(arr, cmp, out);

				out << "Sorted array:\n";
				for (auto i : arr)
					out << i << ' ';
				out << "\n\n\n";

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

				quickRecSort(arr, cmp, out);

				out << "Sorted array:\n";
				for (auto i : arr)
					out << i << ' ';
				out << "\n\n\n";

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

				quickRecSort(arr, cmp, out);

				out << "Sorted array:\n";
				for (auto i : arr)
					out << i << ' ';
				out << "\n\n\n";

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