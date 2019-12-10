#include "HashTable.h"

HashTable::HashTable() :arr(new std::forward_list<std::string>[DEFAULT_LEN]), len(DEFAULT_LEN), realLen(0), coeffs(new unsigned long long[COEFFS_COUNT]) { //высчитываем коэффициенты для хэша
	for (int i = 0; i < COEFFS_COUNT; i++) {
		coeffs[i] = (i > 0) ? coeffs[i - 1] * COEFF : COEFF;
	}
}

HashTable::~HashTable() {
	delete[] coeffs;
	delete[] arr;
}

unsigned long long HashTable::hash(std::string elem) {//полиномиальная функция хэширования (s1*a^1 + s2*a^2 + ... + sn*a^n) mod len

	unsigned long long myHash = 0;
	for (int i = 0; i < elem.length(); i++) {
		myHash += elem[i] * coeffs[i%COEFFS_COUNT];//если нужно больше коэффициентов, то и так сойдет
	}
	myHash %= len;
	return myHash;

}

bool HashTable::find(std::string elem, unsigned long long myHash) {
	if (myHash == len)//если хеш еще не посчитан то передается несуществующий
		myHash = hash(elem);
	if (!arr[myHash].empty()) {
		auto current = arr[myHash].begin();
		auto end = arr[myHash].end();
		while (current != end) {
			if (*current == elem)
				return true;
			current++;
		}
		return false;
	}
	else return false;
}


void HashTable::insert(std::string elem) {

	if (realLen > 0.9 * len) 
		expandTable();

	unsigned long long myHash = hash(elem);
	if (find(elem, myHash)) { //а вот тут уже высчитан хэш, передадим его чтобы не пересчитывать
		return;
	}


	arr[myHash].push_front(elem);
	realLen++;

}

void HashTable::checkCollisions() const {

	std::cout << "Проверка коллизий...\n";
	for (int i = 0; i < len; i++) {
		if (!arr[i].empty()) {
			std::cout << "Занятая ячейка " << i <<"\n";
			auto current = arr[i].begin();
			auto end = arr[i].end();
			size_t counter = 0;
			std::string collisions;//содержимое ячейки
			while (current != end) {
				if (!counter) {
					collisions.clear();
				}
				collisions += *current + "\n";
				counter++;
				current++;
			}
			if (counter > 1) {
				std::cout << "Коллизия!\n" << collisions; //<< "\n";
			}
		}
	}
}
void HashTable::expandTable() {

	std::cout << "Расширение таблицы!\n";
	size_t oldLen = len;
	for (int i = 0; i < PRIMES_COUNT; i++) {
		if ((PRIMES[i] == oldLen) && (i + 1) < PRIMES_COUNT) {
			len = PRIMES[i + 1]; //за новую длину берем следующее простое число из заданных
			break;
		}
		else if ((i + 1) >= PRIMES_COUNT)
			len += DEFAULT_LEN; //если кончились, что поделать
	}

	realLen = 0; //само пересчитается в insert
	auto oldArr = arr;
	arr = new std::forward_list<std::string>[len];

	for (int i = 0; i < oldLen; i++) {
		if (!oldArr[i].empty()) {
			auto current = oldArr[i].begin();
			auto end = oldArr[i].end();
			while (current != end) {
				insert(*current);
				current++;
			}
		}
	}

	delete[] oldArr;

}

size_t HashTable::getLen() const {
	return len;
}