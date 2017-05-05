#include "car.h"

#define MAX_NUM_VOLTAS 6

static pthread_mutex_t printf_mutex;

int Carro::capacidade = 0;

Carro::Carro(Parque &p) : parque(p)
{

    this->voltas = 0;
    Carro::capacidade = p.getNumPassageiros() / 2;
    this->nPassageiros = 0;
    nPessoas = 0;
    lock = true;
    next = 1;
    turn = new int [p.getNumPassageiros()];
}

Carro::~Carro() {}

void Carro::esperaEncher()
{
    while(nPessoas != capacidade)
    {
        if(getParque().getNumPassageiros() == 0)
            break;
    }

        if(getParque().getNumPassageiros() == 0)
            return;

    pthread_mutex_lock(&printf_mutex);
    std::cout << "\nEncheu\n";
    pthread_mutex_unlock(&printf_mutex);

}

void Carro::daUmaVolta()
{
    pthread_mutex_lock(&printf_mutex);
    std::cout << "Saiu para volta [" << voltas+1 <<  "]\n\n";
    pthread_mutex_unlock(&printf_mutex);

    sleep(5);
}

void Carro::esperaEsvaziar()
{
    while(nPessoas);
    pthread_mutex_lock(&printf_mutex);
    std::cout << "\nEsvaziou\n\n";
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
    while ( voltas != parque.getMaxVoltas() + 1)
    {
        esperaEncher();     // Espera encher

        if(getParque().getNumPassageiros() == 0)     //verifica se o parque está vazio
            break;

        daUmaVolta();       // Dorme com sleep
        lock = false;       // Avisa que o carro encheu

        esperaEsvaziar();   // Espera esvaziar
        lock = true;        // Avisa que o carro esvaziou


        voltas++;
    }


}