#include <QtTest>
#include <QCoreApplication>

#include "../../Source/BinaryTree/Headers/huffmantree.h"


class TestEncodeHuffman : public QObject
{
    Q_OBJECT

private slots:
    void test_data();
    void test();

};


void TestEncodeHuffman::test_data()
{
    QTest::addColumn <QString> ("text");
    QTest::addColumn <QString> ("encodedText");

    QTest::newRow ("test0") << "a" << "0";

    QTest::newRow ("test1") << "" << "";

    QTest::newRow ("test2") << "aab" << "110";

    QTest::newRow ("test3") << "ЙцЙцйhguytbynihgyjbhjукцУАК" <<
                               "1110011111001111110001101011001010"
                               "10000000010101111011000110100101101"
                               "00000111011001110001011110001001011111";

    QTest::newRow ("test4") << "купавкаыфчяЦВ       "
                               "вцаыкмасв\n" <<
                               "1111111011011110000111111000001"
                               "11001110000000101011101101010101"
                               "010101001101001000001111110110100"
                               "1110000111010";
}


void TestEncodeHuffman::test()
{
    QFETCH (QString, text);
    QFETCH (QString, encodedText);

    HuffmanTree tree;
    QCOMPARE (tree.encodeText(text), encodedText);
}


QTEST_APPLESS_MAIN (TestEncodeHuffman)

#include "tst_testencodehuffman.moc"
