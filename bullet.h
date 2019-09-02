#ifndef BULLET_H
#define BULLET_H

#include <windows.h>
#include <GL/gl.h>
#include "globject.h"

#define SPEED 0.60f

class Bullet : public GLObject
{
private:
    unsigned int d; // direction
    POINT3D pos;
public:
    void Update(double dTime);
    void Draw();
    POINT3D GetPos();
    Bullet(double x, double y, double z, unsigned int direction);
    ~Bullet();
};

typedef struct _BulletNode
{
    Bullet *Obj;
    _BulletNode *nextObj;
} BulletNode, *PBulletNode;

#endif // BULLET_H
