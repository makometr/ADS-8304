#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;


//вещественное_число:: = целое_число.целое_без_знака |целое_число.целое_без_знакаЕцелое число |целое_числоЕцелое_число
//целое_без_знака:: = цифра | цифра целое_без_знака
//целое_число::=целое_без_знака | + целое_без_знака | -целое_без_знака

void IsFloat(string str, bool* b, int *flag1, int* flag2);

bool IsInteger(string str, bool* b, int *flag1, int *flag2) {//рекурсивная функция, глубина которой определяется количеством цифр в числе
	
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

void IsFloat(string str, bool* b, int* flag1, int *flag2) {//функция регулирует постановку знаков в вещественном числе

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

	cout << "считывание c консоли - 0, с файла - 1\n" << endl;
	int a;
	cin >> a;
	if (a){
		string filename;
		cout << "Введите путь к файлу, который хотите открыть:";
   		cin >> filename;
		ifstream file(filename);
		if(!file.is_open()){
  	  		cout<<"Неверный путь к файлу\n";
	    		return 0;
    		}
		string str;

		while (getline(file,str)){

			IsFloat(str, &b, &flag1, &flag2);//вызов функции IsFloat
			b ? cout << str << " : True\n" : cout << str << " : False\n";
			b = false;
			flag1, flag2 = 0;
		}
		file.close();
	}else if (!a){
			string str1;
      			getline(cin, str1);
        		IsFloat(str1, &b, &flag1, &flag2);
       			b ? cout << ":True\n" : cout << ":False\n";

		}return 0;

}
