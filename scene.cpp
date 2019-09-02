#include "scene.h"

Scene::Scene()
{
    OutputDebugStringA("Scene::Scene()\n");
    ZeroMemory(&camera, sizeof(Camera));
    ZeroMemory(&KeyDown, sizeof(BOOL) * 256);
    ObjList.Obj = NULL;
    ObjList.nextObj = NULL;
    ObjList.childObj = NULL;
    _alpha = 0.0;
    _beta = 0.0;
    scStep = 0.0;
}

Scene::~Scene()
{
    OutputDebugStringA("Scene::-Scene()\n");
    //obj.Release();
    DeallocObj(&ObjList);
}

void Scene::SetCamera(double x1, double y1, double z1, double x2, double y2, double z2)
{
    camera.eyeX = x1;
    camera.eyeY = y1;
    camera.eyeZ = z1;
    camera.cntX = x2;
    camera.cntY = y2;
    camera.cntZ = z2;
}

void Scene::SetKeyDown(unsigned int pos, BOOL state)
{
    KeyDown[pos] = state;
}

void Scene::MoveCamera(double x, double y, double z)
{
    camera.eyeX += x;
    camera.eyeY += y;
    camera.eyeZ += z;
}

double Scene::_GetAlpha()
{
    return _alpha;
}

double Scene::_GetBeta()
{
    return _beta;
}

/*void Scene::_DebugCamera(double r, double ofs_alpha, double ofs_beta)
{
    _alpha += ofs_alpha;
    _beta += ofs_beta;
    camera.eyeX = r * sin(_alpha * ONE_DEG_IN_RAD) * cos(_beta * ONE_DEG_IN_RAD);
    camera.eyeY = r * sin(_beta * ONE_DEG_IN_RAD);
    camera.eyeZ = 55.0 + r * cos(_alpha * ONE_DEG_IN_RAD) * cos(_beta * ONE_DEG_IN_RAD);
    camera.cntX = 0;
    camera.cntY = 0;
    camera.cntZ = 55.0;
}*/

void Scene::_DebugCamera(double r, double ofs_alpha, double ofs_beta)
{
    _alpha += ofs_alpha;
    _beta += ofs_beta;
    camera.eyeX = camera.cntX + r * sin(_alpha * ONE_DEG_IN_RAD) * cos(_beta * ONE_DEG_IN_RAD);
    camera.eyeY = camera.cntY + r * sin(_beta * ONE_DEG_IN_RAD);
    camera.eyeZ = camera.cntZ + r * cos(_alpha * ONE_DEG_IN_RAD) * cos(_beta * ONE_DEG_IN_RAD);
}

void Scene::Init()
{
    OutputDebugStringA("Scene::Init()\n");
    // Initialize antialiasing for RGBA mode
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);

    /*glMatrixMode(GL_MODELVIEW);
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
    GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };

    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );
    glShadeModel( GL_SMOOTH );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);*/

    glClearColor(0, 0, 0, 0);
    _alpha = 0;
    _beta = 0;
    camera.cntX = 0;
    camera.cntY = 0;
    camera.cntZ = 60.0;
    _DebugCamera(25.0, 0.0, 16.0);
    scStep = 0.0;
    Score = 0;
    Lives = 3;
    GameOver = false;
    //obj.Load("C:\\Users\\Vera\\Documents\\Qt\\CG-N4\\model\\spaceship5.obj");
    //create globjects

    srand(time(NULL)); // starts random seed

    // Main Space Ship
    SpaceShip *player1 = new SpaceShip(0.0, 0.0, 60.0, 100, MAIN_SHIP, STATE_ALIVE); // player 1 stored on first posistion
    AddObj((GLObject*)player1);
}

void Scene::AddObj(GLObject *obj)
{
    PGLObjNode i = &ObjList;
    while (i != NULL)
    {
        if (i->Obj == NULL)
        {
            i->Obj = obj;
            i->nextObj = NULL;
            i->childObj = NULL;
            return;
        }
        if (i->nextObj == NULL)
        {
            i->nextObj = new GLObjNode();
            i->nextObj->Obj = obj;
            i->nextObj->nextObj = NULL;
            i->nextObj->childObj = NULL;
            return;
        }
        i = i->nextObj;
    }
}

void Scene::DeallocObj(PGLObjNode node)
{
    if (node != NULL)
    {
        if (node->nextObj != NULL) DeallocObj(node->nextObj);
        if (node->Obj != NULL)
        {
            OutputDebugStringA("Deallocating GLObj\n");
            delete node->Obj;
        }
        if (node != &ObjList) delete node;
        else
        {
            node->childObj = NULL;
            node->nextObj = NULL;
            node->Obj = NULL;
        }
    }
}

void Scene::RemoveObj(GLObject *obj)
{
    if (obj == NULL) return;
    PGLObjNode i = &ObjList;
    if (i->Obj == obj)
    {
        i->Obj = NULL;
        delete obj;
        if (i->nextObj != NULL)
        {
            i->Obj = i->nextObj->Obj;
            i->childObj = i->nextObj->childObj;
            i->nextObj = i->nextObj->nextObj;
        }
        return;
    }
    while (i != NULL)
    {
        if (i->nextObj != NULL && i->nextObj->Obj == obj)
        {
            PGLObjNode tmp = i->nextObj;
            i->nextObj = i->nextObj->nextObj;
            delete obj;
            delete tmp;
            //child ??
        }
        i = i->nextObj;
    }
}

void Scene::StepAnimation(double Ticks, double deltaTime)
{
    static double lastShoot = 0;
    static double lastSpawn = 0;
    // Loop into obj list
    PGLObjNode i = &ObjList;
    PGLObjNode last_i = &ObjList;
    while (i != NULL && GameOver == false)
    {
        switch (i->Obj->GetType())
        {
            case ID_SPACESHIP:
            {
                SpaceShip *ship = (SpaceShip*)i->Obj;
                POINT3D tmp = ship->GetPos();

                switch (ship->GetState())
                {
                    case STATE_ALIVE:
                        {
                            if (ship->GetType2() == MAIN_SHIP)
                            {
                                if (KeyDown[41] == TRUE)
                                {
                                    ship->Move(-(0.50 * deltaTime), 0.0, 0.0); // A
                                    camera.eyeX -= 0.50 * deltaTime;
                                    camera.cntX -= 0.50 * deltaTime;
                                }

                                if (KeyDown[44] == TRUE)
                                {
                                    ship->Move((0.50 * deltaTime), 0.0, 0.0);  // D
                                    camera.eyeX += 0.50 * deltaTime;
                                    camera.cntX += 0.50 * deltaTime;
                                }

                                if (KeyDown[20] == TRUE) // Space
                                {
                                    if ((Ticks - lastShoot) >= SHOOT_INVERTVAL || lastShoot == 0)
                                    {
                                        AddObj(new Bullet(tmp.x, tmp.y, tmp.z - 1.0f, 3));
                                        lastShoot = Ticks;
                                    }
                                }
                            }
                            else // regular ships
                            {
                                if (tmp.z >= 74.0f) // end of scenario
                                {
                                    delete i->Obj;
                                    last_i->nextObj = i->nextObj;
                                    delete i;
                                    i = NULL;
                                    // REDUCE SCORE
                                    Lives -= 1;
                                    if (Lives <= 0)
                                    {
                                        GameOver = true;
                                        DeallocObj(&ObjList);
                                    }
                                }
                            }

                        }
                        break;
                    case STATE_DYING:

                        // ignore
                        break;
                    case STATE_DEAD:
                        // DEALLOC DEAD SPACE SHIP
                        Score += 10;
                        delete i->Obj;
                        last_i->nextObj = i->nextObj;
                        delete i;
                        i = NULL;
                        break;

                } // END OF SPACE SHIP TREATMENT
               // Collision check
            }
            break;
            case ID_BULLET:
            {
                // Collision check
                Bullet *bullet = (Bullet*)i->Obj;
                POINT3D tmp = bullet->GetPos();
                if (tmp.z <= -74.0f) // end of scenario
                {
                    delete i->Obj;
                    last_i->nextObj = i->nextObj;
                    delete i;
                    i = NULL;
                }
                else // box collision check
                {
                    PGLObjNode tmp_i = ObjList.nextObj; // skip first obj
                    //PGLObjNode last_tmp_i = &ObjList;
                    while (tmp_i != NULL)
                    {
                        if (tmp_i->Obj->GetType() == ID_SPACESHIP) // check collision only against boxes
                        {
                            SpaceShip *tmp_ship = (SpaceShip*)tmp_i->Obj;
                            POINT3D tmp_pos = tmp_ship->GetPos();
                            switch (tmp_ship->GetState())
                            {
                                case STATE_ALIVE:
                                    if (tmp.x <= (tmp_pos.x + 1.5f) && tmp.x >= (tmp_pos.x - 1.5f)) // on the way
                                    {
                                        if (tmp.z <= (tmp_pos.z + 1.5f)) // bullet hit box
                                        {
                                            tmp_ship->TakeDamage(SHIP_DMG);
                                            // DELETE BULLET
                                            delete i->Obj;
                                            last_i->nextObj = i->nextObj;
                                            delete i;
                                            tmp_i = NULL; // skip loop
                                            i = NULL;
                                        }
                                    }
                                    break;
                                case STATE_DYING:
                                    // have mercy
                                    break;
                                case STATE_DEAD:
                                    // cant collide against dead objects
                                    break;
                            }

                        }
                        if (tmp_i != NULL)
                        {
                            //last_tmp_i = tmp_i;
                            tmp_i = tmp_i->nextObj;
                        }
                    }
                }
            }
            break;
        }
        if (i != NULL)
        {
            i->Obj->Update(deltaTime);
            last_i = i;
            i = i->nextObj;
        }
        else if (GameOver == false)
        {
            i = last_i->nextObj;
            //last_i ??
        }
    }
    // SPAWN
    if (GameOver == false && (lastSpawn == 0 || (Ticks - lastSpawn) >= SHIP_SPAWN_TIME))
    {
        int number = rand() % 60 - 30;
        AddObj(new SpaceShip(number, 0.0f, -74.0f, 100, NORMAL_SHIP, STATE_ALIVE));
        lastSpawn = Ticks;
    }

    // Scenario Step
    if (scStep < 4.0) scStep += (0.32 * deltaTime);
    else scStep = 0.0;
}

int Scene::GetScore()
{
    return Score;
}

int Scene::GetLives()
{
    return Lives;
}

void Scene::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Setup camera
    gluLookAt(camera.eyeX, camera.eyeY, camera.eyeZ, camera.cntX, camera.cntY, camera.cntZ, 0 ,1 ,0);

    /*glPushMatrix();
        glTranslated(0.0, 0.0, 60.0);
        glRotated(-90, 1.0, 0.0, 0.0);
        glRotated(-90, 0.0, 0.0, 1.0);
        obj.Draw();
    glPopMatrix();*/

    // SCENARIO
    glLineWidth(1.50f);
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i <= 35; i++) // HORIZONTAL LINES
    {
        glBegin(GL_LINES);
            glVertex3f(-30.0, -10.0f, (double)((70.0f - (i * 4))) + scStep);
            glVertex3f(30.0, -10.0f, (double)((70.0f - (i * 4))) + scStep);
        glEnd();
    }
    glBegin(GL_LINES);
        glVertex3f(-30.0f, -10.0f, 74.0f);
        glVertex3f( 30.0f, -10.0f, 74.0f);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(-30.0f, -10.0f, -74.0f);
        glVertex3f( 30.0f, -10.0f, -74.0f);
    glEnd();
    for (int i = 0; i <= 30; i++) // VERTICAL LINES
    {
        glBegin(GL_LINES);
            glVertex3f((double)(30.0 - (i * 2)), -10.0f, 74.0);
            glVertex3f((double)(30.0 - (i * 2)), -10.0f, -74.0);
        glEnd();
    }
    glColor3f(1.0, 1.0, 0.0);
    for (int i = 0; i <= 35; i++)
    {
        glBegin(GL_LINES);
            glVertex3f(-30.0, 10.0f, (double)((70.0f - (i * 4))) + scStep);
            glVertex3f(30.0, 10.0f, (double)((70.0f - (i * 4))) + scStep);
        glEnd();
    }
    glBegin(GL_LINES);
        glVertex3f(-30.0f, 10.0f, 74.0f);
        glVertex3f( 30.0f, 10.0f, 74.0f);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(-30.0f, 10.0f, -74.0f);
        glVertex3f( 30.0f, 10.0f, -74.0f);
    glEnd();
    for (int i = 0; i <= 30; i++)
    {
        glBegin(GL_LINES);
            glVertex3f((double)(30.0 - (i * 2)), 10.0f, 74.0);
            glVertex3f((double)(30.0 - (i * 2)), 10.0f, -74.0);
        glEnd();
    }

    // DRAW OBJ LIST
    PGLObjNode i = &ObjList;
    while (i != NULL)
    {
        if (i->Obj != NULL) i->Obj->Draw();
        i = i->nextObj;
    }
}
