#include "mystack.h"

MyStack::MyStack()
{
    topElem = nullptr;
    sizeStack = 0;
}


MyStack::~MyStack()
{
    if (topElem != nullptr)
        delete topElem;
}


void MyStack::pop()
{
    /*
     * Удаление верхнего элемента из стека
    */
    if (topElem != nullptr) {
        MyStack* oldTopElem = topElem;
        topElem = oldTopElem->topElem;
        sizeStack -= 1;
        oldTopElem->topElem = nullptr;
        delete oldTopElem;
    }
    else {
        qDebug() << "Error: stack is empty";
    }
}


void MyStack::push(const Node elem)
{
    /*
     * Добавление элемента в стек
    */

    MyStack* tmp = topElem;
    topElem = new MyStack;
    topElem->elem = elem;
    sizeStack += 1;
    topElem->topElem = tmp;
}


bool MyStack::isEmpty() const
{
    /*
     * Проверка стека на пустоту
    */

    return topElem == nullptr;
}


MyStack::Node MyStack::top() const
{
    /*
     * Доступ к верхнему элементу стека
    */
    if (topElem != nullptr) {
        return topElem->elem;
    }
    else {
        qDebug() << "Error: stack is empty!";
        return Node("", null);
    }
}


size_t MyStack::size() const
{
    /*
     * Получение размера стека
    */

    return sizeStack;
}


std::string MyStack::toInfix(const std::string &expression)
{
    /*
     * Статический метод класса, для преобразования выражения,
     * заданного в постфиксной форме, в инфиксную.
     *
     * Принимает на вход константную ссылку на строку-выражение, возвращает
     * выражение в инфиксной форме, если исходное выражение корректно и пустую
     * строку в случае ошибки.
     *
     * Строка анализируется посимвольно. Если текущий символ "число или буква", тогда
     * элемент помещается в стек с приоритетом 0, если текущий символ "знак операции",
     * из стека достаются два элемента, записываются в временную строку с учетом приоритетов
     * операций и временная строка помещается в стек с приоритетом знака.
     *
     * В ходе преобразования, если стек пустой, выводится ошибка и возвращается пустая
     * строка. После преобразования в стеке должен находиться один элемент - инфиксное выражение.
    */

    MyStack *stack = new MyStack;

    std::string tmpStr = "";

    for (auto i = expression.cbegin(); i < expression.end(); ++i) {
        char elem = *i;
        if (elem == ' ') {
            continue;
        }
        else if (isDigit(elem) || isAlpha(elem)) {
            while (elem != ' ') {
                tmpStr += elem;
                ++i;
                elem = *i;
            }
            stack->push(Node(tmpStr, optype::null));

            qDebug() << "В стек помещается элемент:" << elem;
        }
        else if (isSign(elem)) {
            Node firstArg;
            Node secondArg;

            qDebug() << "Знак оперции:" << elem;

            if (!stack->isEmpty()) {
                secondArg = stack->top();
                stack->pop();
            }
            else {
                qDebug() << "Error: stack is empty!";
                return "";
            }

            if (!stack->isEmpty()) {
                firstArg = stack->top();
                stack->pop();
            }
            else {
                qDebug() << "Error: stack is empty!";
                return "";
            }

            qDebug() << "Выражения в стеке: " << firstArg.first.c_str() <<
                        "и" << secondArg.first.c_str();

            optype tmpOptype = optype::null;
            if (elem == '+') {
                tmpOptype = optype::plus;
            } else if (elem == '-') {
                tmpOptype = optype::minus;
            } else if (elem == '*') {
                tmpOptype = optype::multiply;
            } else if (elem == '^') {
                tmpOptype = optype::power;
            }

            if (firstArg.second != optype::null && firstArg.second < tmpOptype) {
                tmpStr += '(';
                tmpStr += firstArg.first;
                tmpStr += ')';
            } else {
                tmpStr += firstArg.first;
            }

            tmpStr += elem;

            if (secondArg.second != optype::null && secondArg.second < tmpOptype) {
                tmpStr += '(';
                tmpStr += secondArg.first;
                tmpStr += ')';
            } else {
                tmpStr += secondArg.first;
            }

            qDebug() << "Итоговое выражение помещается в стек:" << tmpStr.c_str();

            stack->push(Node(tmpStr, tmpOptype));
        }
        else {
            qDebug() << "Некорректный символ в строке!";
            return "";
        }
        tmpStr = "";
    }
    if (stack->size() == 1) {
        tmpStr = stack->top().first;
        stack->pop();
        delete stack;
        return tmpStr;
    }
    else {
        delete stack;
        qDebug() << "Error: string is incorrect!";
        return "";
    }
}


bool MyStack::isDigit(const char ch)
{
    /*
     * Проверка на цифру
    */

    return (ch >= '0' && ch <= '9');
}


bool MyStack::isAlpha(const char ch)
{
    /*
     * Проверка на букву
    */

    return ((ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z'));
}


bool MyStack::isSign(const char ch)
{
    /*
     * Проверка на знак
    */

    return (ch == '+' || ch == '-' ||
            ch == '*' || ch == '^');
}
