#include <iostream>
#include "park.h"
#include "passanger.h"
#include "car.h"
#include <thread>

using namespace std;

int main() {

    int a,b;
    cout << "Entre com o numero de passageiros no parque: ";
    cin >> a;
    cout << "Entre com o numero de voltas do carro: ";
    cin >> b;

    Parque *parque = new Parque(a,b);

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