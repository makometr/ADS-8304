#include <iostream>
#include "parser.h"
#include "listhandler.h"
#include "ioManager.h"

using namespace std;

int main(int argc, char** argv)
{
    List::ListP list;
    List::ListP simlifyedList;
    Parser parser;
    ListHandler listHandler;
    IoManager ioManager(argc, argv);

    istream* curStream = ioManager.nextStream();
    while(curStream)
    {
        list = parser.parse(*curStream);

        simlifyedList = listHandler.simplify(*list);

        std::cout << std::endl;

        std::string buf;

        buf = list->toString() + " |is equal to| " + simlifyedList->toString();

        ioManager.writeLine(buf);

        delete curStream;

        curStream = ioManager.nextStream();
    }
	
	std::cin.get();

    return 0;
}
