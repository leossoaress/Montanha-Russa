#include "park.h"

Parque::Parque(int nPassageiros, int maxVoltas)
{
    this->numPassageiros = nPassageiros;
    this->mVoltas = maxVoltas;
}

Parque::~Parque() {}

int Parque::getNumPassageiros()
{
    return numPassageiros;
}

int Parque::getMaxVoltas()
{
    return mVoltas;
}

void Parque::setNumPassageiros(int num)
{
    numPassageiros -= num;
}