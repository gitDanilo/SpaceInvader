#include "spaceship.h"

SpaceShip::SpaceShip(double x, double y, double z, unsigned int health, unsigned int type, unsigned int state) : GLObject(ID_SPACESHIP)
{
    pos.x = x;
    pos.y = y;
    pos.z = z;
    iHealth = health;
    iType = type;
    State = state;
    AnnimationStep = 0;
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::Update(double dTime)
{
    switch (iType)
    {
        case MAIN_SHIP:
            break;
        case NORMAL_SHIP:
            switch (State)
            {
                case STATE_ALIVE:
                    pos.z += dTime * SHIP_SPEED;
                    break;
                case STATE_DYING:
                    if (AnnimationStep < MAX_ANNIMATION_STEPS) AnnimationStep += dTime * ANNIMATION_SPEED;
                    else State = STATE_DEAD;
                    break;
                case STATE_DEAD:
                    // ignore
                    break;
            }
            break;
        case SPECIAL_SHIP:
            pos.z += dTime * SHIP_SPEED;
            break;
    }
}

void SpaceShip::Move(double x, double y, double z)
{
    pos.x += x;
    pos.y += y;
    pos.z += z;
}

void SpaceShip::TakeDamage(int dmg)
{
    if (State == STATE_ALIVE)
    {
        iHealth -= dmg;
        if (iHealth <= 0) State = STATE_DYING;
    }
}

unsigned int SpaceShip::GetState()
{
    return State;
}

unsigned int SpaceShip::GetType2()
{
    return iType;
}

POINT3D SpaceShip::GetPos()
{
    return pos;
}

void SpaceShip::Draw()
{
    switch (iType)
    {
        case MAIN_SHIP:
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_LINE_LOOP);
                glVertex3f(pos.x - 1.0, pos.y - 0.25, pos.z - 1);
                glVertex3f(pos.x + 1.0, pos.y - 0.25, pos.z - 1);
                glVertex3f(pos.x + 1.0, pos.y - 0.25, pos.z + 1);
                glVertex3f(pos.x - 1.0, pos.y - 0.25, pos.z + 1);
            glEnd();
            glBegin(GL_LINE_LOOP);
                glVertex3f(pos.x - 1.0, pos.y + 0.25, pos.z - 1);
                glVertex3f(pos.x + 1.0, pos.y + 0.25, pos.z - 1);
                glVertex3f(pos.x + 1.0, pos.y + 0.25, pos.z + 1);
                glVertex3f(pos.x - 1.0, pos.y + 0.25, pos.z + 1);
            glEnd();
            glBegin(GL_LINE_STRIP);
                glVertex3f(pos.x + 1.0, pos.y + 0.25, pos.z - 1);
                glVertex3f(pos.x + 3.0, pos.y - 0.60, pos.z - 0.25);
                glVertex3f(pos.x + 3.0, pos.y - 0.60, pos.z + 0.25);
                glVertex3f(pos.x + 1.0, pos.y + 0.25, pos.z + 1);
            glEnd();
            glBegin(GL_LINE_STRIP);
                glVertex3f(pos.x + 1.0, pos.y - 0.25, pos.z - 1);
                glVertex3f(pos.x + 3.0, pos.y - 0.60, pos.z - 0.25);
                glVertex3f(pos.x + 3.0, pos.y - 0.60, pos.z + 0.25);
                glVertex3f(pos.x + 1.0, pos.y - 0.25, pos.z + 1);
            glEnd();
            glBegin(GL_LINE_STRIP);
                glVertex3f(pos.x - 1.0, pos.y - 0.25, pos.z - 1);
                glVertex3f(pos.x - 3.0, pos.y - 0.60, pos.z - 0.25);
                glVertex3f(pos.x - 3.0, pos.y - 0.60, pos.z + 0.25);
                glVertex3f(pos.x - 1.0, pos.y - 0.25, pos.z + 1);
            glEnd();
            glBegin(GL_LINE_STRIP);
                glVertex3f(pos.x - 1.0, pos.y + 0.25, pos.z - 1);
                glVertex3f(pos.x - 3.0, pos.y - 0.60, pos.z - 0.25);
                glVertex3f(pos.x - 3.0, pos.y - 0.60, pos.z + 0.25);
                glVertex3f(pos.x - 1.0, pos.y + 0.25, pos.z + 1);
            glEnd();
            glBegin(GL_LINES);
                glVertex3f(pos.x - 1.0, pos.y + 0.25, pos.z - 1);
                glVertex3f(pos.x - 1.0, pos.y - 0.25, pos.z - 1);
            glEnd();
            glBegin(GL_LINES);
                glVertex3f(pos.x + 1.0, pos.y + 0.25, pos.z - 1);
                glVertex3f(pos.x + 1.0, pos.y - 0.25, pos.z - 1);
            glEnd();
            glBegin(GL_LINES);
                glVertex3f(pos.x + 1.0, pos.y + 0.25, pos.z + 1);
                glVertex3f(pos.x + 1.0, pos.y - 0.25, pos.z + 1);
            glEnd();
            glBegin(GL_LINES);
                glVertex3f(pos.x - 1.0, pos.y + 0.25, pos.z + 1);
                glVertex3f(pos.x - 1.0, pos.y - 0.25, pos.z + 1);
            glEnd();
            break;
        case NORMAL_SHIP:
            switch (State)
            {
                case STATE_ALIVE:
                    glColor3f(0.0f, 0.0f, 1.0f);
                    glBegin(GL_LINE_LOOP);
                        glVertex3f(pos.x - 1.5f, pos.y - 1.2f, pos.z - 1.5f);
                        glVertex3f(pos.x + 1.5f, pos.y - 1.2f, pos.z - 1.5f);
                        glVertex3f(pos.x + 1.5f, pos.y - 1.2f, pos.z + 1.5f);
                        glVertex3f(pos.x - 1.5f, pos.y - 1.2f, pos.z + 1.5f);
                    glEnd();
                    glBegin(GL_LINE_LOOP);
                        glVertex3f(pos.x - 1.5f, pos.y + 1.2f, pos.z - 1.5f);
                        glVertex3f(pos.x + 1.5f, pos.y + 1.2f, pos.z - 1.5f);
                        glVertex3f(pos.x + 1.5f, pos.y + 1.2f, pos.z + 1.5f);
                        glVertex3f(pos.x - 1.5f, pos.y + 1.2f, pos.z + 1.5f);
                    glEnd();
                    glBegin(GL_LINES);
                        glVertex3f(pos.x - 1.5f, pos.y - 1.2f, pos.z - 1.5f);
                        glVertex3f(pos.x - 1.5f, pos.y + 1.2f, pos.z - 1.5f);
                    glEnd();
                    glBegin(GL_LINES);
                        glVertex3f(pos.x + 1.5f, pos.y + 1.2f, pos.z - 1.5f);
                        glVertex3f(pos.x + 1.5f, pos.y - 1.2f, pos.z - 1.5f);
                    glEnd();
                    glBegin(GL_LINES);
                        glVertex3f(pos.x + 1.5f, pos.y - 1.2f, pos.z + 1.5f);
                        glVertex3f(pos.x + 1.5f, pos.y + 1.2f, pos.z + 1.5f);
                    glEnd();
                    glBegin(GL_LINES);
                        glVertex3f(pos.x - 1.5f, pos.y - 1.2f, pos.z + 1.5f);
                        glVertex3f(pos.x - 1.5f, pos.y + 1.2f, pos.z + 1.5f);
                    glEnd();
                    break;
                case STATE_DYING:
                    glColor3f(0.0f, 1.0f, 1.0f);
                    glBegin(GL_LINE_LOOP);
                        glVertex3f(pos.x - (1.5f + AnnimationStep), pos.y - (1.2f + AnnimationStep), pos.z - (1.5f + AnnimationStep));
                        glVertex3f(pos.x + (1.5f - AnnimationStep), pos.y - (1.2f + AnnimationStep), pos.z - (1.5f + AnnimationStep));
                        glVertex3f(pos.x + (1.5f - AnnimationStep), pos.y - (1.2f + AnnimationStep), pos.z + (1.5f - AnnimationStep));
                        glVertex3f(pos.x - (1.5f + AnnimationStep), pos.y - (1.2f + AnnimationStep), pos.z + (1.5f - AnnimationStep));
                    glEnd();
                    glBegin(GL_LINE_LOOP);
                        glVertex3f(pos.x - (1.5f + AnnimationStep), pos.y + (1.2f - AnnimationStep), pos.z - (1.5f + AnnimationStep));
                        glVertex3f(pos.x + (1.5f - AnnimationStep), pos.y + (1.2f - AnnimationStep), pos.z - (1.5f + AnnimationStep));
                        glVertex3f(pos.x + (1.5f - AnnimationStep), pos.y + (1.2f - AnnimationStep), pos.z + (1.5f - AnnimationStep));
                        glVertex3f(pos.x - (1.5f + AnnimationStep), pos.y + (1.2f - AnnimationStep), pos.z + (1.5f - AnnimationStep));
                    glEnd();
                    glBegin(GL_LINES);
                        glVertex3f(pos.x - (1.5f + AnnimationStep), pos.y - (1.2f + AnnimationStep), pos.z - (1.5f + AnnimationStep));
                        glVertex3f(pos.x - (1.5f + AnnimationStep), pos.y + (1.2f - AnnimationStep), pos.z - (1.5f + AnnimationStep));
                    glEnd();
                    glBegin(GL_LINES);
                        glVertex3f(pos.x + (1.5f - AnnimationStep), pos.y - (1.2f + AnnimationStep), pos.z - (1.5f + AnnimationStep));
                        glVertex3f(pos.x + (1.5f - AnnimationStep), pos.y + (1.2f - AnnimationStep), pos.z - (1.5f + AnnimationStep));
                    glEnd();
                    glBegin(GL_LINES);
                        glVertex3f(pos.x + (1.5f - AnnimationStep), pos.y - (1.2f + AnnimationStep), pos.z + (1.5f - AnnimationStep));
                        glVertex3f(pos.x + (1.5f - AnnimationStep), pos.y + (1.2f - AnnimationStep), pos.z + (1.5f - AnnimationStep));
                    glEnd();
                    glBegin(GL_LINES);
                        glVertex3f(pos.x - (1.5f + AnnimationStep), pos.y - (1.2f + AnnimationStep), pos.z + (1.5f - AnnimationStep));
                        glVertex3f(pos.x - (1.5f + AnnimationStep), pos.y + (1.2f - AnnimationStep), pos.z + (1.5f - AnnimationStep));
                    glEnd();
                    break;
                case STATE_DEAD:
                    // ignore
                    break;
            }
            break;
        case SPECIAL_SHIP:
            break;
        default:
        break;
    }
}
