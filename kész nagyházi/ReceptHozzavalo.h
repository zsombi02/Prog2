#ifndef RECEPTHOZZAVALO_H
#define RECEPTHOZZAVALO_H

#include "Hozzavalo.h"
#include <ostream>
#include "memtrace.h"


//A receptben a felsorol�shoz l�trehoz egy "sor" elemet, azaz mennyis�g "_" m�rt.egys. "_" hozz�val� "_" alakban 
struct ReceptHozzavalo {
public:
    Hozzavalo* hozzavalo;
    double mennyiseg;

    ReceptHozzavalo(Hozzavalo* hozzavalo, double mennyiseg) : hozzavalo(hozzavalo), mennyiseg(mennyiseg) {}
};

//Ki�r oper�tor
std::ostream& operator<<(std::ostream& lhs, ReceptHozzavalo& rhs) {
    lhs << rhs.mennyiseg << ' ' << rhs.hozzavalo->getMertekegyseg() << ' ' << rhs.hozzavalo->getNev() ;
    return lhs;
}

#endif // RECEPTHOZZAVALO_H
