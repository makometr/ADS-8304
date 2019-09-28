#pragma once
#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <map>

using stringIteratorsPair = std::pair<std::string::iterator, std::string::iterator>;

namespace vecqu
{
	template <typename T>
	T* resize(T*& data, size_t old_size, size_t new_size)
	{
		T* new_data = new T[new_size];
		for (size_t i = 0; i < old_size; i++)
			new_data[i] = data[i];
		delete[] data;

		return new_data;
	}

	template <typename T>
	class Vector
	{
	public:
		Vector() = default;

		Vector(size_t size) : size_(0), capacity_(size), data_(new T[size])
		{ }

		~Vector()
		{
			delete[] data_;
		}

		void erase(size_t eraseInd)
		{
			for (size_t i = eraseInd; i < size_; i++)
				data_[i] = data_[i + 1];
			size_--;
		}

		T front() const
		{
			return *data_;
		}

		size_t size() const
		{
			return size_;
		}

		void push_back(T const& pushArg)
		{
			size_++;
			if (size_ >= capacity_)
			{
				data_ = resize(data_, capacity_, capacity_ + 10);
				capacity_ += 10;
			}

			data_[size_ - 1] = pushArg;
		}

		bool empty() const
		{
			return size_ == 0;
		}

		T operator[](size_t ind) const
		{
			return data_[ind];
		}

		T& operator[](size_t ind)
		{
			return data_[ind];
		}

	private:
		T* data_ = nullptr;
		size_t size_ = 0;
		size_t capacity_ = 0;
	};

	template <typename T>
	class Queue
	{
	public:
		Queue() = default;

		void push(T const& pushArg)
		{
			queue_.push_back(pushArg);
		}

		void pop()
		{
			if (queue_.empty())
				throw std::out_of_range("Queue is empty!");

			queue_.erase(0);
		}

		T front() const
		{
			return queue_.front();
		}

		bool empty() const
		{
			return queue_.empty();
		}

		size_t size() const
		{
			return queue_.size();
		}

	private:
		Vector<T> queue_;
	};
}
