#pragma once
#include "point.h"
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
	}
    vertexnormal(const point& mypoint, const Vec3& mynormal) {
        vertex = mypoint;
        this->mynormal = mynormal;
    }
};