#pragma once
#include "SortsHeader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace sorts;
using StringVector = std::vector<std::string>;

enum class ReturnType
{
	IncorrectStreams,
	IncorrectType,
	IncorrectFileData,
	Correct
};

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

template <typename T, typename FUNC_T>
void sortArr(std::vector<T>& arr, FUNC_T const& cmp)
{
	quickItSort(arr, cmp);
}