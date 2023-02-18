#include <iostream>

using namespace std;

struct Pos {
    int x, y;
    Pos(int x = 0, int y = 0) :x(x), y(y) {}
};

std::ostream& operator<<(std::ostream& os, const Pos& p) {
    return  os << "(" << p.x << "," << p.y << ")";
}

enum Szin { VILAGOS, SOTET };

class Babu
{
    Szin sz;
    Pos p;
public:
    Babu() :sz(VILAGOS), p(Pos(0,0)) {};
    Babu(Szin sz0, Pos p0) :sz(sz0), p(p0) {};
    virtual ~Babu() {};
    void setpos(const Pos& P)
    {
        p.x = P.x;
        p.y = P.y;
    }
    Pos getpos() const {return p;};
    Szin getszin() const {return sz;};

    virtual bool lephet_ide(const Pos& P) const
    {

        if(P.x > 7 && P.x < 0)
            return false;
        if(P.x == p.x && P.y == p.y)
            return false;
        if(P.y > 7 && P.y < 0)
            return false;

        return true;
    }
};

class Bastya : public Babu
{
public:
    bool lephet_ide(const Pos& P) const
    {
        if(P.getpos(.x) == p.getpos(.x) && P.getpos(.y) == p.getpos(.y))
            return false;
        if(P.getpos(.x) != p.getpos(.x) || P.getpos(.y) != p.getpos(.y))
            return false;
        return true;
    }
};

Babu *tabla[8][8];
