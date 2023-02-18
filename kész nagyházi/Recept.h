#ifndef RECEPT_H
#define RECEPT_H

#include "ReceptHozzavalo.h"
#include "Lista.h"
#include <ostream>
#include "memtrace.h"

//Egy recept szerkezete N�v "\n" Hozz�val�k "\n" elk�sz�t�si sz�veg �s a sz�ks�ges id� hozz�
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

//Ki�r oper�tor
std::ostream& operator<<(std::ostream& lhs, Recept& rhs) {
    lhs << rhs.getNev() << std::endl;

    Listaelem<ReceptHozzavalo>* elem = rhs.getHozzavalok()->elem();
    while (elem != NULL) {
        lhs << *elem->ertek << std::endl;
        elem = elem->kov;
    }
    lhs << rhs.getSzoveg() << std::endl;
    lhs << "Elkeszitheto " << rhs.getIdo() << " perc alatt." << std::endl;           //Az id� form�tuma m�g v�ltozhat

    return lhs;
}

#endif // RECEPT_H
