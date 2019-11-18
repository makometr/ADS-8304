#include <set>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <locale>
#include <string>
#include <windows.h>
#include <unordered_map>
#include <fstream>

std::map<std::wstring, int> get_list_count_letter(std::wstring local_string) {
	std::map<std::wstring, int> set;
	for (auto c : local_string) {
		std::wstring tmp_string = { '\0' };
		tmp_string = c;
		if (set[tmp_string] == 0) {
			set[tmp_string] = 1;
		} else {
			set[tmp_string]++;
		}
	}
	return set;
}

std::vector<std::pair<std::wstring, int>>::iterator decision(std::vector<std::pair<std::wstring, int>>& arr, int b) {
	for (std::vector<std::pair<std::wstring, int>>::iterator it = arr.begin(); it != arr.end(); it++) {
		if ((*it).second <= b) {
			return it;
		}
	}
	return arr.end();
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::wstring input_string = {};
	std::vector<std::pair<std::wstring, int>> arr;
	
	std::getline(std::wcin, input_string);
	std::map<std::wstring, int> set = get_list_count_letter(input_string);
		
	for (auto iter : set) {
		arr.emplace_back(std::pair<std::wstring, int>(iter.first, iter.second));
	}

	std::sort(arr.begin(), arr.end(), [](std::pair<std::wstring, int> a, std::pair<std::wstring, int> b) {
									      return a.second > b.second;
									  }
	);

	int sum_frequency = 0;
	std::wstring sum_str = {};

	if (arr.size() > 2) {
		std::unordered_map<wchar_t, std::wstring> result = {};
		while (arr.size() != 1) {
			// определяем последний и предпоследний элементы
			auto last = --arr.end();
			auto penultimate = arr.end() -= 2;

			// считаем их общую частоту и определяем новый элемент
			sum_frequency = (*last).second + (*penultimate).second;
			sum_str = (*last).first + (*penultimate).first;

		// строим путь до элементов
			// проверка на равенство: тогда должны поменяться местами последний и предпоследний элементы, но так как
			// далее проводятся операции только через итераторы, мы просто поменяет местами эти итераторы)))
			if ((*last).second == (*penultimate).second) {
				auto tmp = std::move(last);
				last = std::move(penultimate);
				penultimate = std::move(tmp);
			}
			// операции с последним элементом
			if ((*last).first.size() == 1) {
				result[(*last).first[0]] = L"0";
			} else {
				for (auto c : (*last).first) {
					result[c] = L"0" + result[c];
				}
			}

			//операции с предпоследним элементом
			if ((*penultimate).first.size() == 1) {
				result[(*penultimate).first[0]] = L"1";
			} else {
				for (auto c : (*penultimate).first) {
					result[c] = L"1" + result[c];
				}
			}

			// вставляем новый элемент с общей частотой в нужное место и удаляем два последних
			arr.emplace(decision(arr, sum_frequency), std::pair<std::wstring, int>(sum_str, sum_frequency));
			arr.erase(arr.end() -= 2, arr.end());
		}

		std::wofstream symbol_code("symbol_code.txt");
		std::wofstream coding_message("coding_message.txt", std::ios::trunc);
		
		// вывод значений символ : его код
		for (auto pair : set) {
			symbol_code << pair.first << ":" << result[pair.first[0]] << std::endl;
		}

		// вывод закодированного сообщения
		for (auto symbol : input_string) {
			coding_message << result[symbol] << L" ";
		}
	}
	return 0;
}
