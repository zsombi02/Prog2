#ifndef HOZZAVALO_H
#define HOZZAVALO_H

#include <ostream>
#include "memtrace.h"

//Egy hozz�val� �s annak az �ltal�nos m�rt.egys�g�t t�rol� oszt�ly
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