#pragma once
class color
{
public:
	float r, g, b;
	color() {
		this->r = 0.0f;
		this->g = 0.0f;
		this->b = 0.0f;
	}
	color(float, float ,float);
	color operator+(const color&) const;
	color operator-(const color&) const;
	color operator*(float) const;
	color operator/(float) const;


	color& operator=(const color& other) {
		this->r = other.r;
		this->g = other.g;
		this->b = other.b;
	}


private:

};

color::color(float r, float g, float b) {
	//if (r < 0) r = 0;
	//if (r > 1) r = 1;
	this->r = r;
	this->g = g;
	this->b = b;
}
color color::operator+(const color& col) const {
	color result(this->r + col.r, this->g + col.g, this->b + col.b);
	return result;
}
color color::operator-(const color& col) const {
	color result(this->r - col.r, this->g - col.g, this->b - col.b);
	return result;
}
color color::operator*(float index) const {
	color result(this->r*index, this->g *index, this->b*index);
	return result;
}
color color::operator/(float index) const {
	color result(this->r / index, this->g / index, this->b / index);
	return result;
}


