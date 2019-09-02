#include "globject.h"

GLObject::GLObject(unsigned int id)
{
    type = id;
}

GLObject::~GLObject()
{

}

unsigned int GLObject::GetType()
{
    return type;
}
