#pragma once
#include <optional>
#include <math.h>
constexpr auto DEFAULT_SIZE = 1<<8;

typedef std::optional<int> nInt;

class Vec_Stack {
private:
	int* stack;
	int index;
	int size;

public:
	Vec_Stack(size_t startSize = DEFAULT_SIZE) {
		stack = new int[startSize];
		size = startSize;
		index = -1;
	}


	Vec_Stack(const Vec_stack &copy) {
		
		stack = new int[copy.size];

		index = copy.index;

		size = copy.size;
		
		std::copy(copy.stack, copy.stack + size, stack);
	}

	Vec_Stack& operator=(const Vec_Stack &assignee) {

		stack = new int[assignee.size];

		index = assignee.index;

		size = assignee.size;
		
		std::copy(assignee.stack, assignee.stack + size, stack);

		return *this;

	}

	void push(int element) {
		
		if (index == (size - 1))
		{
			int* newStack = new int[size + DEFAULT_SIZE];

			std::copy(&stack[0], &stack[size], &newStack[0]);

			delete[] stack;

			stack = newStack;

			size += DEFAULT_SIZE;

			stack[++index] = element;
		}

		else {
			stack[++index] = element;
		}
	}

	nInt pop() {
		if (index == -1)
			return std::nullopt;
		else
			return stack[index--];
	}

	bool isEmpty() {
		return (index == -1);
	}

	nInt top() {
		if (index != -1)
			return stack[index];
		else
			return std::nullopt;
	}

	~Vec_Stack() {
		delete[] stack;
	}
};
