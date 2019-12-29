#ifndef DECODE_H
#define DECODE_H

#include <QString>
#include <QMap>
#include <QChar>

#include "encodetree.h"


namespace decode {
QString decode (QMap<QString, QChar>& charactersCode,
                const QString& encodedText);

QString decode (const EncodeTree* tree, const QString& encodedText);
};

#endif // DECODE_H
