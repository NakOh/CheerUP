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

	//��� �����͸� ó���� �ʱ�ȭ
	void InitData();

	//�÷������� ���� �� �ʱ�ȭ
	void InitColor();

	//���ؽ������͸� ������� �߾Ӱ� ���� �� �ʱ�ȭ
	void InitCenter();

	//GPU �� ���� ���̵���� �ʱ�ȭ
	//void InitGPUId();

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

	//file �����͸� �ް� ������ �ʱ�ȭ
	void InitCoordData(FILE* f);

	//file �����͸� �ް� ���� �ʱ�ȭ
	void InitFace(FILE* f);

	//file �����͸� �ް� ���� �ʱ�ȭ
	void InitVertex(FILE* f);

	void makeModel(const char* path);

	Model() {}

	Model(const char* path) {
		makeModel(path);
	}
};

Model* copyModel(Model* model);

#endif