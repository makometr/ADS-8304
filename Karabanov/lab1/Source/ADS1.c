#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int Brackets(char* str, char OpenBracket, int i, int RecDepth);
bool isText(char* str);

/* функция проверки парности скобок, принимает 
указатель на строку, индекс закрывающей скобки и открывающую скобку*/
bool PairScope(char* str, char OpenBracket, int i){ 
	if (OpenBracket == '(' && str[i] == ')') {	   
		return true;				       
	}
	else if (OpenBracket == '{' && str[i] == '}') {
		return true;
	}
	else if (OpenBracket == '[' && str[i] == ']') {
		return true;
	}
	else {
		return false;
	}
}

int main(int argc, char* argv[]) {
	char* str = (char*)calloc(200, sizeof(char)); 
	// если не указана папка с тестами, то пользователь вводи строку
	if (argc == 1){ 
		printf("Введите текст со скобками: ");
		fgets(str, 199, stdin);
			if (isText(str))
				printf("Это текст со скобками\n");
			else
				printf("Это не текст со скобками\n");
	}
	else {
		char* path = (char*)calloc(strlen(argv[1]) + 8, sizeof(char)); // строка для открытия файла
		char* estr; // указатель для отслеживания конца файла
		strcat(path, "Tests/");  
		strcat(path, argv[1]); 
		FILE* fileTests = fopen(path, "r"); // открываем файл
		if (!fileTests){ 
			printf("Ошибка открытия файла\n");
			return 0;
		}
		else{
			while (1){
				estr = fgets(str, 199, fileTests); // считываем строку из файла
				// если указатель NULL то проверяем на ошибку или конец файла
				if (estr == NULL){ 
					if (feof(fileTests) != 0){
						printf("Конец файла\n");
						break;
					}
					else {
						printf("Ошибка чтения файла\n");
						break;
					}
				}
				if (strlen(str) == 1){ // проверка на пустую строку
					printf("'Пустая строка'\n");
				}
				else{
					printf("%s\n", str);
				}
				if (isText(str)) // проверка на текст со скобками
					printf("Это текст со скобками  >> %s", str);
				else
					printf("Это не текст со скобками  >> %s", str);
			}
			free(path);
		}
	}
	free(str);
	return 0;
}

// функция проверки, принимает указатель на строку 
bool isText(char* str) { 
	int i = 0; // индекс символа
	while (str[i] != '\n' || str[i] == '\0') {
		//пропуск букв тк их может сколько угодно идти подряд
		if (str[i] == 'A' || str[i] == 'B') { 
			i++;
		}
		else if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
			i++;
			// находим скобку и вызываем рекурсивную функцию, возвращаем индекс с которого продолжим 
			i = Brackets(str, str[i - 1], i, 0); 
			if (i == -1) { 
				return false;
			}
		}
		else {
            printf("Ошибка на символе номер %d - %c \n", i + 1, str[i]);
			return false;
        }
	}
	// возвращаем истину, тк дошли до конца без ошибок и проверяем на не пустоту строки.  
	return true && i; 
}

/* рекурсивная функция принимает указатель на строку
символ который является открывающей скобкой индекс текущего символа, глубину рекурсии */
int Brackets(char* str, char OpenBracket, int i, int RecDepth) { 
	bool AlphainScope = false; // наличии буквы в скобках
	printf("%*.sRecFun('%c')\n", 4*RecDepth, " ", str[i - 1]); // отладочный вывод
	while (str[i] != '\n'|| str[i] == '\0') {
		if (str[i] == 'A' || str[i] == 'B') {
			AlphainScope = true;
			i++;
		}
		// аналогично работе в функции isText
		else if (str[i] == '(' || str[i] == '[' || str[i] == '{') { 
			i++;
			// возвращаем индекс с которого будем продолжать
			i = Brackets(str, str[i - 1], i, RecDepth + 1); 
			if (i != -1) {
				AlphainScope = true;
			}
			else {
				return -1;
			}
		}
		// проверка на парсность скобок и вложенность в них символа
		else if (PairScope(str, OpenBracket, i) && AlphainScope) { 
			i++;
			printf("%*.s", 4*RecDepth, " "); // отладочные выводы
			printf("Найдена закрывающая скобка '%c', удовлетворяющая условию, выход из рекурсивной функции\n", str[i - 1]);
			return i;
		}
		else {
			printf("Ошибка на символе номер %d - %c \n", i + 1, str[i]);
			break;
		}
	}
	return -1;
}