#ifndef ATOM_H
#define ATOM_H

#include <memory>
#include "data.h"
#include "types.h"
#include "string"

class Atom: public Data
{
private:
    AtomType type_ = AtomType::UNKNOWN;
    std::string valueStr_ = "";
public:
    typedef std::shared_ptr<Atom> AtomP;

    explicit Atom(std::string value);
    Atom(const Atom& atom);
    AtomType type();
    std::string value();
};

#endif // ATOM_H
