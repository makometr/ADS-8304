#include <QtTest>
#include <QCoreApplication>

#include "../../Source/BinaryTree/Headers/fanoshannontree.h"


class TestEncodeFanoShannon : public QObject
{
    Q_OBJECT

private slots:
    void test_data();
    void test();
};


void TestEncodeFanoShannon::test_data()
{
    QTest::addColumn <QString> ("text");
    QTest::addColumn <QString> ("encodedText");

    QTest::newRow ("test0") << "a" << "0";

    QTest::newRow ("test1") << "" << "";

    QTest::newRow ("test2") << "aab" << "001";

    QTest::newRow ("test3") << "ЙцЙцйhguytbynihgyjbhjукцУАК" <<
                               "100000010000001101000110011010010"
                               "101100110010101111100001100101001"
                               "110110001011111011111000001110111"
                               "11011111";

    QTest::newRow ("test4") << "купавкаыфчяЦВ       "
                               "вцаыкмасв\n" <<
                               "011101101011100101000110101010101"
                               "1111100011001110101101100000000000"
                               "0001001110001010100111110101011110"
                               "10011111";
}


void TestEncodeFanoShannon::test()
{
    QFETCH (QString, text);
    QFETCH (QString, encodedText);

    FanoShannonTree tree;
    QCOMPARE (tree.encodeText(text), encodedText);
}


QTEST_APPLESS_MAIN (TestEncodeFanoShannon)

#include "tst_testencodefanoshannon.moc"
