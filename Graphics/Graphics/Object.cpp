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


GLuint ShaderID::loadBMP_custom(const char * imagepath) {
	FILE * file = fopen(imagepath, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }

	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return 0;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

										 // Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);
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



void ShaderID::SetMetrices(Vec4& scale) {
	for (int i = 0; i < 16; i++)	modelMatrix[i] = viewMatrix[i] = orthoMatrix[i] = scalelationMatrix[i] = projMatrix[i] = 0;
	for (int i = 0; i < 4; i++)		modelMatrix[i * 5] = viewMatrix[i * 5] = orthoMatrix[i * 5] = 1;
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
	makeCheckImage();
	GLuint image = loadBMP_custom("models/tree.bmp");

	textureID = glGetAttribLocation(mainID, "vertexTexture");
	texCoordID = glGetUniformLocation(mainID, "tex");

	glActiveTexture(GL_TEXTURE0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, MAX_PIXEL, MAX_PIXEL, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

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

void ShaderID::Render(bool isPerspective,
	Vec4& scale, GLfloat* X_axis_Rot, GLfloat* Y_axis_Rot, GLfloat* Z_axis_Rot,
	Vec4& position, GLfloat* vertexPositionArray, GLfloat* colorData, GLfloat* vertexNormalArray, GLfloat* vertexCoordArray, Camera& cam, Light& light, int faceCount ){

	SetMetrices(scale);

	glUseProgram(mainID);

	glUniform1i(textureID, 0);

	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0]);
	if (isPerspective) glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projMatrix[0]);
	else glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &orthoMatrix[0]);
	glUniformMatrix4fv(xAxisRotationMatrixID, 1, GL_FALSE, &X_axis_Rot[0]);
	glUniformMatrix4fv(yAxisRotationMatrixID, 1, GL_FALSE, &Y_axis_Rot[0]);
	glUniformMatrix4fv(zAxisRotationMatrixID, 1, GL_FALSE, &Z_axis_Rot[0]);
	glUniformMatrix4fv(scaleMatrixID, 1, GL_FALSE, &scalelationMatrix[0]);
	//glUniformMatrix4fv(camXAxisRotationMatrixID, 1, GL_FALSE, &Camera::X_axis_RotationMatrix[0]);
	//glUniformMatrix4fv(camYAxisRotationMatrixID, 1, GL_FALSE, &Camera::Y_axis_RotationMatrix[0]);
	//glUniformMatrix4fv(camZAxisRotationMatrixID, 1, GL_FALSE, &Camera::Z_axis_RotationMatrix[0]);
	glUniformMatrix4fv(camXAxisRotationMatrixID, 1, GL_FALSE, &cam.X_axis_RotationMatrix[0]);
	glUniformMatrix4fv(camYAxisRotationMatrixID, 1, GL_FALSE, &cam.Y_axis_RotationMatrix[0]);
	glUniformMatrix4fv(camZAxisRotationMatrixID, 1, GL_FALSE, &cam.Z_axis_RotationMatrix[0]);

	glUniform4f(centerPositionID, position.x, position.y, position.z, 1);
	glUniform4f(lightPositionID, light.pos.x, light.pos.y, light.pos.z, 1);
	glUniform4f(cameraPositionID, cam.pos.x, cam.pos.y, cam.pos.z, 1);

	glEnableVertexAttribArray(vertexPositionID);
	glEnableVertexAttribArray(vertexColorID);
	glEnableVertexAttribArray(vertexNormalID);
	//texture
	glEnableVertexAttribArray(textureID);

	glVertexAttribPointer( vertexPositionID, 4, GL_FLOAT, GL_FALSE, 0, (void*)&vertexPositionArray[0] );
	glVertexAttribPointer( vertexColorID, 4, GL_FLOAT,	GL_FALSE, 0, (void*)&colorData[0] );
	glVertexAttribPointer( vertexNormalID, 4, GL_FLOAT, GL_FALSE, 0, (void*)&vertexNormalArray[0] );
	//texture
	glVertexAttribPointer(textureID, 2, GL_FLOAT, GL_FALSE, 0, (void*)&vertexCoordArray[0]);

	glDrawArrays(GL_TRIANGLES, 0, faceCount * 3);

	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(vertexColorID);
	glDisableVertexAttribArray(lightPositionID);

	//glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);
}

void ShaderID::makeCheckImage() {
	int i, j, c;
	for (i = 0; i < MAX_PIXEL; i++) {
		for (j = 0; j < MAX_PIXEL; j++) {
			c = 255 - ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			checkImage[i][j][0] = c;
			checkImage[i][j][1] = c;
			checkImage[i][j][2] = c;
			checkImage[i][j][3] = 1;
		}
	}
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



void GameObject::InitGPUId() {
	shaderID.Init();
	//gouraudID.Init();
}

void GameObject::InitFace(FILE* f, bool objFile) {
	//의미없이 셋을 날림.
	char ssss[100];
	for (int i = 0; i < 3; i++)	
		fscanf(f, "%s", &ssss);
	model.faceCount = ParseStringToInt(ssss);
	model.faces = new Point4[model.faceCount];
	model.coords = new Point4[model.faceCount];
	if (objFile) {
		for (int i = 0; i < model.faceCount; i++) {
			fscanf(f, "%d/%d %d/%d %d/%d\n", &model.faces[i].p[0], &model.coords[i].p[0], &model.faces[i].p[1], &model.coords[i].p[1], &model.faces[i].p[2], &model.coords[i].p[2]);
			printf("%d/%d %d/%d %d/%d\n", model.faces[i].p[0], model.coords[i].p[0], model.faces[i].p[1], model.coords[i].p[1], model.faces[i].p[2], model.coords[i].p[2]);
			for (int j = 0; j < 3; j++) {
				model.faces[i].p[j] --;
				model.coords[i].p[j]--;
			}
		}
	}
	else
		for (int i = 0; i < model.faceCount; i++)	fscanf(f, "%d %d %d\n", &model.faces[i].p[0], &model.faces[i].p[1], &model.faces[i].p[2]);
}

void GameObject::InitCoordData(FILE* f, bool objFile) {
	//의미없이 셋을 날림.
	if (objFile) {
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
	else {
		model.coorddata = new Vec4[model.vertexCount * 3];
		for (int i = 0; i < model.vertexCount * 3; i++)	model.coorddata[i].x = model.coorddata[i].y = model.coorddata[i].z = 0;
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

GameObject::GameObject(const char* path, bool objFile) {

	//makeCheckImage();
	transform = Transform(this);

	FILE* f = fopen(path, "rt");

	InitVertex(f);
	InitCoordData(f, objFile);
	InitFace(f, objFile);
	fclose(f);

	InitColor();
	InitCenter();
	InitGPUId();

	InitData();
}

void Transform::SetPosition(float x, float y, float z) {
	int dx, dy, dz;
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
			arrays.vertexCoordArray[(i * 3 + k) * 4 + 0] = model.coorddata[coordIndex].x;
			arrays.vertexCoordArray[(i * 3 + k) * 4 + 1] = model.coorddata[coordIndex].y;
			arrays.vertexCoordArray[(i * 3 + k) * 4 + 2] = model.coorddata[coordIndex].z;
			arrays.vertexCoordArray[(i * 3 + k) * 4 + 3] = 1;
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

/*
void Camera::Rotation(float x, float y, float z) {
	direction.x += x;
	direction.y += y;
	direction.z += z;
	X_axis_RotationMatrix[5] = cos(direction.x);
	X_axis_RotationMatrix[6] = sin(direction.x);
	X_axis_RotationMatrix[9] = -sin(direction.x);
	X_axis_RotationMatrix[10] = cos(direction.x);

	Y_axis_RotationMatrix[0] = cos(direction.y);
	Y_axis_RotationMatrix[2] = -sin(direction.y);
	Y_axis_RotationMatrix[8] = sin(direction.y);
	Y_axis_RotationMatrix[10] = cos(direction.y);

	Z_axis_RotationMatrix[0] = cos(direction.z);
	Z_axis_RotationMatrix[1] = sin(direction.z);
	Z_axis_RotationMatrix[4] = -sin(direction.z);
	Z_axis_RotationMatrix[5] = cos(direction.z);

}
*/

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

void GameObject::Draw(Camera& cam, Light& light) {
	shaderID.Render(true, transform.scale, _axisRotation._X_axis_RotationMatrix,
		_axisRotation._Y_axis_RotationMatrix, _axisRotation._Z_axis_RotationMatrix, transform.position, arrays.vertexPositionArray,
		model.colordata, arrays.vertexNormalArray, arrays.vertexCoordArray, cam, light, model.faceCount);
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