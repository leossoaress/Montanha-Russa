#ifndef MR_PASSANGER_H
#define MR_PASSANGER_H

#include "car.h"
#include <atomic>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <sstream>

class Passageiro {

    Carro &carro;


public:

    Passageiro(Carro &c);

    virtual ~Passageiro();

    void entraNoCarro();

    void esperaVoltaAcabar();

    void saiDoCarro();

    void passeiaPeloParque();

    bool parqueFechado();

    void run(int id);

    int x = {0};

};


#endif //MR_PASSANGER_H
