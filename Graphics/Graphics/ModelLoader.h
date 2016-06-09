#pragma once

#define _CRT_SECURE_NO_WARNINGS


#ifndef __MODEL_LOADER__
#define __MODEL_LOADER__

#include "ShaderID.h"

class Vertex {
public:
	Vec4 pos, normal, sum_normal, color;
	Vertex();
};

namespace NameModels {
	class Object {
	public:
		int vertexCount, faceCount, textureCount;
		Vertex* vertices;
		Vec4* coorddata;
		GLfloat* colordata;
		Point4* faces;
		Point4* coords;

		Object() {}
		~Object() {
			delete vertices;
			delete coorddata;
			delete colordata;
			delete faces;
			delete coords;
		}
	};

	class Arrays {
	public:
		GLfloat* vertexPositionArray;
		Vec4* faceNormalVector;
		GLfloat* vertexNormalArray;
		GLfloat* vertexCoordArray;

		Arrays() {}
		~Arrays() {
			delete vertexPositionArray;
			delete faceNormalVector;
			delete vertexNormalArray;
			delete vertexCoordArray;
		}
	};
};

class Model {
private:
	float ParseStringToFloat(const char *s);
	int ParseStringToInt(const char *s);

public:
	NameModels::Arrays arrays;
	NameModels::Object model;

	//ShaderID shaderID;

	//모든 데이터를 처음에 초기화
	void InitData();

	//컬러데이터 생성 및 초기화
	void InitColor();

	//버텍스데이터를 기반으로 중앙값 설정 및 초기화
	void InitCenter();

	//GPU 에 넣을 아이디들을 초기화
	//void InitGPUId();

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

	//file 포인터를 받고 매핑을 초기화
	void InitCoordData(FILE* f);

	//file 포인터를 받고 면을 초기화
	void InitFace(FILE* f);

	//file 포인터를 받고 점을 초기화
	void InitVertex(FILE* f);

	void makeModel(const char* path);

	Model() {}

	Model(const char* path) {
		makeModel(path);
	}
};

Model* copyModel(Model* model);

#endif