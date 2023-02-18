#ifndef HOZZAVALO_H
#define HOZZAVALO_H

#include <ostream>
#include "memtrace.h"

//Egy hozzávaló és annak az általános mért.egységét tároló osztály
class Hozzavalo {
    std::string nev;
    std::string mertekegyseg;

public:
    Hozzavalo(std::string nev, std::string mertekegyseg) : nev(nev), mertekegyseg(mertekegyseg) {};
    
    std::string getNev() {
        return nev;
    }

    std::string getMertekegyseg() {
        return mertekegyseg;
    }

};


#endif // HOZZAVALO_H