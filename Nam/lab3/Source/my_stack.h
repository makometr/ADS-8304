#pragma once
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

template <typename T>
class Stack
{
public:
	struct Node;
	using NodePtr = std::shared_ptr<Node>;

	struct Node
	{
		Node() = default;

		T data = T();
		NodePtr next = nullptr;
	};

	Stack() = default;
	Stack(int new_size, int arg) : size_(new_size)
	{
		for (int i = 0; i < size_; ++i)
			push(arg);
	}

	Stack(Stack const& other)
	{
		head_ = other.head_;
		size_ = other.size_;
	}

	Stack& operator=(Stack const& other)
	{
		head_ = other.head_;
		size_ = other.size_;

		return *this;
	}

	bool empty()
	{
		return size_ == 0;
	}

	size_t size()
	{
		return size_;
	}

	T front()
	{
		return head_->data;
	}

	void push(T arg)
	{
		auto newElem = std::make_shared<Node>();
		newElem->next = head_;
		newElem->data = arg;
		head_ = newElem;

		++size_;
	}

	void pop()
	{
		if (empty())
			throw std::invalid_argument("Stack is empty");

		head_ = head_->next;

		--size_;
	}

private:
	size_t size_ = 0;
	NodePtr head_ = std::make_shared<Node>();
};