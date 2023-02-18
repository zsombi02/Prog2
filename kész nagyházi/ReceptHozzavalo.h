#ifndef RECEPTHOZZAVALO_H
#define RECEPTHOZZAVALO_H

#include "Hozzavalo.h"
#include <ostream>
#include "memtrace.h"


//A receptben a felsoroláshoz létrehoz egy "sor" elemet, azaz mennyiség "_" mért.egys. "_" hozzávaló "_" alakban 
struct ReceptHozzavalo {
public:
    Hozzavalo* hozzavalo;
    double mennyiseg;

    ReceptHozzavalo(Hozzavalo* hozzavalo, double mennyiseg) : hozzavalo(hozzavalo), mennyiseg(mennyiseg) {}
};

//Kiír operátor
std::ostream& operator<<(std::ostream& lhs, ReceptHozzavalo& rhs) {
    lhs << rhs.mennyiseg << ' ' << rhs.hozzavalo->getMertekegyseg() << ' ' << rhs.hozzavalo->getNev() ;
    return lhs;
}

#endif // RECEPTHOZZAVALO_H
