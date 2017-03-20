#pragma once
#include "vertexnormal.h"

class intersection
{
public:
	vertexnormal vertex;
	
	intersection() {
		
	}
	intersection(vertexnormal vertex) {
		this->vertex = vertex;
	
	}
	~intersection() {
		//this->primitive = NULL;
	}

private:

};

