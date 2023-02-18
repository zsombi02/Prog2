#include "gtest_lite.h"
#include "memtrace.h"
#include "vektor.h"



size_t Vektor::defSize = 17;
double Vektor::defValue = 27;


Vektor::Vektor(const Vektor& v)
{
    nElements = v.nElements;
    pVec = new double[nElements];
    for (size_t i = 0; i < nElements; i++)
    {
        pVec[i] = v.pVec[i];
    }
}



Vektor::~Vektor()
{
    delete []pVec;
}

Vektor& Vektor::operator=(const Vektor& v)
{
    if (pVec != v.pVec)
    {
        delete []pVec;
        nElements = v.nElements;
        pVec = new double[nElements];
        for (size_t i = 0; i < nElements; i++)
            {
                pVec[i] = v.pVec[i];
            }
    }
    return *this;
}


double& Vektor::operator[](size_t idx)
{
    if (idx >= 0 && idx < nElements)
    {
        return pVec[idx];
    }
    throw "P7XRW7";
}

const double& Vektor::operator[](size_t idx) const
{
    if (idx >= 0 && idx < nElements)
        {
        return pVec[idx];
        }
    throw "P7XRW7";
}


Vektor operator*(double val, const Vektor& vec)
{
    int j = vec.size();
    Vektor v(j);
    for (int i = 0; i < j; i++)
    {
        v[i] = val * vec[i];
    }
    return v;
}
