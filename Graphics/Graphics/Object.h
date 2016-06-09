#pragma once
#include "TagHeader.h"
#include "Matrix.h"
#include "Light.h"
#include <fstream>

using namespace std;



GLuint loadBMP_custom(const char * imagepath);

class Vertex {
public:
	Vec4 pos, normal, sum_normal, color;
	Vertex();
};

/*
class Bitmap {
public:

	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
							  // Actual RGB data
	unsigned char * data;

	Bitmap() {}
	Bitmap(const char * imagepath);

	GLuint loadBMP_custom(const char * imagepath);

	void registerImage();

};
*/

class GameObject;

class ShaderID {
protected:
	float aspect = 1024/768;
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
	ShaderID() {}
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
	void Render(GameObject& obj, int textureNumber);
	void setAspect(float as);
};

class Transform {
private:
	void Init() {
		position = Vec4();
		rotation = Vec4();
		scale = Vec4(1, 1, 1, 1);
	}
public:
	Transform() {
		Init();
	}
	Transform(GameObject* parent) {
		Init();
		gameObject = parent;
	}
	GameObject* gameObject;
	Vec4 position;
	Vec4 rotation;
	Vec4 scale;

	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void Translation(float x, float y, float z);
	void Scalelation(float x, float y, float z);

	void Rotation(float x, float y, float z);


};

namespace Model {
	class Object {
	public:
		int vertexCount, faceCount, textureCount;
		Vertex* vertices;
		Vec4* coorddata;
		GLfloat* colordata;
		Point4* faces;
		Point4* coords;
	};

	class Arrays {
	public:
		GLfloat* vertexPositionArray;
		Vec4* faceNormalVector;
		GLfloat* vertexNormalArray;
		GLfloat* vertexCoordArray;
	};
};

class AxisMatrix {
public:
	GLfloat _X_axis_RotationMatrix[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
	GLfloat _Y_axis_RotationMatrix[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
	GLfloat _Z_axis_RotationMatrix[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
};

class GameObject {
protected:
	ShaderID shaderID;

	//��� �����͸� ó���� �ʱ�ȭ
	void InitData();

	//�÷������� ���� �� �ʱ�ȭ
	void InitColor();

	//���ؽ������͸� ������� �߾Ӱ� ���� �� �ʱ�ȭ
	void InitCenter();

	//GPU �� ���� ���̵���� �ʱ�ȭ
	void InitGPUId();

	//file �����͸� �ް� ������ �ʱ�ȭ
	void InitCoordData(FILE* f);

	//file �����͸� �ް� ���� �ʱ�ȭ
	void InitFace(FILE* f);

	//file �����͸� �ް� ���� �ʱ�ȭ
	void InitVertex(FILE* f);

	//���� ��ġ�� float*�� �Ϸķ� �̾Ƴ��� �Լ�
	void Setup_VertexPositionToArray();

	//coordination�� int*�� �Ϸķ� �̾Ƴ��� �Լ�
	void Setup_CoordinationToArray();

	//��� �븻���� �¾�
	void Setup_NormalVector();

	//���� �븻���� �¾�
	void Setup_FaceNormalVector();

	//���� �븻���� �¾�
	void Setup_VertexNormalVector();
	
	//tag ����
	void Setup_Tag(int tag);

	float ParseStringToFloat(const char *s);
	int ParseStringToInt(const char *s);

	void init_GameObject(const char* path, Camera* camera, Light* light, int tag);

public:
	Camera* camera;
	Light* light;
	int tag;
	Model::Arrays arrays;
	Model::Object model;
	Transform transform;
	GameObject() {}
	GameObject(const char* path, Camera* camera, Light* light, int tag);
	AxisMatrix _axisRotation;
	void draw();
	void setAspect(float as);
	virtual void update(int delta) = 0;
};