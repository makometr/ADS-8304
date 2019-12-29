#include "../Headers/decode.h"


QString decode::decode(QMap<QString, QChar>& charactersCode,
                       const QString& encodedText)
{
    QString result;
    QString buffer;

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


QString decode::decode(const EncodeTree *tree, const QString &encodedText)
{
    QMap<QString, QChar> charactersCode = tree->getCharactersCode();

    return decode (charactersCode, encodedText);
}
