#include <iostream>
#include "park.h"
#include "passanger.h"
#include "car.h"
#include <thread>

using namespace std;

int main() {

    int a;
    cout << "Entre com o valor de passageiros no parque: ";
    cin >> a;

    Parque *parque = new Parque(a);

    Carro *carro = new Carro( *parque );

    Passageiro pass( *carro );

    std::thread tCarro = std::thread( &Carro::run, carro );

    std::thread *tPassageiro = new std::thread[a];

    for (int i = 0; i <a; i++)
    {
        tPassageiro[i] = std::thread( &Passageiro::run, pass, i );
    }


    for(int i = 0; i<a; i++)
    {
        tPassageiro[i].join();
    }

    tCarro.join();

    std::cout << std::endl << "Todos os passageiros sairam do parque" << std::endl;
    std::cout << "O parque fechou" << std::endl;

    delete carro;
    delete parque;

    return 0;

}