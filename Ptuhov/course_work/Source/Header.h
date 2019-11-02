#pragma once
#include "SortsHeader.h"
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>

using namespace sorts;
using StringVector = std::vector<std::string>;

//возможные коды завершения ф-ий
enum class ReturnType
{
	IncorrectStreams,
	IncorrectType,
	IncorrectFileData,
	Correct
};

//возможные типы данных хранящихся в массивах
enum class TypeCode
{
	TypeInt,
	TypeChar,
	TypeDouble,
	TypeString
};

// данная структура содержит данные о трансформации некоторой строки s 
// в тип T если трансформация прошла успешно, то transformResult = true
template<typename T>
struct TransformPair
{
	TransformPair(T newVal, bool newTranformResult) : value(newVal), transformResult(newTranformResult)
	{ }

	T value;
	bool transformResult;
};

void readFileData(std::ifstream&, StringVector&);
ReturnType streamsCheck(std::ifstream&, std::ofstream&);
TypeCode determineType(std::string const&);

// данная шаблонная функция пытается превратить переданную строку в шаблонный тип
// результат работы функции хранится в переменная transformResult
template <typename T>
TransformPair<T> from_string(std::string const& checkString)
{
	T value;
	std::istringstream stream(checkString);
	stream >> value;

	if (stream.fail() || stream.peek() != EOF)
		return TransformPair<T>(value, false);

	return TransformPair<T>(value, true);
}

// данная шаблонная функция формирует из строкового представления массива сам массив
// путем последовательного преобразования каждого из эл-ов массива к переданному шаблонному типу
template <typename T>
ReturnType reformArr(std::vector<T>& arr, std::string const& arrStringForm)
{
	auto startPosition = arrStringForm.begin();
	while (1)
	{
		auto searchResult = std::find(startPosition, arrStringForm.end(), ' ');
		if (searchResult == arrStringForm.end())
		{
			TransformPair<T> transformToT = from_string<T>(std::string(startPosition, arrStringForm.end()));
			if (transformToT.transformResult == false)
				return ReturnType::IncorrectFileData;

			arr.push_back(transformToT.value);
			return ReturnType::Correct;
		}
		TransformPair<T> transformToT = from_string<T>(std::string(startPosition, searchResult));
		if (transformToT.transformResult == false)
			return ReturnType::IncorrectFileData;

		arr.push_back(transformToT.value);

		startPosition = searchResult + 1;
	}
}

template <typename T>
ReturnType formArr(std::vector<T>& arr, std::string const& arrStringForm)
{
	ReturnType reformingResult = reformArr(arr, arrStringForm);
	if (reformingResult == ReturnType::IncorrectFileData)
		return ReturnType::IncorrectFileData;

	return ReturnType::Correct;
}


template<typename T>
void chooseSortVariant(int sortChoise, std::vector<T>& arr, std::ostream& out)
{
	auto cmp = [](auto a, auto b) {return a < b; };

	auto start = std::chrono::system_clock::now();
	switch (sortChoise)
	{
	case 1:
		mergeItSort(arr, cmp);
		break;
	case 2:
		mergeRecSort(arr, cmp);
		break;
	case 3:
		quickItSort(arr, cmp);
		break;
	default:
		quickRecSort(arr, cmp, out);
		break;
	}
	auto end = std::chrono::system_clock::now();
	out << "Sort time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds\n\n";
}