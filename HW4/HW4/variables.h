/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

// This is the basic include file for the global variables in the program.  
// Since all files need access to it, we define  as either blank or 
// , depending on if included in the main program or not.  

const float EPS = 1e-5;

int width = 500, height = 500 ; // width and height 
int maxdepth = 5;
camera mycamera;

// Lighting parameter array, similar to that in the fragment shader
struct Light {
    int type;
    Vec3 dir;
    color c;
};
vector<Light> lights;

// Materials (read from file) 
// With multiple objects, these are colors for each.
color ambient; 
color diffuse;
color specular;
color emission;
float shininess;

float attenuation_const, attenuation_linear, attenuation_quadratic;

// For multiple objects, read from a file.
vector<Shape> objects;
vector<point> vertices;
vector<vertexnormal> vtns;


