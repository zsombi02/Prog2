#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <cstdio>
#include "memtrace.h"

//A láncolt lista egy Template eleme
template<class T>
class Listaelem {
public:
    Listaelem<T>* kov;
    T* ertek;

    Listaelem(T* ertek) : kov(NULL), ertek(ertek) {}

    Listaelem(Listaelem<T>* elozo, T* ertek) : kov(NULL), ertek(ertek) { elozo->kov = this; }
};

//Template Láncolt lista
template<class T>
class Lista {
    Listaelem<T>* elso;
public:
    Lista() : elso(NULL) {}

    Listaelem<T>* elem() { return elso; }

    //Új elem a lista végére
    void hozzaad(T* ertek) {
        if (elso == NULL) {
            elso = new Listaelem<T>(ertek);
        }
        else {
            Listaelem<T>* utolso = elso;
            while (utolso->kov != NULL) {
                utolso = utolso->kov;
            }
            new Listaelem<T>(utolso, ertek);
        }
    }

    //Kitöröl egy keresett elemet
    void torol(T* ertek) {
        if (elso == NULL) {
            return;
        }
        if (elso->ertek == ertek) {
            Listaelem<T>* csere = elso->kov;
            delete elso->ertek;
            delete elso;
            elso = csere;
            return;
        }
        Listaelem<T>* kov = elso->kov;
        Listaelem<T>* csere = elso;
        while (kov != NULL) {
            if (kov->ertek == ertek) {
                delete ertek;
                Listaelem<T>* kovkov = kov->kov;
                delete kov;
                csere->kov = kovkov;
                return;
            }
            csere = kov;
            kov = kov->kov;
        }
    }

    ~Lista() {
        Listaelem<T>* elem = elso;
        if (elso != NULL) {
            while (elem->kov != NULL) {
                Listaelem<T>* kov = elem->kov;
                delete elem->ertek;
                delete elem;
                elem = kov;
            }
            delete elem->ertek;
            delete elem;
        }
        elem = NULL;
    }
};

#endif // LISTA_H