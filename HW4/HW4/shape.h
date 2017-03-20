#pragma once
#include "ray.h"
#include "vertexnormal.h"
#include "matrix44.h"
#include <iostream>
class Shape {
public:
    color ambient;
    color diffuse;
    color specular;
    color emission;
    float shininess;
    matrix44 transform;
	Shape() {

	}
	virtual vertexnormal findIntersection(ray& theray) {
		std::cout << "not" << std::endl;
		return vertexnormal();
	}
	~Shape() {

	}
};