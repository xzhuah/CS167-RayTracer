// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// glm provides vector, matrix classes like glsl
// Typedefs to make code more readable 

typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
const float pi = 3.14159265; // For portability across platforms


class Transform
{
public:
    Transform();
    virtual ~Transform();
    static void left(float degrees, vec3& eye, vec3& up);
    static void up(float degrees, vec3& eye, vec3& up);
    static mat4 lookAt(const vec3& eye, const vec3 &center, const vec3& up);
    static mat4 perspective(float fovy, float aspect, float zNear, float zFar);
    static mat3 rotate(const float degrees, const vec3& axis);
    static mat4 scale(const float &sx, const float &sy, const float &sz);
    static mat4 translate(const float &tx, const float &ty, const float &tz);
    static vec3 upvector(const vec3 &up, const vec3 &zvec);
};

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    mat3 ret;
    // YOUR CODE FOR HW2 HERE
    // Please implement this.  Likely the same as in HW 1. 
    mat3 myIdentity = mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
    mat3 myAAT = mat3(axis.x*axis.x, axis.x*axis.y, axis.x*axis.z, axis.y*axis.x, axis.y*axis.y, axis.y*axis.z, axis.z*axis.x, axis.z*axis.y, axis.z*axis.z);
    mat3 myAstar = mat3(0, axis.z, -axis.y, -axis.z, 0, axis.x, axis.y, -axis.x, 0);
    // You will change this return call
    ret = glm::cos(glm::radians(degrees))*myIdentity + (1 - glm::cos(glm::radians(degrees)))*myAAT + glm::sin(glm::radians(degrees))*myAstar;
    return ret;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    mat3 M = rotate(degrees, glm::normalize(up));
    eye = M*eye;
    up = glm::transpose(glm::inverse(M))*up;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE 
    // Likely the same as in HW 1. 
    vec3 w = glm::normalize(eye);
    vec3 u = glm::normalize(glm::cross(up, -eye));
    mat3 M = rotate(degrees, u);
    eye = M*eye;
    up = glm::transpose(glm::inverse(M))*up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    vec3 w = glm::normalize(eye);
    vec3 u = glm::normalize(glm::cross(up, eye));
    vec3 v = glm::cross(w, u);
    mat3 R;
    R[0][0] = u.x; R[0][1] = u.y; R[0][2] = u.z;
    R[1][0] = v.x; R[1][1] = v.y; R[1][2] = v.z;
    R[2][0] = w.x; R[2][1] = w.y; R[2][2] = w.z;
    R = glm::transpose(R);
    vec3 RT = R*eye;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        ret[j][i] = R[j][i];
      }
      ret[3][i] = -RT[i];
    }
    ret[0][3] = 0;  ret[1][3] = 0;  ret[2][3] = 0;  ret[3][3] = 1;
    return ret;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // New, to implement the perspective transform as well.  
    float d = 1.0 / tan(glm::radians(fovy) / 2);
    ret = mat4(d / aspect, 0, 0, 0,   0, d, 0, 0,    0, 0, -(zFar + zNear) / (zFar - zNear), -1,   0, 0, -2 * zFar*zNear / (zFar - zNear), 0);
    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Implement scaling 
    ret = mat4(sx, 0, 0, 0,   0, sy, 0, 0,   0, 0, sz, 0,   0, 0, 0, 1);
    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Implement translation 
    ret = mat4(1, 0, 0, 0,   0, 1, 0, 0,   0, 0, 1, 0,   tx, ty, tz, 1);
    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
