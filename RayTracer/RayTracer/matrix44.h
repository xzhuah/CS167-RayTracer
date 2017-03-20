#pragma once
#include "vec3.h"

class matrix44 {
public:
	float matrix[4][4];
    matrix44();
    matrix44(const float);
	matrix44(const float[4][4]);

	//static matrix44 createMatrix44(float rotateX, float rotateY, float rotateZ, float tran_x, float tran_y, float tran_z, float scale_x, float scale_y, float scale_z);
	static matrix44 createScaleMatrix44(float scale_x, float scale_y, float scale_z);

	static matrix44 createRotateMatrix44(float degrees, const Vec3& axis);
	static matrix44 createTranslateMatrix44(float tran_x, float tran_y, float tran_z);

	void normalize();

    matrix44 operator+(const matrix44&) const;
    matrix44 operator*(const float&) const;
	matrix44 operator*(const matrix44&) const;

	static matrix44 inverse(const matrix44&);
	static matrix44 transpose(const matrix44&);
};
matrix44::matrix44() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            matrix[i][j] = 0;
}
matrix44::matrix44(const float x) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            matrix[i][j] = 0;
    for (int i = 0; i < 4; i++) matrix[i][i] = x;
}
matrix44::matrix44(const float the_matrix[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->matrix[i][j] = the_matrix[i][j];
		}
	}
};

/*
matrix44 matrix44::createMatrix44(float rotateX, float rotateY, float rotateZ, float tran_x, float tran_y, float tran_z, float scale_x, float scale_y, float scale_z) {
	matrix44 scale = matrix44::createScaleMatrix44(scale_x, scale_y, scale_z);
	matrix44 rotate = matrix44::createRotateMatrix44(rotateX, rotateY, rotateZ);
	matrix44 tran = matrix44::createTranslateMatrix44(tran_x, tran_y, tran_z);
	matrix44 result = rotate*scale;
	result = result*tran;
	return result;
}
*/
matrix44  matrix44::createScaleMatrix44(float scale_x, float scale_y, float scale_z) {
	float scale[4][4] = {
		{ scale_x,	0,	0,	0 },
		{ 0,	scale_y,	0,	0 },
		{ 0,	0,	scale_z,	0 },
		{ 0,	0,	0,	1 }
	};
	matrix44 result(scale);
	return result;

}

matrix44 matrix44::createRotateMatrix44(float degrees, const Vec3& axis) {
    const float PI = 3.14159265;
    matrix44 ret;
    matrix44 myIdentity = matrix44(1);
    float tmp1[4][4] = { axis.x*axis.x, axis.x*axis.y, axis.x*axis.z, 0,
                        axis.x*axis.y, axis.y*axis.y, axis.y*axis.z, 0,
                        axis.x*axis.z, axis.y*axis.z, axis.z*axis.z, 0,
                        0,0,0,0 };
    matrix44 myAAT = matrix44(tmp1);
    float tmp2[4][4] = { 0, -axis.z, axis.y, 0,
                        axis.z, 0, -axis.x, 0,
                        -axis.y, axis.x, 0, 0,
                        0,0,0,0 };
    matrix44 myAstar = matrix44(tmp2);
    // You will change this return call
    ret = myIdentity*cos(degrees*PI / 180.0) + myAAT*(1 - cos(degrees*PI / 180.0)) + myAstar*sin(degrees*PI / 180.0);
    ret.matrix[3][3] = 1;
	return ret;
}
matrix44 matrix44::createTranslateMatrix44(float tran_x, float tran_y, float tran_z) {
	float scale[4][4] = {
		{ 0,	0,	0,	tran_x },
		{ 0,	0,	0,	tran_y },
		{ 0,	0,	0,	tran_z },
		{ 0,	0,	0,	1 }
	};
	matrix44 result(scale);
	return result;
}
void matrix44::normalize() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->matrix[i][j] /= this->matrix[3][3];
		}
	}
}

matrix44 matrix44::operator+(const matrix44& mat) const {
    float result[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = this->matrix[i][j] + mat.matrix[i][j];
        }
    }
    matrix44 final(result);
    return final;
}
matrix44 matrix44::operator*(const float& x) const {
    float result[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = this->matrix[i][j] * x;
        }
    }
    matrix44 final(result);
    return final;
}
matrix44 matrix44::operator*(const matrix44& other) const {
	float result[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float ele = 0;
			for (int k = 0; k < 4; k++) {
				ele += this->matrix[i][k] * other.matrix[k][j];
			}
			result[i][j] = ele;
		}
	}
	matrix44 final(result);
	return final;
}

matrix44 matrix44::inverse(const matrix44& mat) {
    
}
matrix44 matrix44::transpose(const matrix44& mat) {
	float result[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[i][j] = mat.matrix[j][i];
		}
	}
	matrix44 final(result);
	return final;
}