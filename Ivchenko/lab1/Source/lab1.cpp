#include <iostream>
#include <string>
#include <cctype>
#include <fstream>



//вещественное_число:: = целое_число.целое_без_знака |целое_число.целое_без_знакаЕцелое число |целое_числоЕцелое_число
//целое_без_знака:: = цифра | цифра целое_без_знака
//целое_число::=целое_без_знака | + целое_без_знака | -целое_без_знака

void IsFloat(std::string str, bool* b, int *flag1, int* flag2);

bool IsInteger(std::string str, bool* b, int *flag1, int *flag2) {//рекурсивная функция, глубина которой определяется количеством цифр в числе
	
	if (!isdigit(str[0])) {
		if ((str[0] == '.')||(str[0] == 'E')||(str[0] == '+')||(str[0] == '-')) {
			IsFloat(str, b, flag1, flag2);

		}
		else {
			*b = false;
			return 0;
		}
	}
	else if (str.length() != 1) {
		IsInteger(str.substr(1, 100), b, flag1, flag2);
		return 1;

	}

}

void IsFloat(std::string str, bool* b, int* flag1, int *flag2) {//функция регулирует постановку знаков в вещественном числе

	if ((!*flag1) &&(!*flag2)&& (((str[0] == '+') || (str[0] == '-')) && ((isdigit(str[1]))) || (isdigit(str[0])))) {
		*flag1 = 1;
		if (!IsInteger(str.substr(1, 100), b, flag1, flag2)) return;
	}
	else if (*flag1 && (str[0] == '.')) {
		*flag1 = 0;
		*flag2 = 1;
		*b = true;
		if (!IsInteger(str.substr(1, 100), b, flag1, flag2)) return;
	}
	
	else if ((*flag2) && (str[0] == 'E')) {
		*flag2 = 0;
		*b = true;
		if (!IsInteger(str.substr(1, 100), b, flag1, flag2)) return;
		}

	else {
		*b = false;
		return;
	}


}


int main()
{
	setlocale(LC_ALL, "Russian");

	bool b = false;
	int flag1 = 0;// флаг, дает доступ к символу '.'
	int flag2 = 0;// флаг, дает доступ к символу 'E'

	std::cout << "считывание c консоли - 0, с файла - 1\n" << std::endl;
	int a;
	std::cin >> a;
	getchar();
	if (a==1){
		std::string filename;
		std::cout << "Введите путь к файлу, который хотите открыть:";
   		std::cin >> filename;
		std::cout << std::endl;
		std::ifstream file(filename);
		if(!file.is_open()){
  	  		std::cout<<"Неверный путь к файлу\n";
	    		return 0;
    		}
		std::string str;
		int a = 1;
		while (std::getline(file,str)){
			
			IsFloat(str, &b, &flag1, &flag2);//вызов функции IsFloat
			b ? std::cout << a << ") " << str << " : True\n\n" : std::cout << a <<") " << str << " : False\n\n";
			b = false;
			flag1, flag2 = 0;
			a++;
		}
		file.close();
	}else if (!a){
			std::string str1;
      			std::getline(std::cin, str1);
        		IsFloat(str1, &b, &flag1, &flag2);
       			b ? std::cout << "True\n" : std::cout << "False\n";
	}else{ std::cout << "Введены некорректные значения, bb" << std::endl;
		
	}

	return 0;

}
