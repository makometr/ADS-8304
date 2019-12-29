#include <QtTest>

// add necessary includes here
#include "../hashTableProject/Headers/HashTable.h"
class hashTableTest : public QObject
{
    Q_OBJECT

public:
    hashTableTest();
    ~hashTableTest();

private slots:
    void insertion();
    void deletion();

private:
    HashTable<std::string>* hashTable;

};

hashTableTest::hashTableTest()
{
    hashTable = new HashTable<std::string>;
}

hashTableTest::~hashTableTest()
{
    delete hashTable;
}

void hashTableTest::insertion()
{
    QCOMPARE(hashTable->find("randomstr", hashTable->getLen()), false);
    QCOMPARE(hashTable->insert("str1"), true);
    QCOMPARE(hashTable->find("str1", hashTable->getLen()), true);
    QCOMPARE(hashTable->insert("str1"), false);
    QCOMPARE(hashTable->insert("somestr"), true);
    QCOMPARE(hashTable->insert("Somestr"), true);
}
void hashTableTest::deletion()
{
    QCOMPARE(hashTable->remove("str1"), true);
    QCOMPARE(hashTable->find("str1", hashTable->getLen()), false);
    QCOMPARE(hashTable->remove("str1"), false);
    QCOMPARE(hashTable->remove("str"), false);
    QCOMPARE(hashTable->remove("somestr"), true);
}

QTEST_APPLESS_MAIN(hashTableTest)

#include "tst_hashtabletest.moc"
