#include "Object.h"
#include <stdlib.h>
#include <string>
#include <iostream>


#include <GL\glut.h>
#include "shader.hpp"
#include "Matrix.h"
#include <math.h>


#include "GameObjectManager.h"

using namespace std;


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


void GameObject::Setup_Tag(int tag) {
	this->tag = tag;
}

void GameObject::init_GameObject(Model* model, GameObjectManager* manager, int tag) {

	transform = Transform(this);
	this->manager = manager;

	this->body = copyModel(model);

	Setup_Tag(tag);
}

GameObject::GameObject(Model* model, GameObjectManager* manager, int tag) {
	init_GameObject(model, manager, tag);
}

GameObject::~GameObject() {
	delete body;
}

void Transform::SetPosition(float x, float y, float z) {
	float dx, dy, dz;
	dx = x - position.x;
	dy = y - position.y;
	dz = z - position.z;
	position.x = x;
	position.y = y;
	position.z = z;

	for (int i = 0; i < gameObject->body->model.vertexCount; i++) {
		gameObject->body->model.vertices[i].pos.x += dx;
		gameObject->body->model.vertices[i].pos.y += dy;
		gameObject->body->model.vertices[i].pos.z += dz;
	}

	for (int i = 0; i < gameObject->body->model.faceCount; i++) {
		for (int k = 0; k < 3; k++) {
			int vertIndex = gameObject->body->model.faces[i].p[k];
			gameObject->body->arrays.vertexPositionArray[(i * 3 + k) * 4 + 0] = gameObject->body->model.vertices[vertIndex].pos.x;
			gameObject->body->arrays.vertexPositionArray[(i * 3 + k) * 4 + 1] = gameObject->body->model.vertices[vertIndex].pos.y;
			gameObject->body->arrays.vertexPositionArray[(i * 3 + k) * 4 + 2] = gameObject->body->model.vertices[vertIndex].pos.z;
			gameObject->body->arrays.vertexPositionArray[(i * 3 + k) * 4 + 3] = 1;
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



void Transform::Translation(float x, float y, float z) {
	position.Add(x, y, z);
	for (int i = 0; i < gameObject->body->model.vertexCount; i++)	gameObject->body->model.vertices[i].pos.Add(x, y, z);
	for (int i = 0; i < gameObject->body->model.faceCount; i++) {
		for (int k = 0; k < 3; k++) {
			int vertIndex = gameObject->body->model.faces[i].p[k];
			gameObject->body->arrays.vertexPositionArray[(i * 3 + k) * 4 + 0] = gameObject->body->model.vertices[vertIndex].pos.x;
			gameObject->body->arrays.vertexPositionArray[(i * 3 + k) * 4 + 1] = gameObject->body->model.vertices[vertIndex].pos.y;
			gameObject->body->arrays.vertexPositionArray[(i * 3 + k) * 4 + 2] = gameObject->body->model.vertices[vertIndex].pos.z;
			gameObject->body->arrays.vertexPositionArray[(i * 3 + k) * 4 + 3] = 1;
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

