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
	virtual string debug() {
		cout << this->center.x << " " << this->center.y << " " << this->center.z<<" "<<this->radius << endl;
		
		return "";
	}
	virtual vertexnormal findIntersection(ray& theray) {
		//cout << "ray source:"<<theray.source.x << " " << theray.source.y << " " << theray.source.z << endl;
		//cout << "ray dir:" << theray.dir.x << " " << theray.dir.y << " " << theray.dir.z << endl;
		Vec3 Poc = theray.source.minus(this->center);
		float a = theray.dir.dot(theray.dir);
		float b = 2 * theray.dir.dot(Poc);
		float c = Poc.dot(Poc) - this->radius*this->radius;

		float delta = b*b - 4 * a*c;

		if (delta < -eps) {
			return vertexnormal();
		}
        else if (delta >= -eps && delta <= eps) {
            if (b >= 0) return vertexnormal();
            point inter_point = theray.calcPosi(-b/2/a);
            Vec3 normal = inter_point.minus(this->center);
            return vertexnormal(inter_point, Vec3::normalize(normal));
        }
		else {
			float r1 = (-b + pow(delta, 0.5)) / 2 / a;
			float r2 = (-b - pow(delta, 0.5)) / 2 / a;
            if (r1 < 0) return vertexnormal();
			else if (r2 > 0) {
				point inter_point=theray.calcPosi(r2);
				Vec3 normal = inter_point.minus(this->center);
                return vertexnormal(inter_point, Vec3::normalize(normal));
			}
			else {
				//ray source inside the sphere
                //cout << "inside" << endl;
				point inter_point = theray.calcPosi(r1);
				Vec3 normal = this->center.minus(inter_point);
                return vertexnormal(inter_point, Vec3::normalize(normal).negative());
			}
		}
	}
};