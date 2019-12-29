#include "decode.h"


std::string decode::decode(std::map<std::string, char>& charactersCode,
                       const std::string& encodedText)
{
   std::string result;
   std::string buffer;

    for (auto elem : encodedText) {
        if (elem != '0' && elem != '1') {
            return "";
        }

        buffer += elem;

        if (charactersCode.find(buffer) != charactersCode.end()) {
            result += charactersCode[buffer];
            buffer.clear();
        }
    }
    return result;
}


std::string decode::decode(const EncodeTree *tree, const std::string &encodedText)
{
    std::map<std::string, char> charactersCode = tree->getCharactersCode();

    return decode (charactersCode, encodedText);
}
