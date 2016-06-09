#define _CRT_SECURE_NO_WARNINGS

#include "ShaderID.h"
#include "Object.h"
#include "GameObjectManager.h"

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

void ShaderID::InitBitmap() {
	int textureNumber = 4;
	texID = (GLuint*)malloc(sizeof(GLuint) * textureNumber);
	glGenTextures(textureNumber, &texID[0]);

	glBindTexture(GL_TEXTURE_2D, texID[0]);
	loadBMP_custom("models/check.bmp");

	glBindTexture(GL_TEXTURE_2D, texID[1]);
	loadBMP_custom("models/flight.bmp");

	glBindTexture(GL_TEXTURE_2D, texID[2]);
	loadBMP_custom("models/flight_enemy.bmp");

	glBindTexture(GL_TEXTURE_2D, texID[3]);
	loadBMP_custom("models/basicMap.bmp");
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

void ShaderID::ObjectInit() {
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


ShaderID::ShaderID() {
	Init();
}

void ShaderID::Init() {
	mainID = shader::LoadShaders("VertexShader.vert", "FragmentShader.frag");
	ObjectInit();
}

void ShaderID::render(GameObject& obj, int textureNumber, bool isPhong) {

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

	glUniformMatrix4fv(camXAxisRotationMatrixID, 1, GL_FALSE, &obj.manager->camera->X_axis_RotationMatrix[0]);
	glUniformMatrix4fv(camYAxisRotationMatrixID, 1, GL_FALSE, &obj.manager->camera->Y_axis_RotationMatrix[0]);
	glUniformMatrix4fv(camZAxisRotationMatrixID, 1, GL_FALSE, &obj.manager->camera->Z_axis_RotationMatrix[0]);

	glUniform4f(centerPositionID, obj.transform.position.x, obj.transform.position.y, obj.transform.position.z, 1);
	glUniform4f(lightPositionID, obj.manager->light->pos.x, obj.manager->light->pos.y, obj.manager->light->pos.z, 1);
	glUniform4f(cameraPositionID, obj.manager->camera->pos.x, obj.manager->camera->pos.y, obj.manager->camera->pos.z, 1);

	glEnableVertexAttribArray(vertexPositionID);
	glEnableVertexAttribArray(vertexColorID);
	glEnableVertexAttribArray(vertexNormalID);
	glEnableVertexAttribArray(textureID);

	glVertexAttribPointer(vertexPositionID, 4, GL_FLOAT, GL_FALSE, 0, (void*)&obj.body->arrays.vertexPositionArray[0]);
	glVertexAttribPointer(vertexColorID, 4, GL_FLOAT, GL_FALSE, 0, (void*)&obj.body->model.colordata[0]);
	if(isPhong)	glVertexAttribPointer(vertexNormalID, 4, GL_FLOAT, GL_FALSE, 0, (void*)&obj.body->arrays.vertexNormalArray[0]);
	else glVertexAttribPointer(vertexNormalID, 4, GL_FLOAT, GL_FALSE, 0, (void*)&obj.body->arrays.faceNormalArray[0]);
	glVertexAttribPointer(textureID, 2, GL_FLOAT, GL_FALSE, 0, (void*)&obj.body->arrays.vertexCoordArray[0]);

	glDrawArrays(GL_TRIANGLES, 0, obj.body->model.faceCount * 3);

	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(vertexColorID);
	glDisableVertexAttribArray(lightPositionID);

	//glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);
}

void ShaderID::setAspect(float as) {
	aspect = as;
}