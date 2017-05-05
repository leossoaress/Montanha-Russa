#include "passanger.h"

std::atomic_int number = {1};

std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;


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
    if (carro.getNVoltas() < carro.getParque().getMaxVoltas())
        return false;

    return true;
}


void Passageiro::run(int i)
{
    while (!parqueFechado())
    {

        if (carro.getNVoltas() == carro.getParque().getMaxVoltas())          // Sai da fila caso o carro já deu o máximo numero de voltas
            break;

        carro.turn[i] = std::atomic_fetch_add( &number, 1 );   // O passageiro pega a ficha

        while (carro.turn[i] != carro.next)                    // Espera a ficha dele
        {
            if (carro.getNVoltas() == carro.getParque().getMaxVoltas())          // Sai da fila caso o carro já deu o máximo numero de voltas
                break;
        }

        while(carro.nPessoas == carro.capacidade)              // Espera caso o carro  esteja cheio
        {
            if (carro.getNVoltas() == carro.getParque().getMaxVoltas())          // Sai da fila caso o carro já deu o máximo numero de voltas
                break;
        }

        while( !carro.lock)                                     // Espera o carro ter esvaziado
        {
            if (carro.getNVoltas() == carro.getParque().getMaxVoltas())           // Sai da fila caso o carro já deu o máximo numero de voltas
                break;
        }

        if (carro.getNVoltas() == carro.getParque().getMaxVoltas())               // Sai da fila caso o carro já deu o máximo numero de voltas
            break;

        pthread_mutex_lock(&printf_mutex);
        std::cout << "Passageiro [" << i << "] com a ficha [" << carro.turn[i] << "] entrou no carro\n";
        pthread_mutex_unlock(&printf_mutex);

        x++;

        entraNoCarro();             // Entra no carro

        carro.next++;               // O próximo passageiro pode entrar

        while(carro.lock);          // Espera o carro dar uma volta


        while(lock_stream.test_and_set());           // Limita que apenas um passageiro saia por vez

        pthread_mutex_lock(&printf_mutex);
        std::cout << "Passageiro [" << i << "] saiu do carro\n";
        pthread_mutex_unlock(&printf_mutex);

        saiDoCarro();               // Sai do carro

        lock_stream.clear();        //Avisa que o próximo passageiro pode sair do carro

        passeiaPeloParque();        // Vai dar um passeio pelo parque

    }


    pthread_mutex_lock(&printf_mutex);

    std::cout << "Passageiro [" << i << "] saiu do parque e deu [ " << x << "] voltas!\n";

    carro.getParque().setNumPassageiros(1);         // decrementa o número de passageiros no parque

    pthread_mutex_unlock(&printf_mutex);
}
