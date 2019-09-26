#include "Header.h"

using namespace vecqu;

std::string getStringNumberValue(std::string& currentFileString)
{
	auto numberBegin = std::find_if(currentFileString.begin(), currentFileString.end(),
		[](char currentCheckElement) {return std::isdigit(currentCheckElement); });
	if (numberBegin == currentFileString.end())
		return "";

	std::string stringNumberValue = "";
	auto numberEnd = numberBegin;

	while (numberEnd != currentFileString.end() && isdigit(*numberEnd))
	{
		stringNumberValue += *numberEnd;
		numberEnd++;
	}
	currentFileString.erase(numberBegin, numberEnd);

	return stringNumberValue;
}

int main(int argc, char** argv)
{
	Queue<std::string> queue;

	if (argc > 2)
	{

		std::ifstream in(argv[1]);
		std::ofstream out(argv[2]);

		if (!in.is_open())
		{
			std::cout << "Input file is incorrect. Try to change data\n";
			return 0;
		}

		if (!out.is_open())
		{
			std::cout << "Output file is incorrect. Try to change data\n";
			return 0;
		}

		std::string currentFileString = "";

		while (std::getline(in, currentFileString))
		{
			if (*(currentFileString.end() - 1) == '\r')
				currentFileString.erase(currentFileString.end() - 1);
			std::cout << "Current check-string - " + currentFileString + "\n" + "Numbers in check-string in right order: ";

			while (1)
			{

				std::string stringNumberValue = getStringNumberValue(currentFileString);
				if (stringNumberValue.empty())
					break;

				queue.push(stringNumberValue);
				std::cout << stringNumberValue << " ";
			}
			std::cout << std::endl << std::endl;

			while (!queue.empty())
			{
				currentFileString += queue.front();

				try
				{
					queue.pop();
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					return 0;
				}
			}

			out << currentFileString << "\r\n";
		}
		std::cout << "Work complete let's eat!\n";
	}
}
