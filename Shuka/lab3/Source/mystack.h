#ifndef MYSTACK_H
#define MYSTACK_H

#include <stack>
#include <QDebug>


class MyStack
{
    /*
     * Класс-реализация стека, для перевода выражения из
     * постфиксной формы в инфиксную.
    */

    //перечисления для приоритета операций
    enum optype {power = 3, multiply = 2, minus = 1, plus = 1, null = 0};
    //Элемент стека, состоящий из выражения и приоритета этого выражения
    typedef std::pair<std::string, optype> Node;

public:
    explicit MyStack();
    ~MyStack();

    //Запрет конструктора копирования и оператора присваивания
    MyStack& operator=(const MyStack& list) = delete;
    MyStack(const MyStack& list) = delete;

    //Стандартные методы для работы со стеком
    void pop();
    void push(const Node elem);
    bool isEmpty() const;
    Node top() const;
    size_t size() const;

    //Статический метод для преобразования выражения с помощью стека
    static std::string toInfix(const std::string& expression);

private:
    //статические методы для проверки на корректность символов
    static bool isDigit(const char ch);
    static bool isAlpha(const char ch);
    static bool isSign(const char ch);

private:
    Node elem;
    MyStack* topElem;
    size_t sizeStack;
};

#endif // MYSTACK_H
