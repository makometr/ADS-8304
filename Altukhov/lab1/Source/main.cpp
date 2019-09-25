#include <iostream>
#include <fstream>
#include <climits> //для отслеживания переполнения
#include <string>
using namespace std;

bool fRead(ifstream& f, int& n, int& m) { //вспомогательная функция для считывания входных данных с файла
	
	bool res = false;
	if ((f >> n) && (f >> m))
		res = true;
	char buff[50];
	f.getline(buff, 50); //досчитываем строку
	return res;
	
}

void consoleInput(int& n, int& m) { //вспомогательная функция для считывания входных данных с консоли
	cout << "Введите n и m.\n";
	cin >> n >> m;
}

string createTabs(int depth){ //возвращает строку с нужным колвом табов
	string res = "";
	for (int i=0; i<depth; i++)
		res+="\t";
	return res;
}

void recBinomial(int n, int m, unsigned long long int& res, int depth, ofstream& f) { //считаем биномиалы
	
	cout << createTabs(depth) << "Начало. Глубина: " << depth << ", " << "n: " << n << ", m: " << m << ", Результат: " << res << "\n";
	f << createTabs(depth) << "Начало. Глубина: " << depth << ", " << "n: " << n << ", m: " << m << ", Результат: " << res << "\n";
	if (ULLONG_MAX == res) { //переполнение
		cout << createTabs(depth) << "Достигнуто максимальное значение. Конечный результат может быть не верен. Глубина: " << depth << ", " << "n: " << n << ", m: " << m << ", Результат: " << res << "\n";
		f << createTabs(depth) << "Достигнуто максимальное значение. Конечный результат может быть не верен. Глубина: " << depth << ", " << "n: " << n << ", m: " << m << ", Результат: " << res << "\n";
		return;
	}
	if (((m == 0) && (n > 0)) || ((m == n) && (m >= 0))) {

		res += 1;
		cout << createTabs(depth) << "+1. Глубина: " << depth << ", " << "n: " << n << ", m: " << m << ", Результат: " << res << "\n";
		f << createTabs(depth) << "+1. Глубина: " << depth << ", " << "n: " << n << ", m: " << m << ", Результат: " << res << "\n";
		return;
	}
	if ((m > n) && (m >= 0)) {
		cout << createTabs(depth) << "+0. Глубина: " << depth << ", " << "n: " << n << ", m: " << m << ", Результат: " << res << "\n";
		f << createTabs(depth) << "+0. Глубина: " << depth << ", " << "n: " << n << ", m: " << m << ", Результат: " << res << "\n";
		return;
	}
	//если не случаи выше, то по определению разложение на сумму двух сочетаний
	recBinomial(n - 1, m - 1, res, depth + 1, f);
	recBinomial(n - 1, m, res, depth + 1, f);
	cout << createTabs(depth) << "Конец. Глубина: " << depth << ", " << "n: " << n << ", m: " << m << ", Результат: " << res << "\n";
}

void inputProcessing(int n, int m, ofstream& f){
	
	if (!((n >= 0) && (m >= 0))) {
		cout << "Введенные данные некорректны: " << n << " " << m << "\n\n\n";
		f << "Введенные данные некорректны: " << n << " " << m << "\n\n\n";
		return;
	}
	cout << "Введенные данные: " << n << " " << m << "\n";
	f << "Введенные данные:" << n << " " << m << "\n";

	unsigned long long int res = 0; //кол-во сочетаний >=0
	recBinomial(n, m, res, 0, f);
	cout << "Результат: " << res << "\n\n\n";
	f << "Результат: " << res << "\n\n\n";
	
}	

int main(int argc,char* argv[]) {

	ifstream inputF;
	if (argc > 1)
		inputF.open(argv[1]);
	else
		inputF.open("input.txt");


	//ifstream inputF("input.txt");
	ofstream outputF("output.txt");
	if (!(outputF.is_open())) {
		cout << "Файл вывода не найден.\n";
		return 0;
	}
	if (!(inputF.is_open()))
		cout << "Файл ввода не найден.\n";
	
	int n = 0, m = 0;
	int inputType = 0;
	if (argc == 1){
		cout << "Выберите тип ввода:\n1 - ввод из консоли.\n2 - ввод из файла.\n";
		cin >> inputType;
	}
	else
		inputType = 2;
	
	
	if (inputType == 1) //выбран ввод с консоли
		consoleInput(n, m);
	else if (inputType == 2) { //выбран ввод с файла
		if (!(inputF.is_open())) {
			cout << "Файл ввода не найден.\n";
			return 0;
		}
	}
	else {
		cout << "Некорректный тип ввода. Выбран тип по умолчанию.\n"; //ввод с консоли
		consoleInput(n, m);
	}

	if (inputType == 1){
		inputProcessing(n, m, outputF);
		
	}
	else{
		while (fRead(inputF, n, m)){ //читаем пока в файле что-то есть
			inputProcessing(n, m, outputF);
		}
	}
	

	inputF.close();
	outputF.close();

	return 0;
}
