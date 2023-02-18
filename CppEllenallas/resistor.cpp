/**
 * \file resistor.cpp
 *   (UTF-8 kodolasu fajl. Allitsa at a megjenetes kodolasat,
 *    ha a tovabbi kommentek nem olvashatok helyesen!)
 *
 * Ohmikus ellenállást modellező osztály megvalósítása
 */

/**
 * Itt kell megvalósítani a resistor.h-ban deklarált nem inline függvényeket.
 * A Jportára ezt a fájlt kell feltölteni.
 */

#include "resistor.h"

double Resistor::defR = 77;

void Resistor::setDef(double r)
{
    defR = r;
}

Resistor::Resistor()
{
    R = Resistor::defR;
    Pr("ctor0");
}
Resistor::Resistor(double r)
{
    R = r;
    Pr("ctor1");
}

Resistor Resistor::operator+(const Resistor& r) const
{
    Resistor res = Resistor(r.getR() + R);
    return res;
}

Resistor Resistor::operator%(const Resistor& r) const
{
    return Resistor((R * r.getR()) / (R + r.getR()));
}

Resistor operator*(int n, const Resistor& r)
{
    if (n <= 0) throw "P7XRW7";
    return
    Resistor(n * r.getR());
}

Resistor::Resistor(const Resistor& rhs) :R(rhs.R)
{
    Pr("Copy");
}
