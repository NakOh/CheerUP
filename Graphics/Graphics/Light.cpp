
#include "Light.h"

/*
void CamNLightInit() {
	light = Vec4(8, 20, -15, 1);
	light.w = 1;
	camera = Vec4(0, 0, -3, 1);
	camera_dir = Vec4(0, 0, 1, 1);
	for (int i = 0; i < 16; i++)	cam_RotMatrix_X[i] = cam_RotMatrix_Y[i] = cam_RotMatrix_Z[i] = 0;
	for (int i = 0; i < 4; i++)		cam_RotMatrix_X[i * 5] = cam_RotMatrix_Y[i * 5] = cam_RotMatrix_Z[i * 5] = 1;

}

void CamRotation(float x, float y, float z) {
	camera_dir.x = x;
	camera_dir.y = y;
	camera_dir.z = z;

	cam_RotMatrix_X[5] = cos(camera_dir.x);
	cam_RotMatrix_X[6] = sin(camera_dir.x);
	cam_RotMatrix_X[9] = -sin(camera_dir.x);
	cam_RotMatrix_X[10] = cos(camera_dir.x);

	cam_RotMatrix_Y[0] = cos(camera_dir.y);
	cam_RotMatrix_Y[2] = -sin(camera_dir.y);
	cam_RotMatrix_Y[8] = sin(camera_dir.y);
	cam_RotMatrix_Y[10] = cos(camera_dir.y);

	cam_RotMatrix_Z[0] = cos(camera_dir.z);
	cam_RotMatrix_Z[1] = sin(camera_dir.z);
	cam_RotMatrix_Z[4] = -sin(camera_dir.z);
	cam_RotMatrix_Z[5] = cos(camera_dir.z);
}
*/
//*
void Light::Init(float x, float y, float z) {
	pos = Vec4(x, y, z, 1);
	pos.w = 1;
}

void Camera::Init() {
	pos = Vec4(0, 0, -3, 1);
	direction = Vec4();
	for (int i = 0; i < 16; i++)	X_axis_RotationMatrix[i] = Y_axis_RotationMatrix[i] = Z_axis_RotationMatrix[i] = 0;
	for (int i = 0; i < 4; i++)		X_axis_RotationMatrix[i * 5] = Y_axis_RotationMatrix[i * 5] = Z_axis_RotationMatrix[i * 5] = 1;
}

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
//*/