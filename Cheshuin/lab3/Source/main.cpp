#include <iostream>
#include <string>
#include "ioManager.h"
#include "validator.h"


int main(int argc, char** argv)
{
    IoManager ioManager(argc, argv);
    Validator validator;
    std::string result;

    std::istream* stream = ioManager.nextStream();
    while(stream != nullptr)
    {
        std::getline(*stream, result);
        stream->seekg(0);

        int error = validator.check(*stream);

        if(error == Validator::VALID)
        {
            result +=  " | Text is valid";
        }
        else
        {
            result += " | Error in " + std::to_string(error) + " character.";
        }

        ioManager.writeLine(result);

        delete stream;
        stream = ioManager.nextStream();
    }

    return 0;
}
