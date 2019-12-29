#include <QtTest>
#include <QCoreApplication>
#include "../../lab2/hierarchicallist.h"

Q_DECLARE_METATYPE(HierarchicalList::ListPointer);
Q_DECLARE_METATYPE(HierarchicalList::ListPointer *);

class Test_HierarchicalList : public QObject
{
    Q_OBJECT

public:
    Test_HierarchicalList() = default;
    ~Test_HierarchicalList() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void buildListTest_data();
    void buildListTest();
    void reverseListTest_data();
    void reverseListTest();

private:
    HierarchicalList::ListPointer* list_1;
    HierarchicalList::ListPointer* list_2;
    HierarchicalList::ListPointer* list_3;
    HierarchicalList::ListPointer* list_4;
    HierarchicalList::ListPointer* list_5;
    HierarchicalList::ListPointer* list_6;
    HierarchicalList::ListPointer* list_7;
};


void Test_HierarchicalList::initTestCase()
{
    list_1 = new HierarchicalList::ListPointer(new HierarchicalList);
    list_2 = new HierarchicalList::ListPointer(new HierarchicalList);
    list_3 = new HierarchicalList::ListPointer(new HierarchicalList);
    list_4 = new HierarchicalList::ListPointer(new HierarchicalList);
    list_5 = new HierarchicalList::ListPointer(new HierarchicalList);
    list_6 = new HierarchicalList::ListPointer(new HierarchicalList);
    list_7 = new HierarchicalList::ListPointer(new HierarchicalList);
}


void Test_HierarchicalList::buildListTest_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<HierarchicalList::ListPointer>("list");
    QTest::addColumn<bool>("result");

    QTest::newRow("testInit_1") << "qwe()(ad))" << *list_1 << false;
    QTest::newRow("testInit_2") << "(" << *list_2 << false;
    QTest::newRow("testInit_3") << ")" << *list_3 << false;
    QTest::newRow("testInit_4") << "(qwer(sadas)(asfas)sda()" << *list_4 << false;
    QTest::newRow("testInit_5") << "(abc)" << *list_5 << true;
    QTest::newRow("testInit_6") << "(abc(asd)asd)" << *list_6 << true;
    QTest::newRow("testInit_7") << "(abc()(asd)sad)" << *list_7 << true;
}


void Test_HierarchicalList::buildListTest()
{
    QFETCH(QString, input);
    QFETCH(bool, result);
    QFETCH(HierarchicalList::ListPointer, list);

    QCOMPARE(HierarchicalList::buildList(list, input.toStdString()), result);
}


void Test_HierarchicalList::reverseListTest_data()
{
    QTest::addColumn<HierarchicalList::ListPointer>("list");
    QTest::addColumn<QString>("result");

    HierarchicalList::buildList(*list_1, "((qwer()(vddkbk))(ervnvn()ekvnnlkewnvkl(ifuhiuvhi)evenn)wevnjvndn(()()edv))");
    HierarchicalList::buildList(*list_2, "(weq(weq((weq)(weq)(we))egdb)egdb)");
    HierarchicalList::buildList(*list_3, "(qwer)");
    HierarchicalList::buildList(*list_4, "()");
    HierarchicalList::buildList(*list_5, "(((((())))))");

    HierarchicalList::reverseList(*list_1);
    HierarchicalList::reverseList(*list_2);
    HierarchicalList::reverseList(*list_3);
    HierarchicalList::reverseList(*list_4);
    HierarchicalList::reverseList(*list_5);

    QTest::newRow("testReverse_1") << *list_1 << "((vde()())ndnvjnvew(nneve(ihvuihufi)lkvnweklnnvke()nvnvre)((kbkddv)()rewq))";
    QTest::newRow("testReverse_2") << *list_2 << "(bdge(bdge((ew)(qew)(qew))qew)qew)";
    QTest::newRow("testReverse_3") << *list_3 << "(rewq)";
    QTest::newRow("testReverse_4") << *list_4 << "()";
    QTest::newRow("testReverse_5") << *list_5 << "(((((())))))";
}


void Test_HierarchicalList::reverseListTest()
{
    QFETCH(QString, result);
    QFETCH(HierarchicalList::ListPointer, list);


    QCOMPARE(list->toStdString(), result.toStdString());
}


void Test_HierarchicalList::cleanupTestCase()
{
    delete list_1;
    delete list_2;
    delete list_3;
    delete list_4;
    delete list_5;
    delete list_6;
    delete list_7;
}

QTEST_MAIN(Test_HierarchicalList)

#include "tst_test_hierarchicallist.moc"

