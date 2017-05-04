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

        carro.turn[i] = std::atomic_fetch_add( &number, 1 );   // O passageiro pega a ficha

        while (carro.turn[i] != carro.next)                    // Espera a ficha dele
        {
            if (carro.getNVoltas() == MAX_NUM_VOLTAS)          // Sai da fila caso o carro já deu o máximo numero de voltas
                break;
        }

        while(carro.nPessoas == carro.capacidade)              // Espera caso o carro  esteja cheio
        {
            if (carro.getNVoltas() == MAX_NUM_VOLTAS)          // Sai da fila caso o carro já deu o máximo numero de voltas
                break;
        }

        while( !carro.lock)                                     // Espera o carro ter esvaziado
        {
            if (carro.getNVoltas() == MAX_NUM_VOLTAS)           // Sai da fila caso o carro já deu o máximo numero de voltas
                break;
        }

        if (carro.getNVoltas() == MAX_NUM_VOLTAS)               // Sai da fila caso o carro já deu o máximo numero de voltas
            break;

        pthread_mutex_lock(&printf_mutex);
        std::cout << "Passageiro [" << i << "] com a ficha [" << carro.turn[i] << "] entrou no carro\n";
        pthread_mutex_unlock(&printf_mutex);

        entraNoCarro();             // Entra no carro

        carro.next++;               // O próximo passageiro pode entrar

        while(carro.lock);          // Espera o carro dar uma volta

        while(TS(&lock));           // Limita que apenas um passageiro saia por vez

        pthread_mutex_lock(&printf_mutex);
        std::cout << "Passageiro [" << i << "] saiu no carro\n";
        pthread_mutex_unlock(&printf_mutex);

        saiDoCarro();               // Sai do carro

        lock = false;               // Avisa que o próximo passageiro pode sair do carro



        passeiaPeloParque();        // Vai dar um passeio pelo parque

    }

    pthread_mutex_lock(&printf_mutex);
    std::cout << "Passageiro [" << i << "] saindo do parque!\n";
    pthread_mutex_unlock(&printf_mutex);
}
