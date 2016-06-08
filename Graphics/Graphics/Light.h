#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <GL\glew.h>
#include <GL\glut.h>
#include "Matrix.h"
#include <math.h>

/*
Vec4 light;
Vec4 camera;
Vec4 camera_dir;

float cam_RotMatrix_X[16];
float cam_RotMatrix_Y[16];
float cam_RotMatrix_Z[16];


void CamNLightInit();

void CamRotation(float x, float y, float z);
*/
//*
class Light {
public:
	void Init(float x, float y, float z);
	Vec4 pos;
};

class Camera {
public:
	void Init();
	Vec4 pos;
	Vec4 direction;
	float X_axis_RotationMatrix[16];
	float Y_axis_RotationMatrix[16];
	float Z_axis_RotationMatrix[16];
	void Rotation(float x, float y, float z);
};

class Time {
private:
	int privTime = 0;
public:
	int deltaTime = 0;
	void update();
};

//*/


#endif

