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

	//모든 데이터를 처음에 초기화
	void InitData();

	//컬러데이터 생성 및 초기화
	void InitColor();

	//버텍스데이터를 기반으로 중앙값 설정 및 초기화
	void InitCenter();

	//GPU 에 넣을 아이디들을 초기화
	void InitGPUId();

	//file 포인터를 받고 매핑을 초기화
	void InitCoordData(FILE* f);

	//file 포인터를 받고 면을 초기화
	void InitFace(FILE* f);

	//file 포인터를 받고 점을 초기화
	void InitVertex(FILE* f);

	//점의 위치를 float*로 일렬로 뽑아내는 함수
	void Setup_VertexPositionToArray();

	//coordination을 int*로 일렬로 뽑아내는 함수
	void Setup_CoordinationToArray();

	//모든 노말벡터 셋업
	void Setup_NormalVector();

	//면의 노말벡터 셋업
	void Setup_FaceNormalVector();

	//점의 노말벡터 셋업
	void Setup_VertexNormalVector();
	
	//tag 설정
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