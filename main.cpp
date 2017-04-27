#include <iostream>
#include "park.h"
#include "passanger.h"
#include "car.h"
#include <thread>

#define NUM_THREADS 10

int next = 1;

using namespace std;

int main() {

    Parque *parque = new Parque( 10 );

    Carro *carro = new Carro( *parque );

    Passageiro pass( *carro );

    std::thread tCarro = std::thread( &Carro::run, carro );

    std::thread *tPassageiro = new std::thread[10];

    for (int i = 0; i < 10; i++)
    {
        tPassageiro[i] = std::thread( &Passageiro::run, pass, i );
    }


    for(int i = 0; i<10; i++)
    {
        tPassageiro[i].join();
    }

    delete carro;


    return 0;
}