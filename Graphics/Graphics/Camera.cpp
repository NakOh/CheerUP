#include "Camera.h"

Vec4 cameraPosition;
Vec4 cameraDirection;


void CameraInit() {
	cameraPosition = Vec4();
	cameraDirection = Vec4();
	cameraPosition.z = 10;
}