#ifndef _MATRIX_H_
#define _MATRIX_H_

class Vec4 {
public:
	float x, y, z, w;
	static float Dot(Vec4* a, Vec4* b);
	static float CrossX(Vec4* a, Vec4* b);
	static float CrossY(Vec4* a, Vec4* b);
	static float CrossZ(Vec4* a, Vec4* b);
	static Vec4* Cross(Vec4* a, Vec4* b);
	Vec4();
	Vec4(float a, float b, float c, float d);
	void Normalize();
	void Add(Vec4& other);
	void Add(float x, float y, float z);
	void Sub(Vec4& other);
	void Mul(float d);
	void Divide(float d);

	bool isColl(Vec4& other, float dist);
	//*
	Vec4& operator=(Vec4& a);
	Vec4 operator+(Vec4& a);
	Vec4 operator-(Vec4& a);
	Vec4 operator*(Vec4& a);
	Vec4 operator*(float a);
	friend Vec4 operator*(float a, Vec4 ref);
	//*/
};



class Point4 {
public:
	int p[4];
	Point4();
	Point4(int a, int b, int c, int d);
};

class Matrix4 {
public:
	float d[4][4];
	static Matrix4* Mult(Matrix4* a, Matrix4* b);
	Matrix4();
};


class Matrix3 {
public:
	float d[3][3];
	static Matrix3* Mult(Matrix3* a, Matrix3* b);
	Matrix3();
};

#endif // !_MATRIX_H_


