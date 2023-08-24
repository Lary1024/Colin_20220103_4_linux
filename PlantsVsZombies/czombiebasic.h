#ifndef CZOMBIEBASIC_H
#define CZOMBIEBASIC_H

#include "czombie.h"


class CZombieBasic : public CZombie
{
public:
    CZombieBasic();

public:
    virtual void InitZombie();
    bool IsHitPea(CPea *pPea);
    bool IsHitPlant(CPlant *pPlant);
};

#endif // CZOMBIEBASIC_H
