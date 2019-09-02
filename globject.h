#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <windows.h>

#define ID_SPACESHIP 1
#define ID_BULLET    2

typedef struct _POINT3D
{
    double x;
    double y;
    double z;
} POINT3D, *PPOINT3D;

typedef struct _POINT2D
{
    double x;
    double y;
} POINT2D, *PPOINT2D;

class GLObject
{
protected:
    GLObject(unsigned int id);
    unsigned int type;
public:
    unsigned int GetType();
    virtual void Update(double dTime) = 0;
    virtual void Draw() = 0;
    virtual ~GLObject();
};

typedef struct _GLObjNode
{
    GLObject *Obj;
    _GLObjNode *nextObj;
    _GLObjNode *childObj;
} GLObjNode, *PGLObjNode;

#endif // GLOBJECT_H
