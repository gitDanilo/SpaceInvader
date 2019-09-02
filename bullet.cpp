#include "bullet.h"

Bullet::Bullet(double x, double y, double z, unsigned int direction) : GLObject(ID_BULLET)
{
    pos.x = x;
    pos.y = y;
    pos.z = z;
    d = direction;
}

Bullet::~Bullet()
{
    OutputDebugStringA("Bullet::~Bullet()\n");

}

void Bullet::Update(double dTime)
{
    switch (d)
    {
        case 1:
            pos.x -= dTime * SPEED;
            break;
        case 2:
            pos.y -= dTime * SPEED;
            break;
        case 3:
            pos.z -= dTime * SPEED;
            break;
        case 4:
            pos.x += dTime * SPEED;
            break;
        case 5:
            pos.y += dTime * SPEED;
            break;
        case 6:
            pos.z += dTime * SPEED;
            break;
    }
}

void Bullet::Draw()
{
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex3f(pos.x - 0.10f, pos.y - 0.07f, pos.z - 0.25f);
        glVertex3f(pos.x + 0.10f, pos.y - 0.07f, pos.z - 0.25f);
        glVertex3f(pos.x + 0.10f, pos.y - 0.07f, pos.z + 0.25f);
        glVertex3f(pos.x - 0.10f, pos.y - 0.07f, pos.z + 0.25f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(pos.x - 0.10f, pos.y + 0.07f, pos.z - 0.25f);
        glVertex3f(pos.x + 0.10f, pos.y + 0.07f, pos.z - 0.25f);
        glVertex3f(pos.x + 0.10f, pos.y + 0.07f, pos.z + 0.25f);
        glVertex3f(pos.x - 0.10f, pos.y + 0.07f, pos.z + 0.25f);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(pos.x - 0.10f, pos.y - 0.07f, pos.z - 0.25f);
        glVertex3f(pos.x - 0.10f, pos.y + 0.07f, pos.z - 0.25f);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(pos.x + 0.10f, pos.y - 0.07f, pos.z - 0.25f);
        glVertex3f(pos.x + 0.10f, pos.y + 0.07f, pos.z - 0.25f);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(pos.x + 0.10f, pos.y - 0.07f,  pos.z + 0.25f);
        glVertex3f(pos.x + 0.10f, pos.y + 0.07f,  pos.z + 0.25f);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(pos.x - 0.10f, pos.y - 0.07f,  pos.z + 0.25f);
        glVertex3f(pos.x - 0.10f, pos.y + 0.07f,  pos.z + 0.25f);
    glEnd();
}

POINT3D Bullet::GetPos()
{
    return pos;
}
