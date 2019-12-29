#include <iostream>
#include <string>
#include "ioManager.h"
#include <istream>
#include "myhashtable.h"

void executeComands(std::istream& input, IoManager& ioManager ,HashTable<std::string>& table);

int main(int argc, char** argv)
{
    HashTable<std::string> table;
    IoManager ioManager(argc, argv);

    std::istream* input = ioManager.nextStream();
    while(input != nullptr)
    {
        executeComands(*input, ioManager, table);

        delete input;
        input = ioManager.nextStream();
    }

    return 0;
}

void executeComands(std::istream& input, IoManager& ioManager, HashTable<std::string>& table)
{
    std::stringstream buf;

    while(input.peek() != EOF)
    {
        std::string word;
        input >> word;

        if(word == "s&d")
        {
            input >> word;

            if(table.search(word))
            {
                table.remove(word);
                buf << word << " - founded and removed" << std::endl;
            }
            else
            {
                buf << word <<" - key not found." << std::endl;
            }
        }
        else
        {
            std::string value;

            input >> value;

            table.insert(word, value);

            buf << "Pair - [" << word << " - " << value << "] - inserted." << std::endl;
        }
    }

    buf << "-----------------Table status!-----------------" << std::endl;
    buf << table.toStr() << std::endl;
    buf << "-----------------------------------------------" << std::endl;

    ioManager.writeLine(buf.str());
}
