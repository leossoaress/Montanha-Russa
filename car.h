#ifndef MR_CAR_H
#define MR_CAR_H

#include "park.h"
#include <unistd.h>
#include <atomic>
#include "stdlib.h"
#include <iostream>
#include <pthread.h>


class Carro {

public:


    Carro(Parque &p);

    virtual ~Carro();

    void esperaEncher();

    void daUmaVolta();

    void esperaEsvaziar();

    int getNVoltas();

    void addPessoa();

    void decPessoa();

    Parque &getParque();

    void run();

    int getCapacidade();

    int getNumPassageiros();

    int next;

    int *turn;

    bool lock;

    int nPessoas;

    static int capacidade;

private:

    int voltas;

    int nPassageiros;

    Parque &parque;
};


#endif //MR_CAR_H
