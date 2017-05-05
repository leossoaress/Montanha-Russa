#ifndef MR_PARK_H
#define MR_PARK_H

class Parque {

public:

    Parque(int nPassageiros, int maxVoltas);

    virtual ~Parque();

    int getNumPassageiros();

    void setNumPassageiros(int num);

    int getMaxVoltas();

private:

    int numPassageiros;
    int mVoltas;
};

#endif //MR_PARK_H
