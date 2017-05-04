#include "passanger.h"

#define MAX_NUM_VOLTAS 5

std::atomic_int number = {1};
std::atomic_int number1 = {5};

bool lock = false;

static pthread_mutex_t printf_mutex;

Passageiro::Passageiro(Carro &c) : carro(c) {}

Passageiro::~Passageiro() {}

void Passageiro::entraNoCarro()
{
    carro.addPessoa();
}

void Passageiro::esperaVoltaAcabar()
{
    sleep(5);
}

void Passageiro::saiDoCarro()
{
    carro.decPessoa();
}

void Passageiro::passeiaPeloParque()
{
    sleep(rand() % 10);
}

bool Passageiro::parqueFechado()
{
    if (carro.getNVoltas() < MAX_NUM_VOLTAS)
        return false;

    return true;
}

bool TS(bool *lock)
{
    pthread_mutex_lock(&printf_mutex);
    bool temp = *lock;
    *lock = true;
    pthread_mutex_unlock(&printf_mutex);
    return temp;

}

void Passageiro::run(int i)
{
    while (!parqueFechado())
    {

        if (carro.getNVoltas() == MAX_NUM_VOLTAS || (carro.nPessoas == 5 && carro.getNVoltas() == MAX_NUM_VOLTAS-1))
            break;

        carro.turn[i] = std::atomic_fetch_add( &number, 1 );

        while (carro.turn[i] != carro.next);

        while(carro.nPessoas == carro.capacidade);

        while( !carro.lock);

        pthread_mutex_lock(&printf_mutex);
        std::cout << "Passageiro [" << i << "] com a ficha [" << carro.turn[i] << "] entrou no carro\n";
        pthread_mutex_unlock(&printf_mutex);

        entraNoCarro();

        carro.next++;

        while(carro.lock);

        while(TS(&lock));

        pthread_mutex_lock(&printf_mutex);
        std::cout << "Passageiro [" << i << "] saiu no carro\n";
        pthread_mutex_unlock(&printf_mutex);

        saiDoCarro();

        lock = false;



        passeiaPeloParque();

    }
    while(carro.nPessoas != 0);
    pthread_mutex_lock(&printf_mutex);
    std::cout << "Passageiro [" << i << "] saindo do parque!\n";
    pthread_mutex_unlock(&printf_mutex);
}
