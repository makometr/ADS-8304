#include <iostream>
#include <exception>
#include <sstream>
#include <tuple>
#include <algorithm>

template<typename T>
class ArrayQueue {
public:
    ArrayQueue(size_t growSize = 128) {
        setGrowSize(growSize);
    }
    ArrayQueue(const ArrayQueue &other) {
        *this = other;
    }
    virtual ~ArrayQueue() {
        delete[] m_array;
    }

    ArrayQueue &operator=(const ArrayQueue &other) {
        if (this == &other)
            return *this;

        clear();

        std::tie(m_array, m_arraySize) = other.elementsCopy(m_array);
        m_toPush = other.length();
        m_toPop = 0;
        m_growSize = other.m_growSize;
    }

    void setGrowSize(size_t growSize) {
        if (growSize == 0)
            throw std::invalid_argument("The grow size must be greater than 0.");
        m_growSize = growSize;
    }
    size_t getGrowSize() const {
        return m_growSize;
    }

    void push(const T& value) {
        if (m_arraySize <= length() + 1)
            reallocate(m_growSize);

        m_array[m_toPush] = value;

        ++m_toPush;
        if (m_toPush >= m_arraySize)
            m_toPush = 0;
    }

    void pop() {
        if (isEmpty())
            return;

        ++m_toPop;
        if (m_toPop >= m_arraySize)
            m_toPop = 0;

        if (m_arraySize >= length() + 1 + m_growSize)
            reallocate();
    }

    const T &front() const {
        if (isEmpty())
            throw std::runtime_error("Calling \"front\" on the empty ArrayQueue.");
        return m_array[m_toPop];
    }

    size_t length() const {
        if (m_toPop <= m_toPush)
            return m_toPush - m_toPop;
        else
            return (m_arraySize - m_toPop) + m_toPush;
    }

    bool isEmpty() const {
        return m_toPush == m_toPop;
    }

    void clear() {
        delete[] m_array;
        m_arraySize = 0;
        m_toPush = 0;
        m_toPop = 0;
    }

private:
    [[nodiscard]] std::pair<T *, size_t> elementsCopy(size_t extraSpace = 0) {
        auto arraySize = length() + 1 + extraSpace;
        auto array = new T[arraySize];


        if (m_toPop <= m_toPush) {
            size_t j = 0;
            for (size_t i = m_toPop; i < m_toPush; ++i) {
                array[j] = m_array[i];
                ++j;
            }
        } else {
            size_t j = 0;
            for (size_t i = m_toPop; i < m_arraySize; ++i) {
                array[j] = m_array[i];
                ++j;
            }
            for (size_t i = 0; i < m_toPush; ++i) {
                array[j] = m_array[i];
                ++j;
            }
        }
        return {array, arraySize};
    }

    void reallocate(size_t extraSpace = 0) {
        auto [newArray, newArraySize] = elementsCopy(extraSpace);
        auto newToPush = length();

        delete[] m_array;
        m_array = newArray;
        m_arraySize = newArraySize;
        m_toPop = 0;
        m_toPush = newToPush;
    }

    T *m_array = nullptr;
    size_t m_arraySize = 0;
    size_t m_toPush = 0;
    size_t m_toPop = 0;
    size_t m_growSize;
};

int main()
{
    std::istringstream stream;
    std::string buffer;
    auto rightTrim = [](std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    };
    auto readLine = [&stream, &buffer, rightTrim] {
        getline(std::cin, buffer);
        rightTrim(buffer);
        stream.str(buffer);
        stream.seekg(0);
    };

    int leftBorder = 0;
    int rightBorder = 0;

    stream.exceptions(std::ios_base::failbit);
    try {
        std::cout << "Enter left border: ";
        readLine();
        stream >> leftBorder;
        std::cout << "Enter right border: ";
        readLine();
        stream >> rightBorder;
    } catch (std::ios_base::failure &) {
        std::cerr << "Error: You should enter a number." << std::endl;
        return EXIT_FAILURE;
    }
    stream.exceptions(std::ios_base::goodbit);

    if (leftBorder > rightBorder)
        std::swap(leftBorder, rightBorder);

    auto const growSize = 2; // 2 for the good testing.
    ArrayQueue<int> lessThanLeft(growSize);
    ArrayQueue<int> insideLeftAndRight(growSize);
    ArrayQueue<int> greaterThanRight(growSize);

    std::cout << "Enter numbers: ";
    readLine();
    while (stream.good()) {
        int number = 0;

        stream >> number;
        if (stream.rdstate() & std::ios_base::failbit) {
            std::cerr << "Error: You should enter numbers." << std::endl;
            return EXIT_FAILURE;
        }

        if (number < leftBorder)
            lessThanLeft.push(number);
        else if (number > rightBorder)
            greaterThanRight.push(number);
        else
            insideLeftAndRight.push(number);
    }

    auto queueToString = [](ArrayQueue<int> &queue) {
        std::string result;
        while (!queue.isEmpty()) {
            result += std::to_string(queue.front()) + ' ';
            queue.pop();
        }
        return result;
    };

    auto result = queueToString(lessThanLeft) +
            queueToString(insideLeftAndRight) +
            queueToString(greaterThanRight);
    rightTrim(result);
    std::cout << "Result: " << result << std::endl;

    return EXIT_SUCCESS;
}

