#pragma once
#include "ray.h"
#include "vertexnormal.h"
class Shape {
public:
    color ambient;
    color diffuse;
    color specular;
    color emission;
    float shininess;
    mat4 transform;
	Shape() {

	}
	virtual vertexnormal findIntersection(ray& theray) {

	}
	~Shape() {

	}
};