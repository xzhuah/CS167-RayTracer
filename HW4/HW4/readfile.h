/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

/*****************************************************************************/
// This file is readfile.cpp.  It includes helper functions for matrix 
// transformations for a stack (matransform) and to rightmultiply the 
// top of a stack.  These functions are given to aid in setting up the 
// transformations properly, and to use glm functions in the right way.  
// Their use is optional in your program.  
  

// The functions readvals and readfile do basic parsing.  You can of course 
// rewrite the parser as you wish, but we think this basic form might be 
// useful to you.  It is a very simple parser.

// Please fill in parts that say YOUR CODE FOR HW 2 HERE. 
// Read the other parts to get a context of what is going on. 
  
/*****************************************************************************/

// Basic includes to get this file to work.  
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include "point.h"
#include "camera.h"
#include "vertexnormal.h"
#include "vec3.h"
#include "matrix44.h"
#include "color.h"
#include "variables.h"
#include "shape.h"
#include "sphere.h"
#include "triangle.h"

using namespace std;

// You may not need to use the following two functions, but it is provided
// here for convenience

// The function below applies the appropriate transform to a 4-vector
void matransform(stack<matrix44> &transfstack, float* values) 
{
    float tmp[4], res[4];
    matrix44 transform = transfstack.top(); 
    tmp[0] = values[0]; tmp[1] = values[1]; tmp[2] = values[2]; tmp[3] = 1;
    for (int i = 0; i < 4; i++) {
        res[i] = 0;
        for (int j = 0; j < 4; j++) {
            res[i] += transform.matrix[i][j] * tmp[j];
        }
    }
    for (int i = 0; i < 3; i++) values[i] = res[i]; 
}

void rightmultiply(const matrix44 & M, stack<matrix44> &transfstack) 
{
    matrix44 &T = transfstack.top(); 
    T = T * M; 
}

// Function to read the input data values
// Use is optional, but should be very helpful in parsing.  
bool readvals(stringstream &s, const int numvals, float* values) 
{
    for (int i = 0; i < numvals; i++) {
        s >> values[i]; 
        if (s.fail()) {
            cout << "Failed reading value " << i << " will skip\n"; 
            return false;
        }
    }
    return true; 
}

void copyColor(color& c, float* values) {
    c.r = values[0];
    c.g = values[1];
    c.b = values[2];
}

void readfile(const char* filename) 
{
    string str, cmd; 
    ifstream in;
    in.open(filename); 
    if (in.is_open()) {

        // I need to implement a matrix stack to store transforms.  
        // This is done using standard STL Templates 
        stack <matrix44> transfstack; 
        transfstack.push(matrix44(1.0));  // identity

        getline (in, str); 
        while (in) {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
                // Ruled out comment and blank lines 

                stringstream s(str);
                s >> cmd; 
                int i; 
                float values[10]; 
                bool validinput; 

                if (cmd == "size") {
                    validinput = readvals(s, 2, values);
                    if (validinput) {
                        width = (int)values[0];
                        height = (int)values[1];
                    }
                }
                else if (cmd == "maxdepth") {
                    validinput = readvals(s, 1, values);
                    if( validinput ){
                        maxdepth = (int)values[0];
                    }
                }
                // Process the light, add it to database.
                // Lighting Command
                else if (cmd == "point" || cmd == "directional") {
                    validinput = readvals(s, 6, values); // Position /color for lts.
                    if (validinput) {
                        Light tmp;
                        if (cmd == "point") tmp.type = 1;
                        else tmp.type = 0;
                        matransform(transfstack, values);
                        tmp.dir = Vec3(values[0], values[1], values[2]);
                        copyColor(tmp.c, values + 3);
                        lights.push_back(tmp);
                    }
                }

                // Material Commands 
                // Ambient, diffuse, specular, shininess properties for each object.
                // Filling this in is pretty straightforward, so I've left it in 
                // the skeleton, also as a hint of how to do the more complex ones.
                // Note that no transforms/stacks are applied to the colors. 

                else if (cmd == "ambient") {
                    validinput = readvals(s, 3, values); // colors 
                    if (validinput) {
                        copyColor(ambient, values);
                    }
                } else if (cmd == "diffuse") {
                    validinput = readvals(s, 3, values); 
                    if (validinput) {
                        copyColor(diffuse, values);
                    }
                } else if (cmd == "specular") {
                    validinput = readvals(s, 3, values); 
                    if (validinput) {
                        copyColor(specular, values);
                    }
                } else if (cmd == "emission") {
                    validinput = readvals(s, 3, values); 
                    if (validinput) {
                        copyColor(emission, values);
                    }
                } else if (cmd == "shininess") {
                    validinput = readvals(s, 1, values); 
                    if (validinput) {
                        shininess = values[0]; 
                    }
                } else if (cmd == "attenuation") {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        attenuation_const = values[0];
                        attenuation_linear = values[1];
                        attenuation_quadratic = values[2];
                    }
                } else if (cmd == "camera") {
                    validinput = readvals(s,10,values); // 10 values eye cen up fov
                    if (validinput) {

                        // YOUR CODE FOR HW 2 HERE
                        // Use all of values[0...9]
                        // You may need to use the upvector fn in Transform.cpp
                        // to set up correctly. 
                        // Set eyeinit upinit center fovy in variables.h 
                        
                        point eyeinit = point(values[0], values[1], values[2]);
                        point center = point(values[3], values[4], values[5]);
                        point upinit = point(values[6], values[7], values[8]);
                        float fovy = values[9];
                        mycamera = camera(eyeinit, center, upinit, fovy);
                    }
                }
                // I've left the code for loading objects in the skeleton, so 
                // you can get a sense of how this works.  
                // Also look at demo.txt to get a sense of why things are done this way.
                else if (cmd == "maxverts" || cmd == "maxvertnorms" ) {
                    readvals(s, 1, values);
                }
                else if (cmd == "vertex") {
                    validinput = readvals(s, 3, values);
                    if( validinput ) vertices.push_back(Vec3(values[0], values[1], values[2]));
                }
                else if (cmd == "vertexnormal") {
                    validinput = readvals(s, 3, values);
                    if (validinput) vtns.push_back(vertexnormal(values[0], values[1], values[2], values[3], values[4], values[5]));
                }
                else if (cmd == "sphere" || cmd == "tri" || cmd == "trinormal") {
                    if (cmd == "sphere") {
                        validinput = readvals(s, 4, values);
                        objects.push_back(sphere(point(values[0], values[1], values[2]), values[3]));
                    }
                    else if (cmd == "tri") {
                        validinput = readvals(s, 3, values);
                        objects.push_back(triangle(vertices[(int)values[0]], vertices[(int)values[0]], vertices[(int)values[0]]) );
                    }
                    else {
                        validinput = readvals(s, 3, values);
                        // to be implemented
                    }
                    if (validinput) {
                        Shape* obj = &(objects.back());
                        // Set the object's light properties
                        for (i = 0; i < 4; i++) {
                            (obj->ambient) = ambient; 
                            (obj->diffuse) = diffuse; 
                            (obj->specular) = specular; 
                            (obj->emission) = emission;
                        }
                        obj->shininess = shininess; 

                        // Set the object's transform
                        obj->transform = transfstack.top(); 
                    }
                }

                else if (cmd == "translate") {
                    validinput = readvals(s,3,values); 
                    if (validinput) {

                        // YOUR CODE FOR HW 2 HERE.  
                        // Think about how the transformation stack is affected
                        // You might want to use helper functions on top of file. 
                        // Also keep in mind what order your matrix is!
                        rightmultiply(matrix44::createTranslateMatrix44(values[0], values[1], values[2]), transfstack);
                    }
                }
                else if (cmd == "scale") {
                    validinput = readvals(s,3,values); 
                    if (validinput) {

                        // YOUR CODE FOR HW 2 HERE.  
                        // Think about how the transformation stack is affected
                        // You might want to use helper functions on top of file.  
                        // Also keep in mind what order your matrix is!
                        rightmultiply(matrix44::createScaleMatrix44(values[0], values[1], values[2]), transfstack);
                    }
                }
                else if (cmd == "rotate") {
                    validinput = readvals(s,4,values); 
                    if (validinput) {
                        rightmultiply(matrix44::createRotateMatrix44(values[3], Vec3::normalize(Vec3(values[0], values[1], values[2]))), transfstack);
                    }
                }

                // I include the basic push/pop code for matrix stacks
                else if (cmd == "pushTransform") {
                    transfstack.push(transfstack.top()); 
                } else if (cmd == "popTransform") {
                    if (transfstack.size() <= 1) {
                        cerr << "Stack has no elements.  Cannot Pop\n"; 
                    } else {
                        transfstack.pop(); 
                    }
                }

                else {
                    cerr << "Unknown Command: " << cmd << " Skipping \n"; 
                }
            }
            getline (in, str); 
        }
    } else {
        cerr << "Unable to Open Input Data File " << filename << "\n"; 
        throw 2; 
    }
}
