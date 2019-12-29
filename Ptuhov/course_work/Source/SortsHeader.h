#include <vector>
#include <stack>
#include <algorithm>
#include <time.h>
#include <memory>
#include <fstream>


namespace sorts
{
	template <typename T>
	std::vector<T> operator+=(std::vector<T>& left, std::vector<T> const& right)
	{
		for (auto i : right)
			left.push_back(i);

		return left;
	}

	template<typename T, typename FUNC_T>
	void quickRecSort(std::vector<T>& arr, FUNC_T const& cmp, std::ostream& out, int n = 0)
	{
		if (arr.size() <= 1)
			return;

		std::vector<T> smaller;
		std::vector<T> bigger;
		std::vector<T> equal;
		T supportingElement = arr[arr.size() / 2];

		for (auto i : arr)
		{
			if (i == supportingElement)
				equal.push_back(i);
			else if (cmp(supportingElement, i))
				bigger.push_back(i);
			else
				smaller.push_back(i);
		}


		//отладочные выводы
		out << "Formed bigger, equal and smaller arrays for stage №" + std::to_string(n) + ":\n";

		for (auto i : arr)
			out << i << ' ';
		out << "\nBig:\n";

		if (bigger.empty())
			out << "Empty";
		else
		{
			for (auto i : bigger)
				out << i << ' ';
		}
		out << "\nEqual:\n";

		for (auto i : equal)
			out << i << ' ';
		out << "\nSmall:\n";

		if (smaller.empty())
			out << "Empty";
		else
		{
			for (auto i : smaller)
				out << i << ' ';
		}
		out << "\n";
		//

		quickRecSort(smaller, cmp, out, ++n);
		quickRecSort(bigger, cmp, out, ++n);

		smaller += equal;
		smaller += bigger;
		arr = std::move(smaller);
	}

	template<typename T, typename FUNC_T>
	void mergeRecSort(std::vector<T>& arr, FUNC_T const& cmp)
	{
		if (arr.size() <= 1)
			return;

		std::vector<T> leftPart(arr.begin(), arr.begin() + arr.size() / 2);
		std::vector<T> rightPart(arr.begin() + arr.size() / 2, arr.end());

		mergeRecSort(leftPart, cmp);
		mergeRecSort(rightPart, cmp);

		std::vector<T> result;
		size_t leftArrIndex = 0;
		size_t rightArrIndex = 0;

		while (leftArrIndex < leftPart.size() && rightArrIndex < rightPart.size())
		{
			if (cmp(leftPart[leftArrIndex], rightPart[rightArrIndex]))
			{
				result.push_back(leftPart[leftArrIndex]);
				leftArrIndex++;
			}
			else
			{
				result.push_back(rightPart[rightArrIndex]);
				rightArrIndex++;
			}
		}

		while (leftArrIndex < leftPart.size())
		{
			result.push_back(leftPart[leftArrIndex]);
			leftArrIndex++;
		}

		while (rightArrIndex < rightPart.size())
		{
			result.push_back(rightPart[rightArrIndex]);
			rightArrIndex++;
		}

		arr = std::move(result);
	}

	template<typename T, typename FUNC_T>
	void mergeItSort(std::vector<T>& arr, FUNC_T const& cmp)
	{
		for (size_t currenttBlockSize = 1; currenttBlockSize < arr.size(); currenttBlockSize *= 2)
		{
			for (size_t blockBorder = 0; blockBorder < arr.size() - currenttBlockSize; blockBorder += 2 * currenttBlockSize)
			{
				size_t leftBorder = blockBorder;
				size_t middleBorder = leftBorder + currenttBlockSize;
				size_t rightBorder = (middleBorder + currenttBlockSize < arr.size()) ? middleBorder + currenttBlockSize : arr.size();
				std::vector<T> sortedBlock;

				size_t leftArrIndex = 0;
				size_t rightArrIndex = 0;
				while (leftBorder + leftArrIndex < middleBorder && middleBorder + rightArrIndex < rightBorder)
				{
					T currentLeftArrElement = arr[leftBorder + leftArrIndex];
					T currentRightArrELement = arr[middleBorder + rightArrIndex];

					if (cmp(currentLeftArrElement, currentRightArrELement))
					{
						sortedBlock.push_back(currentLeftArrElement);
						leftArrIndex++;
					}
					else
					{
						sortedBlock.push_back(currentRightArrELement);
						rightArrIndex++;
					}
				}

				while (leftBorder + leftArrIndex < middleBorder)
				{
					sortedBlock.push_back(arr[leftBorder + leftArrIndex]);
					leftArrIndex++;
				}

				while (middleBorder + rightArrIndex < rightBorder)
				{
					sortedBlock.push_back(arr[middleBorder + rightArrIndex]);
					rightArrIndex++;
				}

				for (size_t insertIndex = leftBorder; insertIndex < rightBorder; insertIndex++)
				{
					arr[insertIndex] = sortedBlock[insertIndex - leftBorder];
				}
			}
		}
	}

	template<typename T, typename FUNC_T>
	void quickItSort(std::vector<T>& arr, FUNC_T const& cmp)
	{
		std::stack<int> indexStack;
		indexStack.push(arr.size() - 1);
		indexStack.push(0);

		int leftBorder = 0;
		int rightBorder = 0;
		int leftIndex = 0;
		int rightIndex = 0;

		do
		{
			leftBorder = indexStack.top();
			indexStack.pop();
			rightBorder = indexStack.top();
			indexStack.pop();

			if (arr[leftBorder] > arr[rightBorder])
			{
				std::swap(arr[leftBorder], arr[rightBorder]);
			}
			else
			{
				T supportingElement = arr[arr.size() / 2];

				leftIndex = leftBorder;
				rightIndex = rightBorder;
				do
				{
					while (supportingElement > arr[leftIndex])
						leftIndex++;

					while (arr[rightIndex] > supportingElement)
						rightIndex--;

					if (leftIndex <= rightIndex)
					{
						std::swap(arr[leftIndex], arr[rightIndex]);
						leftIndex++;
						rightIndex--;
					}

				} while (leftIndex <= rightIndex);
			}

			if (leftBorder < rightIndex)
			{
				indexStack.push(rightIndex);
				indexStack.push(leftBorder);
			}

			if (leftIndex < rightBorder)
			{
				indexStack.push(rightBorder);
				indexStack.push(leftIndex);
			}

		} while (!indexStack.empty());
	}
}
