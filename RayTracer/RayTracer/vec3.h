#pragma once
#include <cmath>
#include "normal.h"
class Vec3 {
public:
	float x;
	float y;
	float z;

	Vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	};
	Vec3() {
        this->x = this->y = this->z = 0.0;
	}
	Vec3(const Vec3& other) {
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}

	Vec3 operator+ (const Vec3& vec) const {
		Vec3 result(x + vec.x, y + vec.y, z + vec.z);
		return result;
	};
	Vec3 operator - (const Vec3& vec) const {
		Vec3 result(x - vec.x, y - vec.y, z - vec.z);
		return result;
	};
	Vec3 operator* (float index) const {
		Vec3 result(x*index, y*index, z*index);
		return result;
	};
	Vec3 operator/ (float index) const {
		Vec3 result(x / index, y / index, z / index);
		return result;
	};


	Vec3& operator=(const Vec3& other) {
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return *this;
	};


	Vec3 negative() const {
		return Vec3(-this->x, -this->y, -this->z);
	}

	Vec3 normalize() {
		float length = this->getlength();
		if (length == 0) {
			this->x = 0;
			this->y = 0;
			this->z = 0;
			Vec3 result(0, 0, 0);
			*this = result;
		}
		this->x = this->x / length;
		this->y = this->y / length;
		this->z = this->z / length;
		return *this;
	};

    static Vec3 normalize(Vec3 vec) {
        float length = vec.getlength();
        Vec3 res(0, 0, 0);
        if (length == 0) return res;
        res.x = vec.x / length;
        res.y = vec.y / length;
        res.z = vec.z / length;
        return res;
    };

	Vec3 cross(const Vec3& other) {
		Vec3 result(this->y*other.z - this->z*other.y, this->z*other.x - this->x*other.z, this->x*other.y - this->y*other.x);
		return result;
	};

	float dot(const Vec3& other) {
		return this->x*other.x + this->y*other.y + this -> z*other.z;
	}
<<<<<<< HEAD
=======

>>>>>>> origin/master
	float getlength() {
		float length = x*x + y*y + z*z;
		length = pow(length, 0.5f);
		return length;
	};

	
};

