#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <climits>
int expression(char* mas, int result, char* flag) {//рекурсивная функция
	while (isdigit(*mas))
		mas++;
	if (*mas == '+') {
		mas++;
		if (result < INT_MAX - atoi(mas)) {//если нет переполнения, рекурсия продолжается
			result = expression(mas, result + atoi(mas), flag);
		}
		else {
			*flag=1;//если переполнение, то ставим флаг
		}
	}
	else if (*mas == '-') {
		mas++;
		if (result > INT_MIN + atoi(mas)) {//аналогично для отрицательных значений
			result = expression(mas, result - atoi(mas), flag);
		}
		else {
			*flag=1;
		}
	}
	return result;//функция возвращает результат выражения
}

void mult(char* arr) {
	char* search = strstr(arr, "*");//ищем знак умножения
	while (search != NULL) {//заменяем умножение на результат
		search -= 1;
		int a = 1;
		while (isdigit(*(search)) && (search > arr)) {
			search -= 1;
			a += 1;
		}
		if (search != arr) {
			search += 1;
			a -= 1;
		}
		int b = (atoi(search) * atoi(search + a + 1));
		char beta[80];
		sprintf(beta, "%d", b);
		search = search + a + 1;
		int c = 0;
		while (isdigit(*(search))) {
			c++;
			search++;
		}
		char* next = search;
		search = search - a - c - 1;
		memmove(search, beta, strlen(beta));
		search = search + strlen(beta);
		memmove(search, next, strlen(next) + c);
		search = strstr(search, "*");
	}
}

int main(int argc, char* argv[]){
	int memory = 50;
	char* arr = (char*)malloc(memory * sizeof(char));//выделяем память для массива
	char* flag = (char*)calloc(3, sizeof(char));//флаг для рекурсивной функции
	if (argc == 1) {//считывание с консоли
		int index = 0;
		char s;
		for (; ; ) {
			s = getchar();
			if (s == '\n')
				break;
			arr[index] = s;
			index++;
			if (index == memory - 1) {
				memory += 50;
				arr = (char*)realloc(arr, memory * sizeof(char));//перевыделение памяти, если требуется
			}
		}
		arr[index] = '\0';
		mult(arr);//вызов функции поиска умножения
		int res = expression(arr, atoi(arr), flag);//вызов рекурсивной функции подсчета выражения
		if (*flag!=1)
			std::cout << res << '\n';//если не было переполнения, выводим результат
		else
			std::cout << "Error, set value exceeded!\n";//иначе выводим сообщение о переполнении
	}
	else {//считывание из файла
		FILE* file = fopen(argv[1], "r");//открываем файл
		if (!file) {//если файл не открыт выводим сообщение и завершаем программу
			std::cout<<"Incorrect file name\n";
			return 0;
		}
		int index = 0;
		char c=getc(file);
		while (c != EOF) {
			while ((c != '\n')&&(c!=EOF)) {
				arr[index] = c;
				index++;
				if (index == memory - 1) {
					memory += 50;
					arr = (char*)realloc(arr, memory * sizeof(char));//перевыделение памяти, если требуется
				}
				c = getc(file);
			}
			arr[index] = '\0';
			mult(arr);//вызов функции поиска умножения
			int res = expression(arr, atoi(arr), flag);//вызов рекурсивной функции подсчета выражения
			if (*flag != 1)
				std::cout << res << '\n';//если не было переполнения, выводим результат
			else
				std::cout << "Error, set value exceeded!\n";//иначе выводим сообщение о переполнении
			*flag = 0;//обнуляем флаг после каждого цикла
			index = 0;//обнуляем индекс после каждого цикла
			c = getc(file);
		}
		fclose(file);
	}
	free(flag);
	free(arr);
	return 0;

}
