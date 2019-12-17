#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <forward_list>

constexpr size_t DEFAULT_LEN = 103;//стартовая длина
constexpr size_t COEFF = 31; //стартовый множитель для хэша
constexpr size_t COEFFS_COUNT = 100; //количество степеней множителя, высчитываемых заранее
constexpr size_t PRIMES_COUNT = 24;//количество простых чисел для расширения хэш-таблицы
constexpr size_t PRIMES[] = { 103 , 211, 331 , 449 , 587 , 709 , 853 , 991 , 1117 , 1279 , 1433 , 1567 , 1709 , 	1873 , 2027 , 2179 , 2341 , 2477 , 2671 , 2797 , 2963 , 	3163, 3319, 3469 };


class HashTable {
private:
	std::forward_list<std::string>* arr; //массив с информацией
	size_t len; //количество выделенной памяти
	size_t realLen; //количество элементов в массиве
	unsigned long long* coeffs;//массив коэффициентов
	unsigned long long hash(std::string elem);
public:
	void expandTable();
public:
	HashTable();
	~HashTable();

	void insert(std::string elem);
	bool find(std::string elem, unsigned long long myHash);
	void checkCollisions() const;
	size_t getLen() const;

};
