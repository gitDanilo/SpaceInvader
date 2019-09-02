#ifndef MODELOBJ
#define MODELOBJ

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9

using namespace std;

class ModelObj
{
  public:
    ModelObj();
    float* calculateNormal(float* coord1,float* coord2,float* coord3 );
    int Load(char *filename);	// Loads the model
    void Draw();					// Draws the model on the screen
    void Release();				// Release the model

    float* Faces_Triangles;					// Stores the triangles
    float* normals;							// Stores the normals
    float* vertexBuffer;					// Stores the points which make the object
    long TotalConnectedPoints;				// Stores the total number of connected verteces
    long TotalConnectedTriangles;			// Stores the total number of connected triangles

};

#endif // MODELOBJ

