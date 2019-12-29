#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "myhashtable.h"

int main()
{
    std::mt19937 randomGen(static_cast<unsigned>(time(nullptr)));
    HashTable<int> table;
    int testsCount = 512;

    for(int k = 0; k < 8; k++){
        clock_t clocks = 0;
        float time = 0;
        float averageTime = 0;

        table.clear();

        for(int i = 0; i < testsCount; i++)
        {
            long long int key = randomGen();
            int value = static_cast<int>(randomGen());

            clocks = clock();

            table.insert(key, value);

            clocks = clock() - clocks;
            time += static_cast<float>(clocks) / CLOCKS_PER_SEC;
        }
        averageTime = time * 1000 / testsCount;

        std::cout << "Elements - " << testsCount << " Average case insertion - " << averageTime << " ms" << std::endl;

        clocks = 0;
        time = 0;
        averageTime = 0;

        table.clear();

        long long int base = 1;
        while(base <= testsCount)
        {
            base <<= 1;
        }

        for(int i = 0; i < testsCount; i++)
        {
            long long int key = (i + 1) * base;
            int value = static_cast<int>(randomGen());

            clocks = clock();

            table.insert(key, value);

            clocks = clock() - clocks;
            time += static_cast<float>(clocks) / CLOCKS_PER_SEC;
        }
        averageTime = time * 1000 / testsCount;

        std::cout << "Elements - " << testsCount << " Bad case insertion - " << averageTime << " ms" << std::endl << std::endl;
        averageTime = 0;

        testsCount *= 2;
    }

    return 0;
}

