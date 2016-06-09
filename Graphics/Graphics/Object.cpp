#define _CRT_SECURE_NO_WARNINGS

#include "Object.h"
#include <stdlib.h>
#include <string>
#include <iostream>


#include <GL\glut.h>
#include "shader.hpp"
#include "Matrix.h"
#include <math.h>


using namespace std;


GLuint loadBMP_custom(const char * imagepath) {
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;
	FILE * file = fopen(imagepath, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }
	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	if (imageSize == 0)    imageSize = width*height * 3;
	if (dataPos == 0)      dataPos = 54;
	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

Vertex::Vertex() {
	pos = Vec4();
	normal = Vec4();
	sum_normal = Vec4();
	color = Vec4(1, 1, 1, 1);
}
///*
int ParseCount(char* strVertex) {
	char* context;
	char* tempStr;
	strtok_s(strVertex, " ", &context);
	strtok_s(NULL, " ", &context);
	tempStr = strtok_s(NULL, " ", &context);
	int strLen = atoi(tempStr);

	return strLen;
}


void ShaderID::InitBitmap() {
	int textureNumber = 2;
	texID = (GLuint*)malloc(sizeof(GLuint) * textureNumber);
	glGenTextures(textureNumber, &texID[0]);

	glBindTexture(GL_TEXTURE_2D, texID[0]);
	loadBMP_custom("models/check.bmp");

	glBindTexture(GL_TEXTURE_2D, texID[1]);
	loadBMP_custom("models/flight.bmp");

}

void ShaderID::SetMetrices(Vec4& scale) {
	for (int i = 0; i < 16; i++)	modelMatrix[i] = viewMatrix[i] = scalelationMatrix[i] = projMatrix[i] = 0;
	for (int i = 0; i < 4; i++)		modelMatrix[i * 5] = viewMatrix[i * 5] = 1;
	scalelationMatrix[0] = scale.x;
	scalelationMatrix[5] = scale.y;
	scalelationMatrix[10] = scale.z;
	scalelationMatrix[15] = 1;

	projMatrix[0] = aspect / d;
	projMatrix[5] = d;
	projMatrix[10] = (far + near) / (far - near);
	projMatrix[11] = 1;
	projMatrix[14] = -2 * (far * near) / (far - near);
	projMatrix[15] = 1;
}

void ShaderID::ObjectInit(){
	//bitmap = Bitmap("models/flight.bmp");

	textureID = glGetAttribLocation(mainID, "vertexTexture");
	texCoordID = glGetUniformLocation(mainID, "tex");

	glActiveTexture(GL_TEXTURE0);

	InitBitmap();

	//각 버텍스마다 값이 같음.
	//기본적인 프로젝션 아이디.
	modelMatrixID = glGetUniformLocation(mainID, "modelMatrix");
	viewMatrixID = glGetUniformLocation(mainID, "viewMatrix");
	projectionMatrixID = glGetUniformLocation(mainID, "projectionMatrix");

	//빛과 카메라를 위한 아이디.
	lightPositionID = glGetUniformLocation(mainID, "lightPosition");
	cameraPositionID = glGetUniformLocation(mainID, "cameraPosition");
	camXAxisRotationMatrixID = glGetUniformLocation(mainID, "camXRot");
	camYAxisRotationMatrixID = glGetUniformLocation(mainID, "camYRot");
	camZAxisRotationMatrixID = glGetUniformLocation(mainID, "camZRot");

	//회전과 크기를 위한 아이디.
	xAxisRotationMatrixID = glGetUniformLocation(mainID, "xAxisRotationMatrixID");
	yAxisRotationMatrixID = glGetUniformLocation(mainID, "yAxisRotationMatrixID");
	zAxisRotationMatrixID = glGetUniformLocation(mainID, "zAxisRotationMatrixID");
	centerPositionID = glGetUniformLocation(mainID, "centerPosition");
	scaleMatrixID = glGetUniformLocation(mainID, "scaleMatrix");


	//각 버텍스마다 값이 다름.
	vertexPositionID = glGetAttribLocation(mainID, "vertexPosition");
	vertexColorID = glGetAttribLocation(mainID, "vertexColor");
	vertexNormalID = glGetAttribLocation(mainID, "vertexNormal");
}

void ShaderID::Init() {
	mainID = shader::LoadShaders("VertexShader.vert", "FragmentShader.frag");
	ObjectInit();
}

void ShaderID::Render(GameObject& obj, int textureNumber) {

	SetMetrices(obj.transform.scale);

	glUseProgram(mainID);

	glUniform1i(textureID, 0);
	glBindTexture(GL_TEXTURE_2D, texID[textureNumber]);

	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0]);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projMatrix[0]);
	glUniformMatrix4fv(xAxisRotationMatrixID, 1, GL_FALSE, &obj._axisRotation._X_axis_RotationMatrix[0]);
	glUniformMatrix4fv(yAxisRotationMatrixID, 1, GL_FALSE, &obj._axisRotation._Y_axis_RotationMatrix[0]);
	glUniformMatrix4fv(zAxisRotationMatrixID, 1, GL_FALSE, &obj._axisRotation._Z_axis_RotationMatrix[0]);
	glUniformMatrix4fv(scaleMatrixID, 1, GL_FALSE, &scalelationMatrix[0]);

	glUniformMatrix4fv(camXAxisRotationMatrixID, 1, GL_FALSE, &obj.camera->X_axis_RotationMatrix[0]);
	glUniformMatrix4fv(camYAxisRotationMatrixID, 1, GL_FALSE, &obj.camera->Y_axis_RotationMatrix[0]);
	glUniformMatrix4fv(camZAxisRotationMatrixID, 1, GL_FALSE, &obj.camera->Z_axis_RotationMatrix[0]);

	glUniform4f(centerPositionID, obj.transform.position.x, obj.transform.position.y, obj.transform.position.z, 1);
	glUniform4f(lightPositionID, obj.light->pos.x, obj.light->pos.y, obj.light->pos.z, 1);
	glUniform4f(cameraPositionID, obj.camera->pos.x, obj.camera->pos.y, obj.camera->pos.z, 1);

	glEnableVertexAttribArray(vertexPositionID);
	glEnableVertexAttribArray(vertexColorID);
	glEnableVertexAttribArray(vertexNormalID);
	glEnableVertexAttribArray(textureID);

	glVertexAttribPointer(vertexPositionID, 4, GL_FLOAT, GL_FALSE, 0, (void*)&obj.arrays.vertexPositionArray[0]);
	glVertexAttribPointer(vertexColorID, 4, GL_FLOAT, GL_FALSE, 0, (void*)&obj.model.colordata[0]);
	glVertexAttribPointer(vertexNormalID, 4, GL_FLOAT, GL_FALSE, 0, (void*)&obj.arrays.vertexNormalArray[0]);
	glVertexAttribPointer(textureID, 2, GL_FLOAT, GL_FALSE, 0, (void*)&obj.arrays.vertexCoordArray[0]);

	glDrawArrays(GL_TRIANGLES, 0, obj.model.faceCount * 3);

	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(vertexColorID);
	glDisableVertexAttribArray(lightPositionID);

	//glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);
}

void ShaderID::setAspect(float as) {
	aspect = as;
}

void GameObject::setAspect(float as) {
	shaderID.setAspect(as);
}

void GameObject::InitCenter() {
	for (int i = 0; i < model.vertexCount; i++)	transform.position.Add(model.vertices[i].pos);
	transform.position.Divide(model.vertexCount);
	for (int i = 0; i < model.vertexCount; i++)	model.vertices[i].pos.Sub(transform.position);
	transform.position.x = transform.position.y = transform.position.z = 0;
}


void GameObject::InitColor() {
	model.colordata = new GLfloat[model.vertexCount * 4 * 10];
	for (int i = 0; i < model.vertexCount * 4 * 10; i++)	model.colordata[i] = 1.0f;
}

void GameObject::Setup_Tag(string tag) {
	model.tag = tag;
}


void GameObject::InitGPUId() {
	shaderID.Init();
	//gouraudID.Init();
}

void GameObject::InitFace(FILE* f) {
	//의미없이 셋을 날림.
	char ssss[100];
	for (int i = 0; i < 3; i++)
		fscanf(f, "%s", &ssss);
	model.faceCount = ParseStringToInt(ssss);
	model.faces = new Point4[model.faceCount];
	model.coords = new Point4[model.faceCount];
	for (int i = 0; i < model.faceCount; i++) {
		fscanf(f, "%d/%d %d/%d %d/%d\n", &model.faces[i].p[0], &model.coords[i].p[0], &model.faces[i].p[1], &model.coords[i].p[1], &model.faces[i].p[2], &model.coords[i].p[2]);
		for (int j = 0; j < 3; j++) {
			model.faces[i].p[j] --;
			model.coords[i].p[j]--;
		}
	}
}

void GameObject::InitCoordData(FILE* f) {
	char ssss[100];
	for (int i = 0; i < 3; i++)
		fscanf(f, "%s", &ssss);
	model.textureCount = ParseStringToInt(ssss);
	model.coorddata = new Vec4[model.textureCount];
	int a, b, c;
	for (int i = 0; i < model.textureCount; i++) {
		fscanf(f, "%f %f %f\n", &model.coorddata[i].x, &model.coorddata[i].y, &model.coorddata[i].z);
		model.coorddata[i].w = 1;
		a = model.coorddata[i].x;
		b = model.coorddata[i].y;
		c = model.coorddata[i].z;
		a = b = c = 0;
	}
}

void GameObject::InitVertex(FILE* f) {
	double size = 0.005;
	fscanf(f, "VERTEX = %d", &model.vertexCount);
	model.vertices = new Vertex[model.vertexCount];
	for (int i = 0; i < model.vertexCount; i++) {
		fscanf(f, "%f %f %f", &model.vertices[i].pos.x, &model.vertices[i].pos.y, &model.vertices[i].pos.z);
		model.vertices[i].pos.Mul(size);
		float a = model.vertices[i].pos.x;
		float b = model.vertices[i].pos.y;
		float c = model.vertices[i].pos.z;
	}
}

GameObject::GameObject(const char* path, Camera* camera, Light* light, string tag) {

	transform = Transform(this);
	this->camera = camera;
	this->light = light;

	FILE* f = fopen(path, "rt");

	InitVertex(f);
	InitCoordData(f);
	InitFace(f);
	Setup_Tag(tag);
	fclose(f);

	InitColor();
	InitCenter();
	InitGPUId();

	InitData();
}

void Transform::SetPosition(float x, float y, float z) {
	float dx, dy, dz;
	dx = x - position.x;
	dy = y - position.y;
	dz = z - position.z;
	position.x += dx;
	position.y += dy;
	position.z += dz;

	for (int i = 0; i < gameObject->model.vertexCount; i++) {
		gameObject->model.vertices[i].pos.x += dx;
		gameObject->model.vertices[i].pos.y += dy;
		gameObject->model.vertices[i].pos.z += dz;
	}

	for (int i = 0; i < gameObject->model.faceCount; i++) {
		for (int k = 0; k < 3; k++) {
			int vertIndex = gameObject->model.faces[i].p[k];
			gameObject->arrays.vertexPositionArray[(i * 3 + k) * 4 + 0] = gameObject->model.vertices[vertIndex].pos.x;
			gameObject->arrays.vertexPositionArray[(i * 3 + k) * 4 + 1] = gameObject->model.vertices[vertIndex].pos.y;
			gameObject->arrays.vertexPositionArray[(i * 3 + k) * 4 + 2] = gameObject->model.vertices[vertIndex].pos.z;
			gameObject->arrays.vertexPositionArray[(i * 3 + k) * 4 + 3] = 1;
		}
	}

}

void Transform::Scalelation(float x, float y, float z) {
	scale.x += x;
	scale.y += y;
	scale.z += z;
}

void Transform::SetScale(float x, float y, float z) {
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

void GameObject::Setup_VertexPositionToArray() {
	for (int i = 0; i < model.faceCount; i++) {
		for (int k = 0; k < 3; k++) {
			int vertIndex = model.faces[i].p[k];
			arrays.vertexPositionArray[(i * 3 + k) * 4 + 0] = model.vertices[vertIndex].pos.x;
			arrays.vertexPositionArray[(i * 3 + k) * 4 + 1] = model.vertices[vertIndex].pos.y;
			arrays.vertexPositionArray[(i * 3 + k) * 4 + 2] = model.vertices[vertIndex].pos.z;
			arrays.vertexPositionArray[(i * 3 + k) * 4 + 3] = 1;
		}
	}
}

void GameObject::Setup_CoordinationToArray() {
	for (int i = 0; i < model.faceCount; i++) {
		for (int k = 0; k < 3; k++) {
			int coordIndex = model.coords[i].p[k];
			arrays.vertexCoordArray[(i * 3 + k) * 2 + 0] = model.coorddata[coordIndex].x;
			arrays.vertexCoordArray[(i * 3 + k) * 2 + 1] = model.coorddata[coordIndex].y;
		}
	}
}

void Transform::Translation(float x, float y, float z) {
	position.Add(x, y, z);
	for (int i = 0; i < gameObject->model.vertexCount; i++)	gameObject->model.vertices[i].pos.Add(x, y, z);
	for (int i = 0; i < gameObject->model.faceCount; i++) {
		for (int k = 0; k < 3; k++) {
			int vertIndex = gameObject->model.faces[i].p[k];
			gameObject->arrays.vertexPositionArray[(i * 3 + k) * 4 + 0] = gameObject->model.vertices[vertIndex].pos.x;
			gameObject->arrays.vertexPositionArray[(i * 3 + k) * 4 + 1] = gameObject->model.vertices[vertIndex].pos.y;
			gameObject->arrays.vertexPositionArray[(i * 3 + k) * 4 + 2] = gameObject->model.vertices[vertIndex].pos.z;
			gameObject->arrays.vertexPositionArray[(i * 3 + k) * 4 + 3] = 1;
		}
	}
}

void Transform::Rotation(float x, float y, float z) {
	rotation.x += x;
	rotation.y += y;
	rotation.z += z;
	gameObject->_axisRotation._X_axis_RotationMatrix[5] = cos(rotation.x);
	gameObject->_axisRotation._X_axis_RotationMatrix[6] = sin(rotation.x);
	gameObject->_axisRotation._X_axis_RotationMatrix[9] = -sin(rotation.x);
	gameObject->_axisRotation._X_axis_RotationMatrix[10] = cos(rotation.x);

	gameObject->_axisRotation._Y_axis_RotationMatrix[0] = cos(rotation.y);
	gameObject->_axisRotation._Y_axis_RotationMatrix[2] = -sin(rotation.y);
	gameObject->_axisRotation._Y_axis_RotationMatrix[8] = sin(rotation.y);
	gameObject->_axisRotation._Y_axis_RotationMatrix[10] = cos(rotation.y);

	gameObject->_axisRotation._Z_axis_RotationMatrix[0] = cos(rotation.z);
	gameObject->_axisRotation._Z_axis_RotationMatrix[1] = sin(rotation.z);
	gameObject->_axisRotation._Z_axis_RotationMatrix[4] = -sin(rotation.z);
	gameObject->_axisRotation._Z_axis_RotationMatrix[5] = cos(rotation.z);

}

void GameObject::Setup_NormalVector() {
	Setup_FaceNormalVector();
	Setup_VertexNormalVector();
}

void GameObject::Setup_FaceNormalVector() {
	Vec4** pos = (Vec4**)malloc(sizeof(Vec4*) * 3);
	for (int i = 0; i < 3; i++)	pos[i] = new Vec4();
	for (int i = 0; i < model.faceCount; i++) {
		for (int k = 0; k < 3; k++) {
			int vertIndex = model.faces[i].p[k];
			pos[k]->x = arrays.vertexPositionArray[(i * 3 + k) * 4 + 0];
			pos[k]->y = arrays.vertexPositionArray[(i * 3 + k) * 4 + 1];
			pos[k]->z = arrays.vertexPositionArray[(i * 3 + k) * 4 + 2];
		}
		pos[1]->Sub(*pos[0]);
		pos[2]->Sub(*pos[0]);

		arrays.faceNormalVector[i] = *Vec4::Cross(pos[1], pos[2]);
		arrays.faceNormalVector[i].Normalize();
	}
	for (int i = 0; i < 3; i++)	delete pos[i];
	free(pos);
}

void GameObject::Setup_VertexNormalVector() {
	for (int i = 0; i < model.faceCount; i++) {
		for (int k = 0; k < 3; k++) {
			int vertIndex = model.faces[i].p[k];
			model.vertices[vertIndex].sum_normal.Add(arrays.faceNormalVector[i]);
		}
	}

	for (int i = 0; i < model.vertexCount; i++) {
		model.vertices[i].sum_normal.Normalize();
	}

	for (int i = 0; i < model.faceCount; i++) {
		for (int k = 0; k < 3; k++) {
			int vertIndex = model.faces[i].p[k];
			arrays.vertexNormalArray[(i * 3 + k) * 4 + 0] = model.vertices[vertIndex].sum_normal.x;
			arrays.vertexNormalArray[(i * 3 + k) * 4 + 1] = model.vertices[vertIndex].sum_normal.y;
			arrays.vertexNormalArray[(i * 3 + k) * 4 + 2] = model.vertices[vertIndex].sum_normal.z;
			arrays.vertexNormalArray[(i * 3 + k) * 4 + 3] = 1;
		}
	}
}

void GameObject::InitData() {
	arrays.vertexPositionArray = new GLfloat[model.faceCount * 3 * 4];
	arrays.vertexNormalArray = new GLfloat[model.faceCount * 3 * 4];
	arrays.vertexCoordArray = new GLfloat[model.faceCount * 3 * 4];
	arrays.faceNormalVector = new Vec4[model.faceCount];
	Setup_VertexPositionToArray();
	Setup_CoordinationToArray();
	Setup_NormalVector();
}

void GameObject::draw() {
	shaderID.Render(*this, 1);
}

float GameObject::ParseStringToFloat(const char *s) {
	int negative = 1;
	int startPos = 0;
	float ret = 0;
	int length = 0;
	bool isFindPoint = false;
	float point = 1;
	if (s == NULL || *s == '\0')	return 0;
	length = strlen(s);
	if (s[0] == '-')	negative = -1;
	if (s[0] == '+' || s[0] == '-')	startPos++;
	for (int i = startPos; i < length - 1; i++) {
		if ('0' <= s[i] && s[i] <= '9') {
			ret = ret * 10 + (s[i] - '0');
			if (isFindPoint) point *= 10;
		}
		else if (s[i] == '.') {
			if (isFindPoint)	return 0;
			else	isFindPoint = true;
		}
		else return 0;
	}
	return ret * negative / point;
}

int GameObject::ParseStringToInt(const char *s) {
	int negative = 1;
	int startPos = 0;
	int ret = 0;
	int length = 0;
	if (s == NULL || *s == '\0')	return 0;
	length = strlen(s);
	if (s[0] == '-')	negative = -1;
	if (s[0] == '+' || s[0] == '-')	startPos++;
	for (int i = startPos; i < length; i++) {
		if ('0' <= s[i] && s[i] <= '9')	ret = ret * 10 + (s[i] - '0');
		else return 0;
	}
	return ret * negative;
}