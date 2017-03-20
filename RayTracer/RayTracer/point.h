#pragma once
#include "Vec3.h"
class point{
public:
	float x, y, z;
	point(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	point(const point& p) {
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
	}
	point() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	point operator+(const Vec3& poi) const {
		point result(x + poi.x, y + poi.y, z + poi.z);
		return result;
	}
	point operator-(const Vec3& poi) const {
		point result(x - poi.x, y - poi.y, z - poi.z);
		return result;
	}
	Vec3 minus(const point& poi) const{
		Vec3 result(x - poi.x, y - poi.y, z - poi.z);
		return result;
	}
	point& operator=(const point& poi) {
		this->x = poi.x;
		this->y = poi.y;
		this->z = poi.z;
		return *this;
	}
    float getdis(const point& pt) const {
        return sqrt((x - pt.x)*(x - pt.x) + (y - pt.y)*(y - pt.y) + (z - pt.z)*(z - pt.z));
    }
};