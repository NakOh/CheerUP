#pragma once

#ifndef __SHADERER_H__
#define __SHADERER_H__

#include <GL\glew.h>
#include <GL\glut.h>
#include "Matrix.h"
#include <math.h>
#include <stdlib.h>

#include "shader.hpp"
#include <fstream>

GLuint loadBMP_custom(const char * imagepath);

class GameObject;
class Model;

class ShaderID {
protected:
	float aspect = 1024 / 768;
	float fovy = 60;
	float far = 3000;
	float near = 0;
	float d = tanf(fovy / 3.141592 * 180);

	GLfloat modelMatrix[16];
	GLfloat viewMatrix[16];
	GLfloat scalelationMatrix[16];
	GLfloat projMatrix[16];

	void SetMetrices(Vec4& scale);
	void ObjectInit();

	GLuint* texID;

	void InitBitmap();
	//sBitmap bitmap;
public:
	ShaderID();
	int mainID; // Shader Program ID;
	int modelMatrixID; // Shader ModelMatrix ID;
	int viewMatrixID; // Shader ViewMatrix ID;
	int projectionMatrixID; // Shader ProjectionMatrix ID;
	int xAxisRotationMatrixID, yAxisRotationMatrixID, zAxisRotationMatrixID;
	int centerPositionID;
	int vertexPositionID; // Shader vertexPosition ID;
	int vertexColorID; // Shader vectexColor ID;
	int scaleMatrixID;

	int camXAxisRotationMatrixID, camYAxisRotationMatrixID, camZAxisRotationMatrixID;
	int lightPositionID; // Light  ID;
	int cameraPositionID; // Camara  ID;
	int vertexNormalID; // Shader vectexColor ID;

	int textureID;
	int texCoordID;

	void Init();
	void render(GameObject& obj, int textureNumber, bool isPhong);
	void setAspect(float as);
};

#endif