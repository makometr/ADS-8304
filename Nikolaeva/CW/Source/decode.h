#ifndef DECODE_H
#define DECODE_H

#include <string>
#include <map>

#include "encodetree.h"


namespace decode {
std::string decode (std::map<std::string, char>& charactersCode,
                const std::string& encodedText);

std::string decode (const EncodeTree* tree, const std::string& encodedText);
};

#endif // DECODE_H
