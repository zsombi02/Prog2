#ifndef RECEPT_H
#define RECEPT_H

#include "ReceptHozzavalo.h"
#include "Lista.h"
#include <ostream>
#include "memtrace.h"

//Egy recept szerkezete Név "\n" Hozzávalók "\n" elkészítési szöveg és a szükséges idö hozzá
class Recept {
    std::string nev;
    int hossz;
    Lista<ReceptHozzavalo>* hozzavalok;
    std::string szoveg;
    double ido;

public:
    Recept(std::string nev, int hossz, Lista<ReceptHozzavalo>* hozzavalok, std::string szoveg, double ido) : nev(nev), hossz(hossz), hozzavalok(hozzavalok), szoveg(szoveg), ido(ido){};

    std::string getNev() {
        return nev;
    }

    int getHossz() {
        return hossz;
    }

    Lista<ReceptHozzavalo>* getHozzavalok() {
        return hozzavalok;
    }

    std::string getSzoveg() {
        return szoveg;
    }

    double getIdo() {
        return ido;
    }

    ~Recept() {
        delete hozzavalok;
    }
};

//Kiír operátor
std::ostream& operator<<(std::ostream& lhs, Recept& rhs) {
    lhs << rhs.getNev() << std::endl;

    Listaelem<ReceptHozzavalo>* elem = rhs.getHozzavalok()->elem();
    while (elem != NULL) {
        lhs << *elem->ertek << std::endl;
        elem = elem->kov;
    }
    lhs << rhs.getSzoveg() << std::endl;
    lhs << "Elkeszitheto " << rhs.getIdo() << " perc alatt." << std::endl;           //Az idö formátuma még változhat

    return lhs;
}

#endif // RECEPT_H
