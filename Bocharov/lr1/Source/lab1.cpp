#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <iostream>

bool isbracketsequence(std::string);
bool issquare(std::string);
bool iscircle(std::string);
bool isfigure(std::string);

bool isbracketsequence(std::string str)
{
	return issquare(str) || iscircle(str) || isfigure(str);
}

bool issquare(std::string str)
{
	if (str == "+")
		return true;

	if (str.size() < 4) return false; // По условию кв.ск. = [ab], при этом не менее 4 символов

	int cnt = 0;

	for (int i = 1; i <= str.size() - 2; i++) // не учитываем первую скобку и последнюю
	{
		if (str[i] == '(') //по условию круглые скобки
			cnt++;
		if (str[i] == ')')
			cnt--;
		if (!cnt)
		{
			cnt = i;
			break;
		}
	}

	if (cnt == str.size() - 2)
		return false; // в строке нет места для других скобок

	std::string substr1 = "";
	std::string substr2 = "";

	for (int i = 1; i <= cnt; i++)
		substr1 += str[i]; // записываю первые скобки
	for (int i = cnt + 1; i <= str.size() - 2; i++)
		substr2 += str[i]; // вторые скобки

	std::cout << "	  Analyzing issquare : " << str << std::endl;

	return ((str[0] == '[') && (str[str.size() - 1] == ']') && iscircle(substr1) && isfigure(substr2));
}

bool iscircle(std::string str)
{
	if (str == "-")
		return true;

	if (str.size() < 4) return false;

	int cnt = 0;

	for (int i = 1; i <= str.size() - 2; i++)
	{
		if (str[i] == '{')
			cnt++;
		if (str[i] == '}')
			cnt--;
		if (!cnt)
		{
			cnt = i;
			break;
		}
	}

	if (cnt == str.size() - 2)
		return false;

	std::string substr1 = "";
	std::string substr2 = "";

	for (int i = 1; i <= cnt; i++)
		substr1 += str[i];
	for (int i = cnt + 1; i <= str.size() - 2; i++)
		substr2 += str[i];


	std::cout << "	  Analyzing iscircle : " << str << std::endl;


	return  ((str[0] == '(') && (str[str.size() - 1] == ')') && isfigure(substr1) && issquare(substr2));
}
//
bool isfigure(std::string str) {

	if (str == "0")
		return true;

	if (str.size() < 4) return false;

	int cnt = 0;

	for (int i = 1; i <= str.size() - 2; i++)
	{
		if (str[i] == '[')
			cnt++;
		if (str[i] == ']')
			cnt--;
		if (!cnt)
		{
			cnt = i;
			break;
		}
	}

	if (cnt == str.size() - 2)
		return false;

	std::string substr1 = "";
	std::string substr2 = "";

	for (int i = 1; i <= cnt; i++)
		substr1 += str[i];
	for (int i = cnt + 1; i <= str.size() - 2; i++)
		substr2 += str[i];



	std::cout << "	  Analyzing isfigure: " << str << std::endl;


	return ((str[0] == '{') && (str[str.size() - 1] == '}') && issquare(substr1) && iscircle(substr2));
}


int main(int argc, char* argv[])
{
        std::string str;
        int k = 0;
	std::ifstream input;
		char tmp;
		std::string proc_str = "";
            	input.open(argv[1]);
		if (!input)
        {
            std::cout << "Couldnt open file" <<std::endl;
            }
            while(input.get(tmp)){
                if (tmp != '\n')
                {
                str +=tmp;

                }



                else
                {
		std::cout << "test "<<++k<<" for string - " << str << std::endl << std::endl;
                if (isbracketsequence(str))
			std::cout << "		" << str << " == Its bracket" << std::endl << std::endl;
                else
			std::cout << "		" << str << " == Its not bracket" << std::endl << std::endl;
                str = "";
                }
            }

}


