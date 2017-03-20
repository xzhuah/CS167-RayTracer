#pragma once
#include "variables.h"
#include "Shape.h"
#include "vertexnormal.h"
#include <cmath>

class sphere: public Shape {
public:
	point center;
	float radius;
	sphere(point& center, float radius) {
		this->center = center;
		this->radius = radius;
	}
	virtual vertexnormal findIntersection(ray& theray) {
		Vec3 Poc = theray.source.minus(this->center);
		float a = theray.dir.dot(theray.dir);
		float b = 2 * theray.dir.dot(Poc);
		float c = Poc.dot(Poc) - this->radius*this->radius;

		float delta = b*b - 4 * a*c;

		if (delta < -EPS) {
			return vertexnormal();
		}
        else if (delta >= -EPS && delta <= EPS) {
            point inter_point = theray.calcPosi(-b/2/a);
            Vec3 normal = inter_point.minus(this->center);
            return vertexnormal(inter_point, glm::normalize(normal));
        }
		else {
			float r1 = (-b + pow(delta, 0.5)) / 2 / a;
			float r2 = (-b - pow(delta, 0.5)) / 2 / a;
			if (r2 > 0) {
				point inter_point=theray.calcPosi(r2);
				Vec3 normal = inter_point.minus(this->center);
                return vertexnormal(inter_point, glm::normalize(normal));
			}
			else {
				//ray source inside the sphere
				point inter_point = theray.calcPosi(r1);
				Vec3 normal = this->center.minus(inter_point);
                return vertexnormal(inter_point, glm::normalize(normal));
			}
		}
	}
};