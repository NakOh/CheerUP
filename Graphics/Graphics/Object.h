#pragma once
#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "TagHeader.h"
#include "Light.h"
#include "ModelLoader.h"
#include "ShaderID.h"

using namespace std;

class GameObject;
class GameObjectManager;

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



class AxisMatrix {
public:
	GLfloat _X_axis_RotationMatrix[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
	GLfloat _Y_axis_RotationMatrix[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
	GLfloat _Z_axis_RotationMatrix[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
};

class GameObject {
protected:
	//tag ¼³Á¤
	void Setup_Tag(int tag);
	void init_GameObject(Model* model, GameObjectManager* manager, int tag);

public:
	GameObjectManager* manager;
	int tag;
	Model* body;

	Transform transform;
	AxisMatrix _axisRotation;

	bool isColl(GameObject* other, float dist) {
		transform.position.isColl(other->transform.position, dist);
	}

	GameObject() {}
	~GameObject();
	GameObject(Model* model, GameObjectManager* manager, int tag);

	virtual void update(int delta) = 0;
};


#endif // !__OBJECT_H__