#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>

template<typename T>
T* resize(T*& old_data, size_t old_size, size_t new_size) {
	T* new_data = new T[new_size];
	for (size_t i = 0; i < std::min(old_size, new_size); i++) {
		new_data[i] = old_data[i];
	}
	delete old_data;

	return new_data;
}

template<typename T>
class vector
{
public:
	vector() = default;

	bool is_empty() const{
		return _veclength == 0;
	}

	void erase(size_t start_erasing_inex, int erasing_length = -1) {
		if (erasing_length == -1) {
			for (size_t i = start_erasing_inex; i < _veclength; i++){
				_data[i] = _data[i + 1];
				}
			_veclength -= (_veclength - start_erasing_inex);
		}
		else {
			for (size_t i = start_erasing_inex; i < start_erasing_inex + erasing_length; i++)
				_data[i] = _data[i + 1];
			_veclength -= erasing_length;
		}
	}

	size_t get_length() const{
		return _veclength;
	}

	void operator+(T &element){
		_veclength++;
		if (_veclength > _vector_allocated_size) {
			size_t allocated_size = 10;
			_data = resize(_data, _vector_allocated_size, _vector_allocated_size + allocated_size);
			_vector_allocated_size += allocated_size;
		}
		_data[_veclength - 1] = element;
	}

	T& operator[](size_t element_index) {
		return _data[element_index];
	}

	friend std::ostream& operator<<(std::ostream& os, const vector<T>& stack) {
		for (size_t i = 0; i < stack.get_length(); i++) {
			os << stack._data[i] << " ";
		}
		return os;
	}

	~vector() {
		delete[] _data;
	}


private:
	T* _data = nullptr;
	size_t _veclength = 0;
	size_t _vector_allocated_size = 0;
};


template<typename T>
class Stack {
public:
	Stack() = default;

	void pop() {
		if (_stack.is_empty())
			throw std::out_of_range("Stack is empty");
		_stack.erase(_stack.get_length() - 1, 1);
	}

	void push(T arguement){
		_stack + arguement;
	}

	T& get_high() {
		if (!_stack.is_empty())
			return _stack[get_length() - 1];
		throw std::out_of_range("Stack is empty");
	}

	bool is_empty() const {
		return _stack.is_empty();
	}

	size_t get_length() const {
		return _stack.get_length();
	}

	friend std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
		return os << stack._stack;
	}

private:
	vector<T> _stack;
};
