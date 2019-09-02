#ifndef SCENE_H
#define SCENE_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include "globject.h"
#include "spaceship.h"
#include "modelobj.h"

#define ONE_DEG_IN_RAD 0.01745329251
#define SHOOT_INVERTVAL 200 // ms

typedef struct _Camera
{
    double eyeX;
    double eyeY;
    double eyeZ;
    double cntX;
    double cntY;
    double cntZ;
} Camera, *PCamera;

class Scene
{
private:
    GLObjNode ObjList;
    Camera camera;
    BOOL KeyDown[256];
    double scStep;
    bool GameOver;
    int Score;
    int Lives;
    void AddObj(GLObject *obj);
    void RemoveObj(GLObject *obj);
    void DeallocObj(PGLObjNode node);
    ModelObj obj;
    // Debug variables
    double _alpha;
    double _beta;
public:
    void Init();
    void Draw();
    void StepAnimation(double Ticks, double deltaTime);
    void SetCamera(double x1, double y1, double z1, double x2, double y2, double z2);
    void SetKeyDown(unsigned int pos, BOOL state);
    void MoveCamera(double x, double y, double z);
    int GetScore();
    int GetLives();
    // Debug function
    double _GetAlpha();
    double _GetBeta();
    void _DebugCamera(double r, double ofs_alpha, double ofs_beta);
    Scene();
    ~Scene();
};

#endif // SCENE_H
