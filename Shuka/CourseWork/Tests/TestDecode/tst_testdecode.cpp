#include <QtTest>
#include <QMap>
#include <QString>
#include <QCoreApplication>

#include "../../Source/BinaryTree/Headers/decode.h"


typedef  QMap <QString, QChar> myMap;


class TestDecode : public QObject
{
    Q_OBJECT

private slots:
    void test_data();
    void test();
};


void TestDecode::test_data()
{
    QTest::addColumn<myMap> ("map");
    QTest::addColumn<QString> ("encodedText");
    QTest::addColumn<QString> ("result");

    QTest::newRow ("test0") << myMap ({std::make_pair ("0", 'a')}) <<
                               "000" << "aaa";

    QTest::newRow ("test1") << myMap() << "" << "";

    QTest::newRow ("test2") << myMap ({std::make_pair ("0", 'a'),
                                       std::make_pair ("10", 'b'),
                                       std::make_pair ("11", 'c')}) <<
                               "010111011" << "abcbc";

    QTest::newRow ("test3") << myMap({std::make_pair ("0", 'q'),
                                      std::make_pair ("11", 'w'),
                                      std::make_pair ("100", 'r'),
                                      std::make_pair ("101", 'e')}) <<
                               "00111001011111110001100101" <<
                               "qqwrewwwqqqwqqe";

    QTest::newRow ("test4") << myMap({std::make_pair ("00", L'к'),
                                      std::make_pair ("010", L'с'),
                                      std::make_pair ("011", L'м'),
                                      std::make_pair ("10", L'п'),
                                      std::make_pair ("111", L'а'),
                                      std::make_pair ("1100", L'П'),
                                      std::make_pair ("1101", L'г')}) <<
                               "110011011001100001111111010010" <<
                               "Пгпмккааппс";

    /*QTest::newRow ("test5") << myMap ({std::make_pair ("00", 'a'),
                                       std::make_pair ("01", 'b')}) <<
                               "111111" << "";*/
}


void TestDecode::test()
{
    QFETCH (myMap, map);
    QFETCH (QString, encodedText);
    QFETCH (QString, result);

    QCOMPARE (decode::decode (map, encodedText), result);
}


QTEST_APPLESS_MAIN (TestDecode)

#include "tst_testdecode.moc"
