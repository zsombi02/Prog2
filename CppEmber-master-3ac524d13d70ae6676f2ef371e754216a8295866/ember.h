#ifndef EMBER_H_INCLUDED
#define EMBER_H_INCLUDED

class Ember
{
protected:
    char *nev;
    int szulEv;
public:
    Ember(const char *n = "P7XRW7", int ev = 2002);
    Ember(const Ember& e);
    Ember& operator =(const Ember& e);
    const char* getNev() const;
    virtual int getKor(int ev) const;
    virtual const char* foglalkozas() const;
    virtual ~Ember();
};

#endif // EMBER_H_INCLUDED
