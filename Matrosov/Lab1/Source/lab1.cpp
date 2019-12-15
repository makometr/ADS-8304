#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<double>> minor(vector<vector<double>> matrix, int number) {

	int matrix_size = matrix.size();

	vector<vector<double>> minor;

	for (int i = 1; i < matrix_size; i++) {
		minor.push_back(matrix[i]);
		minor[i-1].erase(minor[i-1].begin() + number);
	}
	return minor;
}

double det(vector<vector<double>> matrix) {
	double result = 0;
	int matrix_size = matrix.size();
	if (matrix_size == 1) {
		result = matrix[0][0];
	}
	else if (matrix_size == 2) {
		result = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
	}
	else {
		for (int i = 0; i < matrix_size; i++) {
		result +=	matrix[0][i] * pow(-1, i + 2) * det(minor(matrix, i)); //+2 т.к. i >= 0
		}
	}
	return result;
}

int main()
{
	cout << "Enter full name of imput file: ";

	string input_file_name; //имя файла ввода
	cin >> input_file_name;
	ifstream fin;
	fin.open(input_file_name);

	vector<vector<double>> matrix; //исходная матрица

	vector<double> line;

	if (fin.is_open()) {
		double tmp;

		int matrix_size; //размерность матрицы

		fin >> matrix_size;

		for (int i = 0; i < matrix_size; i++) {
			for (int j = 0; j < matrix_size; j++) {
				fin >> tmp;
				line.push_back(tmp);
			}
			matrix.push_back(line);
			line.clear();
		}

		cout <<"DetA = " << det(matrix) << endl;


	}
	else {
		cout << "File " << input_file_name << " can't be opened for reading!";
	}

	fin.close();
	fout.close();
	system("pause");
    return 0;
}

