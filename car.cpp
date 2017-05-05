#include "car.h"

#define MAX_NUM_VOLTAS 5

static pthread_mutex_t printf_mutex;

int Carro::capacidade = 0;

Carro::Carro(Parque &p) : parque(p)
{

    this->voltas = 0;
    Carro::capacidade = 5;
    this->nPassageiros = 0;
    nPessoas = 0;
    lock = true;
    next = 1;
    turn = new int [10];
}

Carro::~Carro() {}

void Carro::esperaEncher()
{
    while(nPessoas != capacidade);

    pthread_mutex_lock(&printf_mutex);
    std::cout << "Encheu\n";
    pthread_mutex_unlock(&printf_mutex);

}

void Carro::daUmaVolta()
{
    pthread_mutex_lock(&printf_mutex);
    std::cout << "Saiu para volta [" << voltas+1 <<  "]\n";
    pthread_mutex_unlock(&printf_mutex);

    voltas++;
    sleep(5);
}

void Carro::esperaEsvaziar()
{
    while(nPessoas);
    pthread_mutex_lock(&printf_mutex);
    std::cout << "Esvaziou\n";
    pthread_mutex_unlock(&printf_mutex);

}

int Carro::getNVoltas()
{
    return voltas;
}

Parque &Carro::getParque()
{
    return parque;
}

void Carro::addPessoa()
{
    Carro::nPessoas += 1 ;
}

void Carro::decPessoa()
{
    Carro::nPessoas -= 1;
}

int Carro::getCapacidade()
{
    return capacidade;
}

int Carro::getNumPassageiros()
{
    return nPessoas;
}

void Carro::run()
{
    while (parque.getNumPassageiros() > 0)
    {
        esperaEncher();     // Espera encher
        daUmaVolta();       // Dorme com sleep
        lock = false;       // Avisa que o carro encheu

        esperaEsvaziar();   // Espera esvaziar
        lock = true;        // Avisa que o carro esvaziou

    }

}