#pragma once
#include "point.h"
#include "matrix44.h"

class vertexnormal {
public:
	point vertex;
	Vec3 mynormal;
	vertexnormal() {
		vertex.x = 0;
		vertex.y = 0;
		vertex.z = 0;
		mynormal.x = 0;
		mynormal.y = 0;
		mynormal.z = 0;
	}
	vertexnormal(float x, float y, float z, float nx, float ny, float nz) {
		vertex.x = x;
		vertex.y = y;
		vertex.z = z;
		mynormal.x = nx;
		mynormal.y = ny;
		mynormal.z = nz;
		mynormal.normalize();
	}
    vertexnormal(const point& mypoint, const Vec3& mynormal) {
        vertex = mypoint;
        this->mynormal = mynormal;
		this->mynormal.normalize();
    }
    vertexnormal transf(matrix44 mat) {
        vertexnormal newvn;
        float tmp1[4] = { vertex.x, vertex.y, vertex.z, 1 };
        float tmp2[4] = { mynormal.x, mynormal.y, mynormal.z, 0 };
        float res[4];
        for (int i = 0; i < 4; i++) {
            res[i] = 0;
            for (int j = 0; j < 4; j++) {
                res[i] += mat.matrix[i][j] * tmp1[j];
            }
        }
        newvn.vertex = point(res[0], res[1], res[2]);
        mat = matrix44::transpose(matrix44::inverse(mat));
        for (int i = 0; i < 4; i++) {
            res[i] = 0;
            for (int j = 0; j < 4; j++) {
                res[i] += mat.matrix[i][j] * tmp2[j];
            }
        }
        newvn.mynormal = Vec3::normalize(Vec3(res[0], res[1], res[2]));
        return newvn;
    }
};