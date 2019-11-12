#include <QtTest>
#include "../lab3/mainwindow.h"

class toInfixTest : public QObject
{
    Q_OBJECT

public:
    toInfixTest() = default;
    ~toInfixTest() = default;

private slots:
    void test_correct_data();
    void test_correct();
    void test_incorrect_data();
    void test_incorrect();

};


void toInfixTest::test_correct_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");

    QTest::newRow("testCorrect_1") << "+ a b" << "a+b";
    QTest::newRow("testCorrect_2") << "* + a b c" << "(a+b)*c";
    QTest::newRow("testCorrect_3") << "^ - * a b + c d 11" << "(a*b-c+d)^11";
    QTest::newRow("testCorrect_4") << "123" << "123";
    QTest::newRow("testCorrect_5") << "- 100 + * h j ^ h j" << "100-h*j+h^j";
}


void toInfixTest::test_correct()
{
    QFETCH(QString, input);
    QFETCH(QString, result);

    QCOMPARE(MainWindow::prefixToInfix(input.toStdString()), result.toStdString());
}


void toInfixTest::test_incorrect_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");

    QTest::newRow("testCorrect_1") << "+ a b b" << "";
    QTest::newRow("testCorrect_2") << "* a b c" << "";
    QTest::newRow("testCorrect_3") << "^ - * a b + c d4 11" << "";
    QTest::newRow("testCorrect_4") << "-" << "";
    QTest::newRow("testCorrect_5") << "- 10d0 + * h j ^ h j" << "";
}


void toInfixTest::test_incorrect()
{
    QFETCH(QString, input);
    QFETCH(QString, result);

    QCOMPARE(MainWindow::prefixToInfix(input.toStdString()), result.toStdString());
}


QTEST_APPLESS_MAIN(toInfixTest)

#include "tst_toinfixtest.moc"
