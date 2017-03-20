#pragma once
#include "point.h"
#include "Vec3.h"

class ray
{
public:
	point source;
	Vec3 dir;
	ray() {}
	ray(point source, Vec3 direction) {
		this->source = source;
		this->dir = glm::normalize(direction);
	}

	point calcPosi(float t) const {
		point result(this->source + dir*t);
		return result;
	}

    ray transf(glm::mat4 mat) {

    }
};