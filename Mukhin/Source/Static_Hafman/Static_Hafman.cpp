#include "Static_Hafman.h"

/*!
 * @brief Функция, которая подсчитывает количество вхождений каждого символа в переданную ей строку.
 * @param local_string строка, в которой надо подсчитать количество вхождений её символов
 * @return словарь <std::string, int>, содержащий символ и его количество
 */
std::map<std::string, int> get_list_count_letter(const std::string& local_string) {
	std::map<std::string, int> set;
	for (auto c : local_string) {
		std::string tmp_string = { '\0' };
		tmp_string = c;
		if (set[tmp_string] == 0) {
			set[tmp_string] = 1;
		} else {
			set[tmp_string]++;
		}
	}
	return set;
}

/*!
 * @brief Функция поиска нужного места для вставки слитых символов
 * @param arr вектор, в котором должна произойти вставка
 * @param b вес, который сравнивается с остальными весами в векторе
 * @return если такого места нет, возвращается итератор на end(), в противном случае на элемент,
 * перед которым произойдёт вставка
 */
std::vector<std::pair<std::string, int>>::iterator decision(std::vector<std::pair<std::string, int>>& arr, int b) {
	for (auto it = arr.begin(); it != arr.end(); it++) {
		if ((*it).second <= b) {
			return it;
		}
	}
	return arr.end();
}

/*!
 * @brief Функция декодирования закодированной строки.
 * @details Декодирование происходит до тех пор, пока мы не пройдёмся по закодированной строке полностью.
 * В цикле перебирая все пары из словаря result мы ищем ключ-символ, строка-значение которого
 * будет началом закодированной строки. В виду того, что все коды символов обладают свойством префиксности,
 * проход по закодированной строке будет однозначным.
 * @param result словарь <char, std::string>, ключ является символом, а значение по ключу кодированием этого символа
 * @param coding_message закодированное сообщение
 * @param i порядковый номер аргумента командной строки, нужен для создания очередного файлы    вывода
 */
void decode(const std::unordered_map<char, std::string>& result, std::fstream& coding_message) {
	int lenght = 0;
	std::string coding_string = {};
	std::ofstream decode_message(std::string("decode_message_Static_Hafman.txt"));
	coding_message.seekg(0, std::ios::beg);

	std::getline(coding_message, coding_string);

	while (!coding_string.empty()) {
		for (const auto& pair : result) {
			auto k = coding_string.find(pair.second);
			if (!k) {
				decode_message << pair.first;
				lenght = pair.second.length();
				coding_string.erase(0, lenght);
				break;
			}
		}
	}
}

int use_static(std::string input_string) {
    std::vector<std::pair<std::string, int>> arr;

    std::map<std::string, int> set = get_list_count_letter(input_string);

    for (const auto& iter : set) {
        arr.emplace_back(std::pair<std::string, int>(iter.first, iter.second));
    }

    std::sort(arr.begin(), arr.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                                          return a.second > b.second;
                                      }
    );

    int sum_frequency = 0;
    std::string sum_str = {};
    std::unordered_map<char, std::string> result = {};

    if (arr.size() == 1) {
        result[arr[0].first[0]] = "1";
    } else {
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
                std::swap(last, penultimate);
            }

            // операции с последним элементом
            if ((*last).first.size() == 1) {
                result[(*last).first[0]] = "0";
            } else {
                for (auto c : (*last).first) {
                    result[c] = "0" + result[c];
                }
            }

            //операции с предпоследним элементом
            if ((*penultimate).first.size() == 1) {
                result[(*penultimate).first[0]] = "1";
            } else {
                for (auto c : (*penultimate).first) {
                    result[c] = "1" + result[c];
                }
            }

            // вставляем новый элемент с общей частотой в нужное место и удаляем два последних
            arr.emplace(decision(arr, sum_frequency), std::pair<std::string, int>(sum_str, sum_frequency));
            arr.erase(arr.end() -= 2, arr.end());
        }
    }

    std::ofstream symbol_code(std::string("symbol_code_Static_Hafman.txt"));
    std::fstream coding_message(std::string("code_message_Static_Hafman.txt"), std::ios::out | std::ios::in | std::ios::trunc);

    // вывод значений символ : его код
    for (const auto& pair : set) {
        symbol_code << pair.first << ":" << result[pair.first[0]] << std::endl;
    }

    for (auto symbol : input_string) {
        coding_message << result[symbol];
    }

    decode(result, coding_message);

    symbol_code.close();
    coding_message.close();
	return 0;
}
