#ifndef MR_PARK_H
#define MR_PARK_H

class Parque {

public:

    Parque(int nPassageiros);

    virtual ~Parque();

    int getNumPassageiros();

    void setNumPassageiros(int num);

private:

    int numPassageiros;

};

#endif //MR_PARK_H
