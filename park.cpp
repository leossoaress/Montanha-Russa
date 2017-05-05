#include "park.h"

Parque::Parque(int nPassageiros)
{
    this->numPassageiros = nPassageiros;
}

Parque::~Parque() {}

int Parque::getNumPassageiros()
{
    return numPassageiros;
}

void Parque::setNumPassageiros(int num)
{
    numPassageiros -= num;
}