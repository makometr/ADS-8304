#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <algorithm>
enum class TypeCode
{
	TypeInt,
	TypeChar,
	TypeDouble,
	TypeString
};

template<typename T>
struct TransformPair
{
	TransformPair(T newVal, bool newTranformResult) : value(newVal), transformResult(newTranformResult)
	{ }

	T value;
	bool transformResult;
};

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
bool split(std::vector<T>& arr, std::string const& arrStringForm, char separator)
{
	auto startPosition = arrStringForm.begin();
	while (1)
	{
		auto searchResult = std::find(startPosition, arrStringForm.end(), separator);
		if (searchResult == arrStringForm.end())
		{
			TransformPair<T> transformToT = from_string<T>(std::string(startPosition, arrStringForm.end()));
			if (transformToT.transformResult == false)
				return false;

			arr.push_back(transformToT.value);
			return true;
		}
		TransformPair<T> transformToT = from_string<T>(std::string(startPosition, searchResult));
		if (transformToT.transformResult == false)
			return false;

		arr.push_back(transformToT.value);

		startPosition = searchResult + 1;
	}
}


template <typename T, typename F>
void comb(std::vector<T>& arr, F cmp)
{
	int n = 0; // количество перестановок
	double fakt = 1.2473309; // фактор уменьшения
	double step = arr.size() - 1;

	while (step >= 1)
	{
		for (size_t i = 0; i + step < arr.size(); ++i)
		{
			if (cmp(arr[i + static_cast<size_t>(step)], arr[i]))
			{
				std::swap(arr[i + static_cast<size_t>(step)], arr[i]);
				n++;
			}
		}
		step /= fakt;
	}

	for (size_t i = 0; i < arr.size() - 1; i++)
	{
		bool swapped = false;
		for (size_t j = 0; j < arr.size() - i - 1; j++)
		{
			if (cmp(arr[j + 1], arr[j])) {
				std::swap(arr[j], arr[j + 1]);
				swapped = true;
				++n;
			}
		}

		if (!swapped)
			break;
	}
}

template <typename T, typename F>
void bubble(std::vector<T>& arr, F cmp)
{
	for (size_t i = 0; i < arr.size() - 1; i++)
	{
		for (size_t j = 0; j < arr.size() - i - 1; j++)
		{
			if (cmp(arr[j + 1], arr[j])) {
				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
}
