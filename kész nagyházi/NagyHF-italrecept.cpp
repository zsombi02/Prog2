#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string>
#include <fstream>

#include "Hozzavalo.h"
#include "ReceptHozzavalo.h"
#include "Recept.h"
#include "Lista.h"
#include "memtrace.h"
#define TEST



//Az int és double utáni \n eltárolására
template <typename T> T readT(std::istream& lhs) {
    T result;
    if (!(lhs >> result)) {
        lhs.clear();
        result = -1;
        //lhs.ignore(32767, '\n');                                              // Jportához át kell írni.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        //std::cout << "Nem jo a bemenet! ";
    }
    std::string skip;
    std::getline(lhs, skip);
    return result;
}

//Fileból olvasás
void beolvas(Lista<Hozzavalo>& hozzavalok, Lista<Recept>& receptek) {
    std::ifstream hozzavalo("Hozzavalok.txt");
    std::ifstream recept("Receptek.txt");

    if (hozzavalo.is_open() && recept.is_open()) {

        //A hozzávalók változó feltöltése
        int hosszusag = 0;
        hosszusag = readT<int>(hozzavalo);
        std::string tag_egy;
        std::string tag_ketto;

        while (hosszusag != 0) {
            std::getline(hozzavalo, tag_egy);
            std::getline(hozzavalo, tag_ketto);
            Hozzavalo* uj = new Hozzavalo(tag_egy, tag_ketto);
            hozzavalok.hozzaad(uj);
            hosszusag--;
        }

        //A receptek változó feltöltése
            //A receptek nevének beolvasása

        std::string Rec_nev;
        int hossz;
        std::string Hoz_nev;
        std::string Hoz_mert_egys;
        double Hoz_menny;
        std::string Rec_szoveg;
        double Rec_ido;
        hosszusag = readT<int>(recept);
        while (hosszusag != 0) {
            Lista<ReceptHozzavalo>* ujtag = new Lista<ReceptHozzavalo>();

            std::getline(recept, Rec_nev);
                //A hozzávalók listáinak beolvasása
            hossz = readT<int>(recept);
            int iter = hossz;
            while (iter != 0) {
                std::getline(recept, Hoz_nev);
                std::getline(recept, Hoz_mert_egys);
                Hoz_menny = readT<double>(recept);
                Hozzavalo* elso = new Hozzavalo(Hoz_nev, Hoz_mert_egys);
                ReceptHozzavalo* lista = new ReceptHozzavalo(elso, Hoz_menny);
                ujtag->hozzaad(lista);
                //delete elso;                  //Jporta memtrace adatszivárgást dobott, de vele nem fut a program rendesen
                iter--;
            }
            std::getline(recept, Rec_szoveg);
            Rec_ido = readT<double>(recept);
            Recept* kell = new Recept(Rec_nev, hossz, ujtag, Rec_szoveg, Rec_ido);
            receptek.hozzaad(kell);
            hosszusag--;
        }
    }
    hozzavalo.close();
    recept.close();

}

// A main menu, amivel nyílik a program és ehhez tér vissza minden parancs végrehajtása után, innen lehet elkezdeni minden parancsot
void mainmenu() {
    std::cout << std::endl << std::endl;
    std::cout << " [1]  = Receptek nevenek listazasa" << std::endl;
    std::cout << " [2]  = Kivalasztott recept alapanyagainak kiirasa" << std::endl;
    std::cout << " [3]  = Uj recept hozzaadasa" << std::endl;
    std::cout << " [4]  = Recept torlese" << std::endl;
    std::cout << "[404] = Kilepes" << std::endl << std::endl;
    std::cout << "Az alabbi sorok kozul valassza ki mit szeretne csinalni az egyik" << std::endl << "alabbi gomb leirasaval es egy Enter gomb lenyomasaval" << std::endl << std::endl;
}

//Kiír minden recept nevét sorszámmal
void Kiir_all(Lista<Recept>& rhs) {
    Listaelem<Recept>* futo = rhs.elem();
    int szam = 1;
    while (futo != NULL) {

        std::cout << "[" << szam << "] " << futo->ertek->getNev() << std::endl;

        futo = futo->kov;
        szam++;
    }
}

//Kiír egy keresett receptet
void Recept_kiir(Lista<Recept>& receptek) {
    std::cout << "Irja be a kivant recept sorszamat!" << std::endl;

    int keresett;
    keresett = readT<int>(std::cin);

    int hossz = 0;
    Listaelem<Recept>* futo = receptek.elem();
    while (--keresett != 0 && futo != NULL) {
        futo = futo->kov;
        hossz++;
    }
    if (futo != NULL) {
        std::cout << *futo->ertek << std::endl;
    }
    else {
        std::cout << "1 es " << hossz << " kozotti szamot adjal meg!" << std::endl;
    }
}

//Új recept hozzáadása
void UjRecept(Lista<Hozzavalo>& hozzavalok, Lista<Recept>& receptek) {
    //Név hozzáadása
    std::cout << "Adja meg a recept nevet: ";
    std::string nev;
    std::getline(std::cin, nev);

    //Új hozzávalók hozzáadása
    Lista<ReceptHozzavalo>* hozzavalo = new Lista<ReceptHozzavalo>;
    std::string alapanyag;
    std::string mert_egys;
    double szam = -1;

    int uj = 1;
    int hossz = 1;
    while (uj != 2) {
        std::cout << "Adjon meg egy hozzavalot: ";
        std::getline(std::cin, alapanyag);
        std::cout << "Adja meg a mertekegyseget (roviditve): ";
        std::getline(std::cin, mert_egys);
        std::cout << "Adja meg mennyi kell belole: ";
        while (szam <= 0) {
            szam = readT<double>(std::cin);
            if (szam <= 0) {
                std::cout << "0-nal nagyobbat irj be! ";
            }
        }
        Hozzavalo* adat = new Hozzavalo(alapanyag, mert_egys); ;
        hozzavalok.hozzaad(adat);
        ReceptHozzavalo* elem = new ReceptHozzavalo(adat, szam);
        hozzavalo->hozzaad(elem);
        hossz++;
        std::cout << "Van meg uj hozzavaloja a receptnek? (1, ha igen, 2, ha nem) ";
        uj = readT<int>(std::cin);
        while (uj != 1 && uj != 2) {
            std::cout << "Kérlek 1 vagy 2 erteket irjon be!" << std::endl;
            std::cin >> uj;
        }
    }
    //A recept elkészítési útnutatója
    std::string szoveg;
    std::cout << std::endl << "Kerem adja meg az elkeszitesi modot: ";
    std::getline(std::cin, szoveg);

    //A recept elkészítési ideje
    std::cout << std::endl << "Adja meg az elkeszitesi idejet percben: ";
    double ido = -1;
    while (ido <= 0) {
        ido = readT<double>(std::cin);
        if (ido <= 0) {
            std::cout << "0-nal nagyobbat irj be! ";
        }
    }
    Recept* recept = new Recept (nev, hossz, hozzavalo, szoveg, ido);

    receptek.hozzaad(recept);
}

//Töröl egy receptet
void Recept_torol(Lista<Hozzavalo>& hozzavalok, Lista<Recept>& receptek) {
    int melyik;
    std::cout << "Valassza ki a recept sorszamat amit torolni szeretne: ";
    melyik = readT<int>(std::cin);
    if (melyik < 1) {
        std::cout << "Pozitiv szamot irjon be!" << std::endl;
        melyik = readT<int>(std::cin);
    }
    int hossz = 0;
    Listaelem<Recept>* elem = receptek.elem();
    while (--melyik != 0 && elem != NULL) {
        elem = elem->kov;
        hossz++;
    }
    if (elem == NULL) {
        std::cout << "Nincs ennyi recept a listaban 1 es " << hossz << "kozotti erteket irjon be";
    }
    else {
        std::cout << "Sikeres torles!" << std::endl;
        receptek.torol(elem->ertek);
    }
}

//Fileba ment minden adatot (listák hossza, tartalma)
void ment(Lista<Hozzavalo>& hozzavalok, Lista<Recept>& receptek) {
    std::ofstream hozzavalo("Hozzavalok.txt");
    std::ofstream recept("Receptek.txt");

    if (hozzavalo.is_open() && recept.is_open()) {

        //A Hozzávalók bejárása és elmentése
        int hosszusag = 0;
        Listaelem<Hozzavalo>* elem = hozzavalok.elem();
        while (elem != NULL) {
            hosszusag++;
            elem = elem->kov;
        }
        hozzavalo << hosszusag << std::endl;

        elem = hozzavalok.elem();
        while (elem != NULL) {
            hozzavalo << elem->ertek->getNev() << std::endl;
            hozzavalo << elem->ertek->getMertekegyseg() << std::endl;
            elem = elem->kov;
        }

        //A receptek bejárása és elmentése
        Listaelem<Recept>* tag = receptek.elem(); //az első recept pointer
        int elemhosszusag = 0;
        while (tag != NULL) {
            elemhosszusag++;
            tag = tag->kov;
        }
        recept << elemhosszusag << std::endl;

        tag = receptek.elem();
        while (tag != NULL) {
            recept << tag->ertek->getNev() << std::endl;
            Listaelem<ReceptHozzavalo>* futo = tag->ertek->getHozzavalok()->elem();  // tag elem hozzávalóinak elsőre muutató pointere

            recept << tag->ertek->getHossz() << std::endl;

            futo = tag->ertek->getHozzavalok()->elem();
            while (futo != NULL) {
                recept << futo->ertek->hozzavalo->getNev() << std::endl;
                recept << futo->ertek->hozzavalo->getMertekegyseg() << std::endl;
                recept << futo->ertek->mennyiseg << std::endl;
                futo = futo->kov;
            }
            recept << tag->ertek->getSzoveg() <<std::endl;
            recept << tag->ertek->getIdo() << std::endl;
            tag = tag->kov;
        }
        hozzavalo.close();
        recept.close();
    }
}




#ifdef TEST

    /// Hozzávaló létrejötte
    void test_1() {
        Hozzavalo* test = new Hozzavalo("Víz","dl");
        if (strcmp(test->getNev().c_str(), "Víz") != 0)
            throw std::exception();
        if (strcmp(test->getMertekegyseg().c_str(), "dl") != 0)
            throw std::exception();
    }

    /// Recept hozzávaló létrejötte
    void test_2() {
        const double mennyiseg = 2.0;
        Hozzavalo* test = new Hozzavalo((char*)"Víz", (char*)"dl");
        ReceptHozzavalo* test2 = new ReceptHozzavalo(test, mennyiseg);
        if (strcmp(test2->hozzavalo->getNev().c_str(), "Víz") != 0)
            throw std::exception();
        if (test2->mennyiseg != mennyiseg)
            throw std::exception();
    }

    /// Recept létrejötte
    void test_3() {
        const double mennyiseg = 2.0;
        Hozzavalo* test = new Hozzavalo((char*)"Víz", (char*)"dl");
        ReceptHozzavalo* test2 = new ReceptHozzavalo(test, mennyiseg);
        Lista<ReceptHozzavalo>* test3 = new Lista<ReceptHozzavalo>();
        test3->hozzaad(test2);
        Recept* test4 = new Recept((char*)"Egy pohár víz", 1, test3, (char*)"Finom", 1);
        if (strcmp(test4->getHozzavalok()->elem()->ertek->hozzavalo->getNev().c_str(), "Víz") != 0)
            throw std::exception();
        if (strcmp(test4->getSzoveg().c_str(), "Finom") != 0)
            throw std::exception();
        if (test4->getIdo() != 1)
            throw std::exception();
    }

    bool hozzavaloBetoltes(Lista<Hozzavalo>& hozzavalok) {
        std::ifstream hozzavalo("Test_h.txt");
        if (hozzavalo.is_open()) {
            //A hozzávalók változó feltöltése
            int hosszusag;
            hosszusag = readT<int>(hozzavalo);
            std::string tag_egy;
            std::string tag_ketto;

            while (hosszusag != 0) {
                std::getline(hozzavalo, tag_egy);
                std::getline(hozzavalo, tag_ketto);
                Hozzavalo* uj = new Hozzavalo(tag_egy, tag_ketto);
                hozzavalok.hozzaad(uj);
                hosszusag--;
            }
            hozzavalo.close();
            std::cout << "Fajl beolvasva.";

        }
        return true;
    }

    bool receptBetoltes(const Lista<Recept>& receptek) {
        std::ifstream recept("Test_r.txt");

        if(recept.is_open()) {
        std::string Rec_nev;
        int hosszusag;
        int hossz;
        std::string Hoz_nev;
        std::string Hoz_mert_egys;
        double Hoz_menny;
        std::string Rec_szoveg;
        double Rec_ido;
        hosszusag = readT<int>(recept);
            while (hosszusag != 0) {
                Lista<ReceptHozzavalo>* ujtag = new Lista<ReceptHozzavalo>();

                std::getline(recept, Rec_nev);
                //A hozzávalók listáinak beolvasása
                hossz = readT<int>(recept);
                int iter = hossz;
                    while (iter != 0) {
                    std::getline(recept, Hoz_nev);
                    std::getline(recept, Hoz_mert_egys);
                    Hoz_menny = readT<double>(recept);
                    Hozzavalo* elso = new Hozzavalo(Hoz_nev, Hoz_mert_egys);
                    ReceptHozzavalo* lista = new ReceptHozzavalo(elso, Hoz_menny);
                    ujtag->hozzaad(lista);
                    //delete elso;                  //Jporta memtrace adatszivárgást dobott, de vele nem fut a program rendesen
                    iter--;
            }
            std::getline(recept, Rec_szoveg);
            Rec_ido = readT<double>(recept);
            Recept* kell = new Recept(Rec_nev, hossz, ujtag, Rec_szoveg, Rec_ido);
            hosszusag--;
            }
        }
        recept.close();
        return true;
    }
    //Egy elem elmentése
    bool hozzavaloMentes() {
        std::ofstream hozzavalo("Test_h.txt");
        if (hozzavalo.is_open()) {
            hozzavalo << "2" << std::endl;
            hozzavalo << "Hozzavalo nev1" << std::endl;
            hozzavalo << "Hozzavalo mert.egys.1" << std::endl;
            hozzavalo << "Hozzavalo nev2" << std::endl;
            hozzavalo << "Hozzavalo mert.egys.2" << std::endl;
            hozzavalo.close();
            std::cout << "Fajl elmentve.";
        }
        return true;
    }
    //Egy recept elmentese
    bool receptMentes() {
        std::ofstream recept("Test_r.txt");
        if (recept.is_open()) {
            recept << "1" << std::endl;     //Hány recept van listában
            recept << "Proba nev" << std::endl;
            recept << "2" << std::endl;     //hány hozzávaló van listában
            recept << "Hozzavalo nev1" << std::endl;
            recept << "Hozzavalo mert.egys.1" << std::endl;
            recept << "Mennyiseg1" << std::endl;
            recept << "Hozzavalo nev2" << std::endl;
            recept << "Hozzavalo mert.egys.2" << std::endl;
            recept << "Mennyiseg2" << std::endl;
            recept.close();
            std::cout << "Fajl elmentve.";
        }


        return true;
    }

    int main() {
        Lista<Hozzavalo> hozzavalok;
        Lista<Recept> receptek;

        try {
            int nr;
            nr = readT<int>(std::cin);  // hányadik teszteset
            switch (nr) {
            case 1:
                test_1();   // hozzávaló létrejötte
                break;
            case 2:
                test_2();   // recept hozzávaló létrejötte
                break;
            case 3:
                test_3();   // recept létrejötte
                break;
            case 4:
                hozzavaloBetoltes(hozzavalok);
                break;
            case 5:
                receptBetoltes(receptek);
                break;
            case 6 :
                hozzavaloMentes();
                break;
            case 7:
                receptMentes();
                break;
            default:
                return 1;
            }
            // kivétel elkapása
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return 2;
        }
        catch (...) {
            std::cerr << "mas hiba";
            return 3;
        }

        return 0;
    }
#else
int main() {

    std::cout << "Italrecept " << std::endl << std::endl;

    Lista<Hozzavalo> hozzavalok;
    Lista<Recept> receptek;

    beolvas(hozzavalok, receptek);


    int cnt = 0; //a "menüváltozó"
    while (cnt != 404) {
        mainmenu();

        std::cout << "Valasszon egy parancsot : ";

        //std::cin >> cnt;
        if (!(std::cin >> cnt)) {
            std::cin.clear();
            cnt = -1;
            //std::cin.ignore(32767, '\n');                                           // Jporta *.*
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nem jo a bemenet! ";
        }
        std::string skip;
        std::getline(std::cin, skip);

        switch (cnt) {

        case 1:
            Kiir_all(receptek);
            break;

        case 2:
            Recept_kiir(receptek);
            break;

        case 3:
            UjRecept(hozzavalok, receptek);
            break;
        case 4:
            Recept_torol(hozzavalok, receptek);
            break;
        case 404:
            break;

        default: std::cout << "Nincs ilyen parancs." << std::endl;
            break;                                                   //Szintén Jporta csak így fogadja el...
        }

    }

    ment(hozzavalok, receptek);

    return 0;
}
#endif
