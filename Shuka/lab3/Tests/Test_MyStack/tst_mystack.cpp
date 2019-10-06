#include <QtTest>
#include <QCoreApplication>
#include <string>
#include "../../lab3/mystack.h"
#include "../../lab3/mainwindow.h"


class Test_MyStack : public QObject
{
    Q_OBJECT

public:
    Test_MyStack();
    ~Test_MyStack();

private slots:
    void test_correct();
    void test_incorrect();

    void test_correct_data();
    void test_incorrect_data();

private:
    MyStack* stack;
};


void Test_MyStack::test_correct_data()
{
    QTest::addColumn<QString>("expression");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_correct_1") << "d" << "d";
    QTest::newRow("test_correct_2") << "a b +" << "a+b";
    QTest::newRow("test_correct_3") << "1 2 3 + *" << "1*(2+3)";
    QTest::newRow("test_correct_4") << "2 3 4 5 + * +" << "2+3*(4+5)";
    QTest::newRow("test_correct_5") << "1 2 3 4 5 + + * +" << "1+2*(3+4+5)";
    QTest::newRow("test_correct_6") << "1 2 * 3 +" << "1*2+3";
    QTest::newRow("test_correct_7") << "a 2 3 4 ^ - *" << "a*(2-3^4)";
    QTest::newRow("test_correct_8") << "r t + y * 12 ^" << "((r+t)*y)^12";
}


Test_MyStack::Test_MyStack()
{
    stack = new MyStack;
}


Test_MyStack::~Test_MyStack()
{
    delete stack;
}


void Test_MyStack::test_correct()
{
    QFETCH(QString, expression);
    QFETCH(QString, result);
    QCOMPARE(MainWindow::toInfix(stack, expression.toStdString()), result.toStdString());
}


void Test_MyStack::test_incorrect_data()
{
    QTest::addColumn<QString>("expression");
    QTest::addColumn<QString>("result");

    QTest::newRow("test_incorrect_1") << "a b" << "";
    QTest::newRow("test_incorrect_2") << "" << "";
    QTest::newRow("test_incorrect_3") << "12 * 1" << "";
    QTest::newRow("test_incorrect_4") << "+" << "";
    QTest::newRow("test_incorrect_5") << "1 1 1 +" << "";
    QTest::newRow("test_incorrect_6") << "a1" << "";
    QTest::newRow("test_incorrect_7") << "1 2 + aaa +" << "";
}


void Test_MyStack::test_incorrect()
{
    QFETCH(QString, expression);
    QFETCH(QString, result);
    QCOMPARE(MainWindow::toInfix(stack, expression.toStdString()), result.toStdString());
}


QTEST_MAIN(Test_MyStack)

#include "tst_mystack.moc"
