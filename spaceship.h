#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <GL/gl.h>
#include "globject.h"
#include "bullet.h"

#define MAIN_SHIP    0
#define NORMAL_SHIP  1
#define SPECIAL_SHIP 2

#define SHIP_SPEED      0.30f
#define SHIP_SPAWN_TIME 1500
#define SHIP_DMG        50

#define STATE_ALIVE 1
#define STATE_DYING 2
#define STATE_DEAD  3

#define ANNIMATION_SPEED     0.50f
#define MAX_ANNIMATION_STEPS 10.0f

class SpaceShip : public GLObject
{
private:
    int iHealth;
    POINT3D pos; // center
    unsigned int iType;
    unsigned int State;
    double AnnimationStep;
public:
    void Draw();
    void Update(double dTime);
    void Move(double x, double y, double z);
    void TakeDamage(int dmg);
    unsigned int GetState();
    unsigned int GetType2();
    POINT3D GetPos();
    SpaceShip(double x, double y, double z, unsigned int health, unsigned int type, unsigned int state);
    ~SpaceShip();
};

#endif // SPACESHIP_H
