
#include "Matrix.h"
#include <math.h>

void Vec4::Add(Vec4& other) {
	x += other.x;
	y += other.y;
	z += other.z;
}

void Vec4::Add(float x, float y, float z) {
	this->x += x;
	this->y += y;
	this->z += z;
}

void Vec4::Sub(Vec4& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

void Vec4::Divide(float d) {
	x /= d;
	y /= d;
	z /= d;
}

void Vec4::Mul(float d) {
	x *= d;
	y *= d;
	z *= d;
}

float Vec4::Dot(Vec4* a, Vec4* b) {
	float ret = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
	return ret;
}

Vec4* Vec4::Cross(Vec4* a, Vec4* b) {
	Vec4* ret = new Vec4();
	ret->x = a->y * b->z - a->z * b->y;
	ret->y = a->z * b->x - a->x * b->z;
	ret->z = a->x * b->y - a->y * b->x;
	return ret;
}

float Vec4::CrossX(Vec4* a, Vec4* b) {
	return a->y * b->z - a->z * b->y;
}

float Vec4::CrossY(Vec4* a, Vec4* b) {
	return a->z * b->x - a->x * b->z;
}

float Vec4::CrossZ(Vec4* a, Vec4* b) {
	return a->x * b->y - a->y * b->x;
}

Vec4::Vec4() {
	x = y = z = 0;
	w = 1;
}

Vec4::Vec4(float a, float b, float c, float d) {
	x = a;
	y = b;
	z = c;
	w = d;
}

void Vec4::normalize() {
	float dist = sqrt(x * x + y * y + z * z);
	x = x / dist;
	y = y / dist;
	z = z / dist;
	w = 1;
}


//*
Vec4& Vec4::operator=(Vec4& a) {
	x = a.x;
	y = a.y;
	z = a.z;
	w = a.w;
	return *this;
}

Vec4 Vec4::operator+(Vec4& a) { return Vec4(a.x + x, a.y + y, a.z + z, 1); }
Vec4 Vec4::operator-(Vec4& a) { return Vec4(a.x - x, a.y - y, a.z - z, 1); }
Vec4 Vec4::operator*(Vec4& a) { return Vec4(a.x * x, a.y * y, a.z * z, 1); }
Vec4 Vec4::operator*(float a) { return Vec4(a * x, a * y, a * z, 1); }
//*/

//*
Vec4 operator*(float a, Vec4 ref) {
	return Vec4(a * ref.x, a * ref.y, a * ref.z, 1);
}
//*/


void Vec4::rotX(float theta) {
	Matrix3 r = Matrix3();
	float sinT = sin(theta);
	r.d[0][0] = 1;
	r.d[2][2] = r.d[1][1] = cos(theta);
	r.d[2][1] = sinT;
	r.d[1][2] = -sinT;

	x = x;
	y = y * r.d[1][1] + z * r.d[1][2];
	z = y * r.d[2][1] + z * r.d[2][2];
}

void Vec4::rotY(float theta) {
	Matrix3 r = Matrix3();
	float sinT = sin(theta);
	r.d[1][1] = 1;
	r.d[0][0] = r.d[2][2] = cos(theta);
	r.d[0][2] = sinT;
	r.d[2][0] = -sinT;

	x = x * r.d[0][0] + z * r.d[0][2];
	y = y;
	z = x * r.d[2][0] + z * r.d[2][2];
}

void Vec4::rotZ(float theta) {
	Matrix3 r = Matrix3();
	float sinT = sin(theta);
	r.d[2][2] = 1;
	r.d[0][0] = r.d[1][1] = cos(theta);
	r.d[1][0] = sinT;
	r.d[0][1] = -sinT;

	x = x * r.d[0][0] + y * r.d[0][1];
	y = x * r.d[1][0] + y * r.d[1][1];
	z = z;
}

bool Vec4::isColl(Vec4& other, float dist) {
	float dx = other.x - x;
	float dy = other.y - y;
	float dz = other.z - z;
	return dx * dx + dy * dy + dz * dz <= dist * dist;
}

Point4::Point4() {
	for (int i = 0; i < 4; i++)	p[i] = 0;
}

Point4::Point4(int a, int b, int c, int d) {
	p[0] = a;
	p[1] = b;
	p[2] = c;
	p[3] = d;
}



Matrix4::Matrix4() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			d[i][j] = 0;
}

Matrix4* Matrix4::Mult(Matrix4* a, Matrix4* b) {
	Matrix4* ret = new Matrix4();
	float sum;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			sum = 0;
			for (int k = 0; k < 4; k++)
				sum += a->d[i][k] * b->d[k][j];
			ret->d[i][j] = sum;
		}
	return ret;
}

Matrix3::Matrix3() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			d[i][j] = 0;
}

Matrix3* Matrix3::Mult(Matrix3* a, Matrix3* b) {
	Matrix3* ret = new Matrix3();
	float sum;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			sum = 0;
			for (int k = 0; k < 3; k++)
				sum += a->d[i][k] * b->d[k][j];
			ret->d[i][j] = sum;
		}
	return ret;
}